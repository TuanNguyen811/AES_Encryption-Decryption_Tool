include <iostream>
#include <filesystem>
#include <string>
#include <chrono>

#include "aes.h"
#include "hash.h"
#include "hmac.h"
#include "compressor.h"
#include "readFile.h"
#include "writeFile.h"
#include "decryptionFormat.h"

namespace fs = std::filesystem;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: program <file_or_folder>\n";
        return 1;
    }

    fs::path inputPath(argv[1]);
    if (!fs::exists(inputPath)) {
        std::cerr << "Path does not exist: " << inputPath << "\n";
        return 1;
    }

    // Nhập key
    std::string k;
    std::cout << "\nEnter key: ";
    std::getline(std::cin, k);

    auto total_start = high_resolution_clock::now();

    // Đọc dữ liệu từ file cần giải mã
    std::cout << "Reading encrypted file...\n";
    auto read_start = high_resolution_clock::now();
    std::vector<uint8_t> buffer = readFileAsBytes(inputPath);
    auto read_end = high_resolution_clock::now();
    std::cout << "Read complete. File size: " << buffer.size() << " bytes\n";

    // Băm key
    std::cout << "Hashing key...\n";
    auto hash_start = high_resolution_clock::now();
    SHA256 sha256;
    std::vector<uint8_t> key = sha256.hash(std::vector<uint8_t> (k.begin(), k.end()));
    auto hash_end = high_resolution_clock::now();
    std::cout << "Key hashing complete\n";

    DecryptionResult result;
    auto format_start = high_resolution_clock::now();
    try {
        // Tách dữ liệu trong tệp mục tiêu và xác thực file có hợp lệ không
        std::cout << "Parsing encrypted format...\n";
        result = parseEncryptedFormat(buffer, key);
        std::cout << "Format verified and HMAC valid\n";
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }
    auto format_end = high_resolution_clock::now();

    // Giải mã
    std::cout << "Decrypting AES...\n";
    auto decrypt_start = high_resolution_clock::now();
    AES aes(key, static_cast<AES::Mode>(result.mode));
    std::vector<uint8_t> plaintext;
    try {
        plaintext = aes.decrypt(result.ciphertext, result.iv);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    auto decrypt_end = high_resolution_clock::now();
    std::cout << "AES decryption complete\n";

    // Ghi dữ liệu vào file 7z
    fs::path zipFile = inputPath; zipFile = zipFile.replace_extension(".7z");

    std::cout << "Writing decrypted archive...\n";
    auto write_start = high_resolution_clock::now();
    if (!writeFileAsBytes(zipFile, plaintext)) {
        std::cerr << "Failed to write file\n";
        return 1;
    }
    auto write_end = high_resolution_clock::now();
    std::cout << "Written to: " << zipFile << "\n";

    // Thực hiện giải nén file 7z
    std::cout << "Decompressing archive...\n";
    auto decompress_start = high_resolution_clock::now();
    fs::path outputFolder = zipFile.parent_path();
    if (!Compressor::decompress(plaintext, zipFile, outputFolder)) {
        return 1;
    }
    auto decompress_end = high_resolution_clock::now();

    // Thực hiện xóa file mã hóa (.aes)
    fs::remove_all(inputPath.string().c_str());
    
    // Thực hiện xóa đi file nén 7z
    fs::remove_all(zipFile.string().c_str());

    auto total_end = high_resolution_clock::now();

    // In thời gian
    auto ms = [](auto start, auto end) {
        return duration_cast<milliseconds>(end - start).count();
    };

    auto mbps = [](size_t bytes, auto start, auto end) {
        double seconds = duration_cast<duration<double>>(end - start).count();
        return (bytes / (1024.0 * 1024.0)) / (seconds > 0 ? seconds : 1e-6);
    };

    std::cout << "\n\n===== Time taken and speed =====\n";
    std::cout << "Read encrypted  : " << ms(read_start, read_end) << " ms ("
              << mbps(buffer.size(), read_start, read_end) << " MB/s)\n";
    std::cout << "Hash key        : " << ms(hash_start, hash_end) << " ms\n";
    std::cout << "Parse format    : " << ms(format_start, format_end) << " ms\n";
    std::cout << "AES Decryption  : " << ms(decrypt_start, decrypt_end) << " ms ("
              << mbps(result.ciphertext.size(), decrypt_start, decrypt_end) << " MB/s)\n";
    std::cout << "Write zip       : " << ms(write_start, write_end) << " ms ("
              << mbps(plaintext.size(), write_start, write_end) << " MB/s)\n";
    std::cout << "Decompress      : " << ms(decompress_start, decompress_end) << " ms\n";
    std::cout << "Total time      : " << ms(total_start, total_end) << " ms\n";

    return 0;
}

#include <iostream>
#include <filesystem>
#include <chrono>
#include <string>

#include "aes.h"
#include "hash.h"
#include "hmac.h"
#include "compressor.h"
#include "readFile.h"
#include "writeFile.h"
#include "encryptionFormat.h"

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
    std::cout << "\nEnter key: ";
    std::string k;
    std::getline(std::cin, k);
    
    auto total_start = high_resolution_clock::now();

    // Nén
    std::cout << "Compressing input...\n";
    auto compress_start = high_resolution_clock::now();
    Compressor compressor(inputPath);
    if (!compressor.compress()) {
        return 1;
    }
    std::string zipFile = compressor.getOutputName();
    auto compress_end = high_resolution_clock::now();

    // Đọc file nén
    std::cout << "Reading compressed file...\n";
    auto read_start = high_resolution_clock::now();
    fs::path inputZipFile = inputPath.parent_path() / zipFile;
    std::vector<uint8_t> buffer = readFileAsBytes(inputZipFile);
    auto read_end = high_resolution_clock::now();
    std::cout << "Read complete. File size: " << buffer.size() << " bytes\n";

    // Băm key
    std::cout << "Hashing key...\n";
    auto hash_start = high_resolution_clock::now();
    SHA256 hash;
    std::vector<uint8_t> key = hash.hash(std::vector<uint8_t>(k.begin(), k.end()));
    auto hash_end = high_resolution_clock::now();
    std::cout << "Key hashing complete\n";

    // Mã hóa AES
    std::cout << "Encrypting with AES...\n";
    auto encrypt_start = high_resolution_clock::now();
    AES aes(key, AES::Mode::CBC);

    // Tạo iv nếu không phải là mode ECB
    std::vector<uint8_t> iv;
    if (aes.mode_ != AES::Mode::ECB) {
        iv = aes.generateRandomIV();
    }
    
    std::vector<uint8_t> ciphertext = aes.encrypt(buffer, iv);
    auto encrypt_end = high_resolution_clock::now();
    std::cout << "AES encryption complete\n";

    // Tạo định dạng file mã hóa
    std::cout << "Building encrypted format...\n";
    auto format_start = high_resolution_clock::now();
    ciphertext = buildEncryptedFormat(ciphertext, key, iv, static_cast<uint8_t>(aes.mode_));
    auto format_end = high_resolution_clock::now();
    std::cout << "Encrypted format built successfully\n";

    // Ghi file mã hóa
    std::cout << "Writing encrypted file...\n";
    auto write_start = high_resolution_clock::now();
    fs::path outputFile = inputZipFile; outputFile.replace_extension(".aes");
    if (!writeFileAsBytes(outputFile, ciphertext)) {
        std::cerr << "Failed to write file\n";
        return 1;
    }
    auto write_end = high_resolution_clock::now();
    std::cout << "File written: " << outputFile << "\n";

    // Thực hiện xóa đi dữ liệu gốc
    fs::remove_all(inputPath.string().c_str());

    // Thực hiện xóa đi file nén 7z
    fs::remove_all(inputZipFile.string().c_str());

    auto total_end = high_resolution_clock::now();

    // In thời gian
    auto ms = [](auto start, auto end) {
        return duration_cast<milliseconds>(end - start).count();
    };

    auto mbps = [](size_t bytes, auto start, auto end) {
        double seconds = duration_cast<duration<double>>(end - start).count();
        return (bytes / (1024.0 * 1024.0)) / (seconds > 0 ? seconds : 1e-6);  // tránh chia 0
    };


    std::cout << "\n\n===== Time taken and speed =====\n";
    std::cout << "Compression     : " << ms(compress_start, compress_end) << " ms\n";

    std::cout << "Read file       : " << ms(read_start, read_end) << " ms"
            << " (" << mbps(buffer.size(), read_start, read_end) << " MB/s)\n";

    std::cout << "Hash key        : " << ms(hash_start, hash_end) << " ms\n";

    std::cout << "AES Encryption  : " << ms(encrypt_start, encrypt_end) << " ms"
            << " (" << mbps(buffer.size(), encrypt_start, encrypt_end) << " MB/s)\n";

    std::cout << "Format building : " << ms(format_start, format_end) << " ms\n";

    std::cout << "Write file      : " << ms(write_start, write_end) << " ms"
            << " (" << mbps(ciphertext.size(), write_start, write_end) << " MB/s)\n";

    std::cout << "Total time      : " << ms(total_start, total_end) << " ms\n";

    return 0;
}

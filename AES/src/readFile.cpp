#include "readFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

std::vector<uint8_t> readFileAsBytes(const std::filesystem::path& filename) {
    std::cout << "DEBUG: Reading file: " << filename << std::endl;

    try {
        // Kiểm tra file có tồn tại không
        if (!std::filesystem::exists(filename)) {
            std::cerr << "File does not exist: " << filename << "\n";
            return {};
        }

        // Lấy kích thước file bằng filesystem (an toàn hơn tellg)
        std::error_code ec;
        std::uintmax_t file_size = std::filesystem::file_size(filename, ec);

        if (ec) {
            std::cerr << "Cannot get file size: " << ec.message() << "\n";
            return {};
        }

        std::cout << "DEBUG: File size from filesystem: " << file_size << " bytes" << std::endl;

        if (file_size == 0) {
            std::cout << "Warning: File is empty: " << filename << "\n";
            return {};
        }

        // Kiểm tra kích thước hợp lý (max 1GB)
        if (file_size > 1024ULL * 1024 * 1024) {
            std::cerr << "File too large (>1GB): " << filename << " (" << file_size << " bytes)\n";
            return {};
        }

        // Kiểm tra vector có thể chứa được không
        std::vector<uint8_t> test_vector;
        if (file_size > test_vector.max_size()) {
            std::cerr << "File size exceeds vector max_size: " << file_size << " > " << test_vector.max_size() << "\n";
            return {};
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << "\n";
            return {};
        }

        // Sử dụng kích thước từ filesystem thay vì tellg()
        size_t filesize = static_cast<size_t>(file_size);
        std::cout << "DEBUG: About to create vector of size: " << filesize << std::endl;

        // Tạo vector với kích thước cố định
        std::vector<uint8_t> buffer(filesize);

        std::cout << "DEBUG: Vector created successfully, reading file..." << std::endl;

        // Đọc file
        file.read(reinterpret_cast<char*>(buffer.data()), filesize);

        // Kiểm tra số byte đã đọc
        std::streamsize bytes_read = file.gcount();
        std::cout << "DEBUG: Bytes read: " << bytes_read << " / " << filesize << std::endl;

        if (bytes_read != static_cast<std::streamsize>(filesize)) {
            std::cout << "Warning: Expected " << filesize << " bytes, got " << bytes_read << " bytes" << std::endl;
            buffer.resize(bytes_read); // Resize theo số byte thực tế
        }

        file.close();

        std::cout << "Successfully read " << buffer.size() << " bytes from " << filename << "\n";
        return buffer;

    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << "\n";
        return {};
    } catch (const std::exception& e) {
        std::cerr << "Exception reading file: " << e.what() << "\n";
        return {};
    }
}

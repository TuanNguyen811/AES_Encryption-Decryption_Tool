#include "writeFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

// ghi dữ liệu mã hóa vào file
int writeFileAsBytes(const std::filesystem::path& filename, const std::vector<uint8_t>& buffer) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return 0;
    }
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    return 1;
}
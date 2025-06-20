#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace fs = std::filesystem;

class Compressor {
public:
    // Constructor
    Compressor(const fs::path& input, const std::string& format = "7z", const std::string& level = "-mx=1");

    // Nén file hoặc thư mục
    bool compress();

    static bool checkFormat7z(const std::vector<uint8_t>& plaintext);

    // Giải nén
    static bool decompress(const std::vector<uint8_t>& plaintext, const fs::path& archivePath, const fs::path& destination);

    // Lấy tên file nén
    std::string getOutputName();

private:
    fs::path inputPath;
    std::string outputFile;
    std::string compressionLevel;
    std::string archiveFormat;

    // Tạo câu lệnh cho việc nén
    std::string buildCompressCommand() const;
};

#include "compressor.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdint>

Compressor::Compressor(const fs::path& input, const std::string& format, const std::string& level)
    : inputPath(input), archiveFormat(format), compressionLevel(level) {
        outputFile = getOutputName();
}

std::string Compressor::getOutputName() {
    if (fs::is_directory(inputPath))
        return inputPath.filename().string() + "." + archiveFormat;
    else
        return inputPath.stem().string() + "." + archiveFormat;
}

std::string Compressor::buildCompressCommand() const {
    std::string typeArg = "-t" + archiveFormat;
    std::string quotedOutput = "\"" + (inputPath.parent_path() / outputFile).string() + "\"";
    std::string quotedInput = "\"" + inputPath.string() + "\"";
    return "7z a " + typeArg + " -mmt=on -ms=off " + quotedOutput + " " + quotedInput + " " + compressionLevel;
}

bool Compressor::compress() {
    if (!fs::exists(inputPath)) {
        std::cerr << "Path does not exist: " << inputPath << "\n";
        return false;
    }

    std::string cmd = buildCompressCommand();
    std::cout << "Executing: " << cmd << "\n";

    int result = system(cmd.c_str());
    if (result == 0) {
        std::cout << "Compression complete: " << outputFile << "\n";
        return true;
    } else {
        std::cerr << "Compression failed.\n";
        return false;
    }
}

// Kiểm tra format 7z
// Độ dài tối thiểu của một file 7z phải là 32bytes, trong đó có 6bytes đầu là magic bytes
bool Compressor::checkFormat7z(const std::vector<uint8_t>& plaintext) {
    const std::vector<uint8_t> magic7z = {0x37, 0x7A, 0xBC, 0xAF, 0x27, 0x1C};
    return plaintext.size() >= 32 && std::equal(magic7z.begin(), magic7z.end(), plaintext.begin());
}

bool Compressor::decompress(const std::vector<uint8_t>& plaintext, const fs::path& archivePath, const fs::path& destination) {
    // Kiểm tra format
    if (!checkFormat7z(plaintext)) {
        std::cerr << "Invalid format: not a valid 7z archive (signature mismatch).\n";
        return false;
    }

    if (!fs::exists(archivePath)) {
        std::cerr << "Archive not found: " << archivePath << "\n";
        return false;
    }

    std::string cmd = "7z x \"" + archivePath.string() + "\" -o\"" + destination.string() + "\" -y";
    std::cout << "Extracting: " << cmd << "\n";

    int result = system(cmd.c_str());
    if (result == 0) {
        std::cout << "Decompression complete.\n";
        return true;
    } else {
        std::cerr << "Decompression failed.\n";
        return false;
    }
}

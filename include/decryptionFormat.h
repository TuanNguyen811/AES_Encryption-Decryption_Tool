#pragma once

#include <vector>
#include <cstdint>
#include <string>

struct DecryptionResult {
    uint8_t mode;
    std::vector<uint8_t> iv;
    std::vector<uint8_t> ciphertext;
};

DecryptionResult parseEncryptedFormat(const std::vector<uint8_t>& data, std::vector<uint8_t>& key);
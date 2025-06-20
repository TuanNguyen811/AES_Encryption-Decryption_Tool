#pragma once

#include <vector>
#include <cstdint>
#include <string>

std::vector<uint8_t> buildEncryptedFormat(
    const std::vector<uint8_t>& cipherText,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& iv,
    uint8_t mode      
);
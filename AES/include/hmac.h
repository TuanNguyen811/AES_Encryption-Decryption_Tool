#pragma once

#include <string>
#include <cstdint>
#include <vector>

class HMAC {
public:
    HMAC() = delete;
    static std::vector<uint8_t> compute(const std::vector<uint8_t>& key, const std::vector<uint8_t>& message);
};

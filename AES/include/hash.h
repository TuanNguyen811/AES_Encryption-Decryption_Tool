#pragma once

#include <string>
#include <cstdint>
#include <vector>

class SHA256 {
private:
    uint32_t h[8];
    static const uint32_t K[64];
    
    uint32_t RIGHTROTATE(uint32_t n, uint32_t x) { return (x >> n) | (x << (32 - n)); }
    uint32_t sigma0(uint32_t x) { return RIGHTROTATE(7, x) ^ RIGHTROTATE(18, x) ^ (x >> 3); }
    uint32_t sigma1(uint32_t x) { return RIGHTROTATE(17, x) ^ RIGHTROTATE(19, x) ^ (x >> 10); }
    uint32_t SIGMA0(uint32_t x) { return RIGHTROTATE(2, x) ^ RIGHTROTATE(13, x) ^ RIGHTROTATE(22, x); }
    uint32_t SIGMA1(uint32_t x) { return RIGHTROTATE(6, x) ^ RIGHTROTATE(11, x) ^ RIGHTROTATE(25, x); }
    uint32_t CH(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }

public:
    SHA256();
    void reset();
    // std::string hash(const std::string& message);
    std::vector<uint8_t> hash(const std::vector<uint8_t>& message);
};

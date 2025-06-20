#include "hmac.h"
#include "hash.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

// HMAC(K,M)=H((K′⊕opad)∥H((K′⊕ipad)∥M)) với ∥ là phép nối chuỗi
std::vector<uint8_t> HMAC::compute(const std::vector<uint8_t> &key, const std::vector<uint8_t> &message) {
    const size_t block_size = 64;
    SHA256 sha256;
    std::vector<uint8_t> padded_key = key;

    // Đệm thêm các byte 0x0 vào để bằng độ dài với block 64bytes
    padded_key.resize(block_size, 0x00);

    // Tạo khóa đệm ipad và opad
    std::vector<uint8_t> ipad(block_size, 0x00);
    std::vector<uint8_t> opad (block_size, 0x00);
    for (size_t i = 0; i < block_size; ++i) {
        opad[i] = padded_key[i] ^ 0x5c;
        ipad[i] = padded_key[i] ^ 0x36;
    }

    // Tính HMAC 
    std::vector<uint8_t> innerInput = ipad;
    innerInput.insert(innerInput.end(), message.begin(), message.end());
    std::vector<uint8_t> innerHash = sha256.hash(innerInput);

    std::vector<uint8_t> outerInput = opad;
    outerInput.insert(outerInput.end(), innerHash.begin(), innerHash.end());

    return sha256.hash(outerInput);
}

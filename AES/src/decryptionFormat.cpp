#include "decryptionFormat.h"
#include "hmac.h"
#include <stdexcept>
#include <iostream>

DecryptionResult parseEncryptedFormat(
    const std::vector<uint8_t>& data,
    std::vector<uint8_t>& key
) {
    DecryptionResult result;
    size_t offset = 0;

    // Kiểm tra độ dài tối thiểu: magic (3) + keylen (1) + mode (1)
    if (data.size() < 5)
        throw std::runtime_error("\nEncrypted data is invalid: too short.");

    // 1. Kiểm tra magic bytes
    if (!(data[0] == 'A' && data[1] == 'E' && data[2] == 'S'))
        throw std::runtime_error("\nInvalid magic bytes.");

    offset = 3;

    // 2. Kiểm tra key
    size_t keyLength = data[offset++];
    if (keyLength != 16 && keyLength != 24 && keyLength != 32) {
        throw std::runtime_error("\nInvalid key length. Only 16, 24, or 32 bytes are supported.");
    }

    // Cắt ngắn key
    key.resize(keyLength);

    // 3. kiểm tra mode
    result.mode = data[offset++];
    if (result.mode > 3) {
        throw std::runtime_error("\nInvalid AES mode.");
    }

    // 4. IV (nếu không phải ECB, giả định 16 byte)
    if (result.mode != 0) {
        if (data.size() < offset + 16)
            throw std::runtime_error("\nMissing IV data.");
        result.iv.assign(data.begin() + offset, data.begin() + offset + 16);
        offset += 16;
    }

    // 5. Kiểm tra HMAC (32 bytes cuối cùng)
    if (data.size() < offset + 32)
        throw std::runtime_error("\nMissing HMAC data.");

    size_t hmac_offset = data.size() - 32;

    // 6. Ciphertext
    result.ciphertext.assign(data.begin() + offset, data.begin() + hmac_offset);
    if (result.ciphertext.empty()) {
        throw std::runtime_error("\nNo ciphertext found in the encrypted data.");
    }

    // 7. Xác thực HMAC
    std::vector<uint8_t> buffer(data.begin(), data.begin() + hmac_offset);
    std::vector<uint8_t> expected_hmac(data.begin() + hmac_offset, data.end());
    std::vector<uint8_t> computed_hmac = HMAC::compute(key, buffer);

    if (computed_hmac != expected_hmac) {
        throw std::runtime_error("\nInvalid key.");
    }

    return result;
}

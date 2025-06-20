#pragma once

#include <vector>
#include <cstdint>
#include <stdexcept>

class AES {
public:
    // Enum for key lengths and modes
    enum class KeyLength { AES_128 = 16, AES_192 = 24, AES_256 = 32 };
    enum class Mode {ECB, CBC, CFB, OFB};

    // Constructor: Khởi tạo với khóa và chế độ mã hóa
    AES(const std::vector<uint8_t>& key, Mode mode);

    Mode mode_; // Chế độ mã hóa

    std::vector<uint8_t> generateRandomIV(); // Tạo IV ngẫu nhiên an toàn

    // Mã hóa plaintext, trả về ciphertext
    // IV là tùy chọn (chỉ cần cho CBC, CFB, OFB)
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext,
                                const std::vector<uint8_t>& iv = {});

    // Giải mã ciphertext, trả về plaintext
    // IV là tùy chọn (chỉ cần cho CBC, CFB, OFB)
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext,
                                const std::vector<uint8_t>& iv = {});

private:
    // Hằng số AES
    size_t Nb = 4; // Số cột (4 từ 32-bit)
    size_t Nk = 4; // Số từ trong khóa (4, 6, hoặc 8)
    size_t Nr = 10; // Số vòng (10, 12, hoặc 14)
    std::vector<uint32_t> expanded_key_; // Khóa mở rộng

    // Key expansion
    uint32_t subWord(uint32_t word);
    uint32_t rotWord(uint32_t word);
    void keyExpansion(const std::vector<uint8_t>& key);

    // Block processing
    void encryptBlock(uint8_t state[16]);
    void decryptBlock(uint8_t state[16]);

    // AES transformations
    void subBytes(uint8_t state[16]);
    void shiftRows(uint8_t state[16]);
    void mixColumns(uint8_t state[16]);
    void addRoundKey(uint8_t state[16], size_t round);

    // Inverse transformations
    void invSubBytes(uint8_t state[16]);
    void invShiftRows(uint8_t state[16]);
    void invMixColumns(uint8_t state[16]);

    // Mode implementations
    void processECB(const uint8_t* input, uint8_t* output, size_t blocks, bool encrypt);
    void processCBC(const uint8_t* input, uint8_t* output, size_t blocks,
                   const uint8_t iv[16], bool encrypt);
    void processCFB(const uint8_t* input, uint8_t* output, size_t numBytes,
                   const uint8_t iv[16]);
    void processOFB(const uint8_t* input, uint8_t* output, size_t numBytes,
                   const uint8_t iv[16]);

    // Helpers
    void validateIV(const std::vector<uint8_t>& iv) const;
    void validateKey(const std::vector<uint8_t>& key) const;
    void xorBlock(uint8_t* target, const uint8_t* source);
    void padData(std::vector<uint8_t>& data) const;
    void unpadData(std::vector<uint8_t>& data) const;

    // Lookup tables (khai báo trong .cpp để tránh vấn đề liên kết)
    static const uint8_t sbox[256];
    static const uint8_t inv_sbox[256];
    static const uint8_t rcon[11];
    static const uint8_t galoisMul2[256];
    static const uint8_t galoisMul3[256];
    static const uint8_t galoisMul9[256];
    static const uint8_t galoisMul11[256];
    static const uint8_t galoisMul13[256];
    static const uint8_t galoisMul14[256];
};

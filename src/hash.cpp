#include "hash.h"
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>

// Xoay phải
#define RIGHTROTATE(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
// Các phép toán SHA-256
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIGMA0(x) (RIGHTROTATE(x, 2) ^ RIGHTROTATE(x, 13) ^ RIGHTROTATE(x, 22))
#define SIGMA1(x) (RIGHTROTATE(x, 6) ^ RIGHTROTATE(x, 11) ^ RIGHTROTATE(x, 25))
#define sigma0(x) (RIGHTROTATE(x, 7) ^ RIGHTROTATE(x, 18) ^ ((x) >> 3))
#define sigma1(x) (RIGHTROTATE(x, 17) ^ RIGHTROTATE(x, 19) ^ ((x) >> 10))

const uint32_t SHA256::K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

SHA256::SHA256() {
    reset();
}

void SHA256::reset() {
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
}

// std::string SHA256::hash(const std::string &message) {
//     reset();

//     size_t initial_len = message.length();
//     std::vector<uint8_t> msg(initial_len);
//     memcpy(msg.data(), message.c_str(), initial_len);

//     // Thêm bit 1 (0x80)
//     msg.push_back(0x80);
//     // Thêm các bit 0 để độ dài chia hết cho 64 byte, trừ 8 byte cuối
//     while (msg.size() % 64 != 56) {
//         msg.push_back(0);
//     }

//     // Thêm độ dài bit của thông điệp ban đầu
//     uint64_t bit_len = initial_len * 8;
//     for (int i = 7; i >= 0; i--) {
//         msg.push_back((bit_len >> (i * 8)) & 0xFF);
//     }

//     // Xử lý từng khối 512 bit (64 byte)
//     for (size_t i = 0; i < msg.size(); i += 64) {
//         uint32_t w[64];

//         // (message schedule)
//         for (int j = 0; j < 16; j++) {
//             w[j] = (msg[i + j * 4] << 24) |
//                    (msg[i + j * 4 + 1] << 16) |
//                    (msg[i + j * 4 + 2] << 8) |
//                    (msg[i + j * 4 + 3]);
//         }

//         for (int j = 16; j < 64; j++) {
//             w[j] = sigma1(w[j - 2]) + w[j - 7] + sigma0(w[j - 15]) + w[j - 16];
//         }

//         // Khởi tạo giá trị băm cho khối hiện tại
//         uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
//         uint32_t e = h[4], f = h[5], g = h[6], h_temp = h[7];

//         // 64 vòng lặp chính
//         for (int j = 0; j < 64; j++) {
//             uint32_t t1 = h_temp + SIGMA1(e) + CH(e, f, g) + K[j] + w[j];
//             uint32_t t2 = SIGMA0(a) + MAJ(a, b, c);
//             h_temp = g;
//             g = f;
//             f = e;
//             e = d + t1;
//             d = c;
//             c = b;
//             b = a;
//             a = t1 + t2;
//         }

//         // Cập nhật giá trị băm
//         h[0] += a;
//         h[1] += b;
//         h[2] += c;
//         h[3] += d;
//         h[4] += e;
//         h[5] += f;
//         h[6] += g;
//         h[7] += h_temp;
//     }

//     // Tạo chuỗi kết quả
//     std::stringstream ss;
//     for (int i = 0; i < 8; i++) {
//         ss << std::hex << std::setw(8) << std::setfill('0') << h[i];
//     }

//     return ss.str();
// }

std::vector<uint8_t> SHA256::hash(const std::vector<uint8_t>& message) {
    reset();

    std::vector<uint8_t> msg = message;

    // Thêm bit 1 (0x80)
    msg.push_back(0x80);
    // Thêm các bit 0 để độ dài chia hết cho 64 byte, trừ 8 byte cuối
    while (msg.size() % 64 != 56) {
        msg.push_back(0);
    }

    // Thêm độ dài bit của thông điệp ban đầu
    uint64_t bit_len = message.size() * 8;
    for (int i = 7; i >= 0; i--) {
        msg.push_back((bit_len >> (i * 8)) & 0xFF);
    }

    // Xử lý từng khối 512 bit (64 byte)
    for (size_t i = 0; i < msg.size(); i += 64) {
        uint32_t w[64];

        // (message schedule)
        for (int j = 0; j < 16; j++) {
            w[j] = (msg[i + j * 4] << 24) |
                   (msg[i + j * 4 + 1] << 16) |
                   (msg[i + j * 4 + 2] << 8) |
                   (msg[i + j * 4 + 3]);
        }

        for (int j = 16; j < 64; j++) {
            w[j] = sigma1(w[j - 2]) + w[j - 7] + sigma0(w[j - 15]) + w[j - 16];
        }

        // Khởi tạo giá trị băm cho khối hiện tại
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], h_temp = h[7];

        // 64 vòng lặp chính
        for (int j = 0; j < 64; j++) {
            uint32_t t1 = h_temp + SIGMA1(e) + CH(e, f, g) + K[j] + w[j];
            uint32_t t2 = SIGMA0(a) + MAJ(a, b, c);
            h_temp = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        // Cập nhật giá trị băm
        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_temp;
    }

    // Tạo chuỗi kết quả
    std::vector<uint8_t> digest;
    for (int i = 0; i < 8; ++i) {
        digest.push_back((h[i] >> 24) & 0xFF);
        digest.push_back((h[i] >> 16) & 0xFF);
        digest.push_back((h[i] >> 8) & 0xFF);
        digest.push_back(h[i] & 0xFF);
    }
    return digest;
}

#include "encryptionFormat.h"
#include "hmac.h"
#include <vector>
#include <cstdint>
#include <string>

/*
Format của file mã hóa sẽ bao gồm
[magic bytes][key length][mode][iv][ciphertext][hmac]

Trong đó:
    - magic bytes là b'AES'
    - iv nếu không phải là ECB
    - hmac sẽ được tính dựa vào key mã hóa và [magic bytes][key length][mode][iv][ciphertext]
*/

std::vector<uint8_t> buildEncryptedFormat(
    const std::vector<uint8_t>& cipherText,
    const std::vector<uint8_t>& key,
    const std::vector<uint8_t>& iv,
    uint8_t mode      
) {
    std::vector<uint8_t> output;

    // 1. Magic bytes: "AES"
    output.insert(output.end(), {'A', 'E', 'S'});

    // 2. Key length (1 byte)
    output.push_back(key.size());

    // 3. Mode (1 byte)
    output.push_back(mode);

    // 4. IV (nếu không phải ECB)
    if (mode != 0) {
        output.insert(output.end(), iv.begin(), iv.end());
    }

    // 5. Ciphertext
    output.insert(output.end(), cipherText.begin(), cipherText.end());

    // 6. HMAC
    std::vector<uint8_t> hmac = HMAC::compute(key, output);
    output.insert(output.end(), hmac.begin(), hmac.end());

    return output;
}

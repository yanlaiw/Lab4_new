#include "crypto.h"
#include <stdexcept>
// Week 2: Implement XOR encryption/decryption. The same function does both.
std::string xorCipher(const std::string& text, unsigned char key) {
    (void)key;
    // TODO: return a string with every byte XORed with key.
    return text;
}
// Week 3: Implement repeated-squaring modular exponentiation.
int modPow(int base, int exponent, int modulus) {
    (void)base; (void)exponent; (void)modulus;
    // TODO: compute (base^exponent) % modulus without using floating-point pow().
    return 0;
}
int rsaEncrypt(int value, int e, int n) {
    // TODO: use modPow() with the public exponent.
    (void)value; (void)e; (void)n;
    return 0;
}
int rsaDecrypt(int value, int d, int n) {
    // TODO: use modPow() with the private exponent.
    (void)value; (void)d; (void)n;
    return 0;
}

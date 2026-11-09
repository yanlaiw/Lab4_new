#pragma once
#include <string>
// Educational algorithms only: NOT secure for real-world use.
std::string xorCipher(const std::string& text, unsigned char key);
int modPow(int base, int exponent, int modulus);
int rsaEncrypt(int value, int e, int n);
int rsaDecrypt(int value, int d, int n);

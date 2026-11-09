#include "wire.h"
#include <sys/socket.h>
#include <cctype>
#include <cstdio>

bool sendLine(int fd, const std::string& line) {
    if (line.size() > 4095 || line.find('\n') != std::string::npos) return false;
    std::string data = line + "\n";
    size_t pos = 0;
    while (pos < data.size()) {
        ssize_t n = send(fd, data.data() + pos, data.size() - pos, MSG_NOSIGNAL);
        if (n <= 0) return false;
        pos += static_cast<size_t>(n);
    }
    return true;
}
bool readLine(int fd, std::string& line) {
    line.clear(); char c;
    while (line.size() < 4096) {
        ssize_t n = recv(fd, &c, 1, 0);
        if (n <= 0) return false;
        if (c == '\n') return true;
        line.push_back(c);
    }
    return false;
}
std::string hexEncode(const std::string& bytes) {
    const char* digits = "0123456789ABCDEF";
    std::string out;
    for (unsigned char c : bytes) { out += digits[c >> 4]; out += digits[c & 15]; }
    return out;
}
bool hexDecode(const std::string& hex, std::string& bytes) {
    if (hex.size() % 2) return false;
    auto val = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return -1;
    };
    bytes.clear();
    for (size_t i=0; i<hex.size(); i+=2) {
        int a=val(hex[i]), b=val(hex[i+1]);
        if (a < 0 || b < 0) return false;
        bytes += static_cast<char>((a<<4)|b);
    }
    return true;
}

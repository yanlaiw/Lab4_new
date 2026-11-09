#pragma once
#include <string>
// Provided transport helpers: newline-delimited protocol, max 4096 bytes per line.
bool sendLine(int fd, const std::string& line);
bool readLine(int fd, std::string& line);
std::string hexEncode(const std::string& bytes);
bool hexDecode(const std::string& hex, std::string& bytes);

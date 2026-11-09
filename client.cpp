#include "crypto.h"
#include "wire.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>

// TODO Week 1: Read command line: ./client 127.0.0.1 PORT plain|xor|hybrid.
// TODO Week 1: Connect to the server using socket() and connect().
// TODO Week 1: Read multiple lines from stdin and send TEXT <message>.
//              Print each ACK response as ACK: <message>.
// TODO Week 2: In xor mode, encrypt each message using key=7,
//              hex-encode it, send MSG <hex>, decrypt ACK responses.
// TODO Week 3: In hybrid mode, send KEY <RSA-encrypted key> first,
//              wait for READY, then exchange encrypted messages.
// TODO: On input quit, send QUIT, wait for BYE, print BYE, close and exit.
// You may add helper functions and change the structure of this file.
int main(int argc, char** argv) {
    (void)argc; (void)argv;
    std::cerr << "TODO: implement client.cpp\n";
    return 1;
}

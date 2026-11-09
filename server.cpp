#include "crypto.h"
#include "wire.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>

// TODO Week 1: Read command line: ./server PORT plain|xor|hybrid.
// TODO Week 1: Create an IPv4 TCP socket, bind to 127.0.0.1:PORT,
//              listen(), accept() one client, and close descriptors.
// TODO Week 1: In plain mode, receive TEXT <message> and reply ACK <message>.
// TODO Week 2: In xor mode, decode MSG <hex>, decrypt with key=7,
//              and reply ACK <hex-encoded encrypted echo>.
// TODO Week 3: In hybrid mode, first receive KEY <RSA ciphertext>,
//              decrypt it with (d=27,n=55), send READY, then use that key.
// TODO: Accept multiple messages until QUIT; reply BYE and exit.
// You may add helper functions and change the structure of this file.
int main(int argc, char** argv) {
    (void)argc; (void)argv;
    std::cerr << "TODO: implement server.cpp\n";
    return 1;
}

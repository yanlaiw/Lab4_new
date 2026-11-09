# CSCE 313 — Lab 4: Encrypted TCP Messenger

**Due: Dec 2, 2026| 100 points**

Build a single-client TCP echo messenger on `127.0.0.1`, then add educational XOR encryption and toy RSA key exchange. **The cryptography in this lab is intentionally insecure and is for classroom learning only.**

## Build and run

```bash
make
./server 8080 plain       # terminal 1
./client 127.0.0.1 8080 plain  # terminal 2
# type hello, another message, quit
make test
```

Modes: `plain` (Week 1), `xor` (Week 2), `hybrid` (Week 3). Both processes must use the same mode. Start the server first; it accepts **one** client and then exits. Run on Linux or WSL with g++ and Python 3. No OpenSSL or external Python packages.

## Provided vs student code

You implement **client.cpp, server.cpp, crypto.cpp**. `wire.cpp/.h`, `crypto.h`, `Makefile`, tests are provided. The starter compiles but does not implement the lab. Do not modify the provided interface/protocol. You may add helpers in your three source files.

## Protocol (each record is one newline-terminated line)

- Plain: client sends `TEXT hello`; server replies `ACK hello`.
- XOR: client sends `MSG <HEX>`; server replies `ACK <HEX>`. HEX encodes bytes XORed with key **7**. `hexEncode`/`hexDecode` are provided.
- Hybrid: client first sends `KEY <INTEGER>`, where INTEGER is the RSA encryption of key 7 using public key `(e=3,n=55)`; server decrypts with `(d=27,n=55)` and replies `READY`. Subsequent messages follow XOR mode using the recovered key.
- In every mode: client input `quit` sends `QUIT`; server responds `BYE`; client prints `BYE`; both exit cleanly.
- Client prints `ACK: <plaintext>` for each reply. Keep message content unchanged (case/spaces). Maximum message length: **1000 characters**. All tests use ASCII messages without embedded newlines.
- Server binds **127.0.0.1**, not a public network interface. One client only; no threads, GUI, or database.

## Week 1 — TCP (suggested 2–3 h)

Implement socket setup, `bind/listen/accept` server, `connect` client, repeated plaintext messages, `quit` handling, errors and close. `sendLine` and `readLine` are provided; these handle TCP partial sends and newline framing.

## Week 2 — Symmetric encryption (suggested 2–3 h)

Implement `xorCipher()` (same function encrypts/decrypts). Add `xor` mode using fixed educational key 7. Encrypt *before* transmission, hex-encode ciphertext, decode/decrypt on receipt. Verify `ACK` restores plaintext.

## Week 3 — RSA + hybrid mode (suggested 2–3 h)

Implement `modPow()` using integer repeated squaring; implement `rsaEncrypt()` and `rsaDecrypt()` as wrappers. Use the supplied toy RSA public/private parameters (no key generation). Implement initial `KEY`/`READY` exchange and reuse Week 2's XOR messenger. Do not use `std::pow` for modular exponentiation.

## Milestone checks

1. `./server 8080 plain` + client: `hello`, `test`, `quit` => `ACK: hello`, `ACK: test`, `BYE`.
2. Repeat in `xor` mode; verify same visible responses and encrypted wire format.
3. Repeat in `hybrid` mode; verify RSA key exchange, encrypted messages, graceful exit.

## Rubric (100 points)

- TCP server 20; TCP client 20; repeated message transmission 15; XOR 15; RSA 15; hybrid integration 10; error handling 5.

## Submission

Submit your completed source code directly to Canvas. Upload `client.cpp`, `server.cpp`, and `crypto.cpp` (or one ZIP containing these three files). Do not upload executables or object files. Run `make clean && make && make test` before submission.

## Academic integrity and scope

Follow your course collaboration/AI policy. Explain code you submit. This is not production cryptography: reused XOR keys and tiny, unpadded RSA are insecure. Do not use this lab to protect real data.

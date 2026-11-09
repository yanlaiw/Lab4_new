CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -O2
all: server client
server: server.cpp crypto.cpp wire.cpp crypto.h wire.h
	$(CXX) $(CXXFLAGS) -o $@ server.cpp crypto.cpp wire.cpp
client: client.cpp crypto.cpp wire.cpp crypto.h wire.h
	$(CXX) $(CXXFLAGS) -o $@ client.cpp crypto.cpp wire.cpp
test: all
	python3 tests/test_lab4.py
clean:
	rm -f server client
.PHONY: all test clean

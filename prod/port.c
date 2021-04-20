
unsigned char* port0Address= 0xff3927;

unsigned char* getPortAddress(int portNumber) {
    return port0Address + portNumber;
}

void setPortAddress0(unsigned char* address) {
    port0Address = address;
}
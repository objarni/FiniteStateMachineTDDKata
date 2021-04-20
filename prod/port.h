#pragma once

// *** Use this in your production code ***
// Get memory mapped port adress.
// The returned pointer can be used for both
// reading and writing to the port.
unsigned char* getPortAddress(int portNumber);

// *** Use this in your tests ***
// Function to modify the memory mapped address
// of the ports.
// The ports are mapped in-order, and calling
// this function specifies the memory offset
// of port 0.
//
// 0, 1, 2, ...
// ^
//
void setPortAddress0(unsigned char* address);

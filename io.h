#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

// Sends the given data to the given I/O port.
void outb(unsigned short port, unsigned char data);

// Read a byte from an I/O port.
unsigned char inb(unsigned short port);

#endif
#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

// Sends the given data to the given I/O port.
void outb(uint8_t port, uint8_t data);

// Read a byte from an I/O port.
unsigned char inb(uint8_t port);

#endif
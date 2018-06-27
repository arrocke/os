#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

#include "stdint.h"

#define COM1 0x3F8
#define COM2 0x2F8

// Initializes a serial port.
void serial_init(uint16_t com);

// Prints a byte to the framebuffer.
void serial_print_byte(uint16_t com, uint8_t c);

// Prints a string to the framebuffer.
void serial_print_string(uint16_t com, char const *str);

#endif 
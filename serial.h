#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

#define COM1 0x3F8
#define COM2 0x2F8

// Initializes a serial port.
void serial_init(unsigned int com);

// Prints a byte to the framebuffer.
void serial_print_byte(unsigned int com, char c);

// Prints a string to the framebuffer.
void serial_print_string(unsigned int com, char const *str);

#endif 
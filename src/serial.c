#include "serial.h"
#include "io.h"

// I/O ports
#define DATA_PORT(base)             (base)
#define FIFO_CONTROL_PORT(base)     (base + 2)
#define LINE_CONTROL_PORT(base)     (base + 3)
#define MODEM_CONTROL_PORT(base)    (base + 4)
#define LINE_STATUS_PORT(base)      (base + 5)
#define DLAB_LOW_BYTE_PORT(base)    (base)
#define DLAB_HIGH_BYTE_PORT(base)   (base + 1)

// I/O commands
#define ENABLE_DLAB 0x80
#define BAUD_RATE_DIVISOR 0x03

// Checks whether a transmit FIFO is empty for the given COM port.
static int is_transmit_fifo_empty(uint16_t com)
{
    /* 0x20 = bit 5: 1 if XMIT fifo is empty */
    return inb(LINE_STATUS_PORT(com)) & 0x20;
}

// Initializes the configuration for a COM port.
void serial_init(uint16_t com) {
    // Write the baud rate divisor.
    outb(LINE_CONTROL_PORT(com), ENABLE_DLAB);
    outb(DLAB_LOW_BYTE_PORT(com), BAUD_RATE_DIVISOR & 0x00FF);
    outb(DLAB_HIGH_BYTE_PORT(com), (BAUD_RATE_DIVISOR & 0xFF00) >> 8);
    // Configure the serial line.
    outb(LINE_CONTROL_PORT(com), 0x03);
    // Configure the buffers.
    outb(FIFO_CONTROL_PORT(com), 0xC7);
    // Configure the modem.
    outb(MODEM_CONTROL_PORT(com), 0x03);
}

// Prints a byte to the given COM port once the transmit FIFO is empty.
void serial_print_byte(uint16_t com, uint8_t c) {
    while (!is_transmit_fifo_empty(com)) { }
    outb(DATA_PORT(com), c);
}

// Prints a string to the given COM port.
void serial_print_string(uint16_t com, char const *str) {
    while (*str != '\0') {
        serial_print_byte(com, *str++);
    }
}
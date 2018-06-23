#include "fb.h"
#include "serial.h"

int kmain() {
    fb_init();
    serial_init(COM1);

    fb_print_string("row1");
    fb_set_cursor(1, 0);
    fb_print_string("row2");
    fb_set_cursor(24, 79);
    fb_print_string(" row25");

    serial_print_string(COM1, "test");

    return 0xDEADDEAD;
}
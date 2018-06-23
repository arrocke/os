#include "fb.h"

int kmain() {
    fb_init();
    fb_print_string("test");
    fb_set_cursor(10,20);

    return 0xDEADDEAD;
}
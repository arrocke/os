#include "fb.h"

int kmain() {
    fb_init();
    fb_print_string("row1");
    fb_set_cursor(1, 0);
    fb_print_string("row2");
    fb_set_cursor(24, 79);
    fb_set_color(FB_LTGREEN, FB_RED);
    fb_print_string(" row25");

    return 0xDEADDEAD;
}
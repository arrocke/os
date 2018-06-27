#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

#include "stdint.h"

// The size of the framebuffer
#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25

// Framebuffer colors
enum FB_Colors {
    FB_BLACK = 0,
    FB_BLUE,
    FB_GREEN,
    FB_CYAN,
    FB_RED,
    FB_MAGENTA,
    FB_BROWN,
    FB_LTGREY,
    FB_DKGREY,
    FB_LTBLUE,
    FB_LTGREEN,
    FB_LTCYAN,
    FB_LTRED,
    FB_LTMAGENTA,
    FB_LTBROWN,
    FB_WHITE
};

// Prints a null terminated string to the framebuffer.
void fb_print_string(char const *buf);

// Prints a byte to the framebuffer.
void fb_print_byte(uint8_t i);

// Clears the framebuffer.
void fb_clear();

// Sets the cursor position of the framebuffer.
void fb_set_cursor(uint16_t row, uint16_t col);

// Initializes the framebuffer.
void fb_init();

#endif
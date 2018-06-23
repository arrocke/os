#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

// Framebuffer colors
#define FB_BLACK 0x0
#define FB_BLUE 0x1
#define FB_GREEN 0x2
#define FB_CYAN 0x3
#define FB_RED 0x4
#define FB_MAGENTA 0x5
#define FB_BROWN 0x6
#define FB_LTGREY 0x7
#define FB_DKGREY 0x8
#define FB_LTBLUE 0x9
#define FB_LTGREEN 0xA
#define FB_LTCYAN 0xB
#define FB_LTRED 0xC
#define FB_LTMAGENTA 0xD
#define FB_LTBROWN 0xE
#define FB_WHITE 0xF

// Prints a null terminated string to the framebuffer.
void fb_print_string(char const *buf);

// Prints a byte to the framebuffer.
void fb_print_byte(char i);

// Clears the framebuffer.
void fb_clear();

// Sets the cursor position of the framebuffer.
void fb_set_cursor(unsigned int row, unsigned int col);

// Initializes the framebuffer.
void fb_init();

#endif
#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

void fb_print_string(char const *buf);

void fb_print_byte(char i);

void fb_clear();

void fb_set_cursor(unsigned int row, unsigned int col);

void fb_init();

#endif
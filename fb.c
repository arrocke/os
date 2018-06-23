#include "io.h"
#include "fb.h"

// The memory address of the framebuffer
#define FB_MEMORY 0x000B8000

// The size of the framebuffer
#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25

// The I/O ports
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

// The I/O port commands
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

// Framebuffer colors
#define BLACK_ON_WHITE 0x0F

static char *fb = (char *) FB_MEMORY;
static unsigned int cursor_pos = 0;

// Writes a character to the framebuffer at the given index.
static void write_cell(unsigned int i, char c) {
    fb[2 * i] = c;
    fb[2 * i + 1] = BLACK_ON_WHITE;
}

static void write_at(unsigned int row, unsigned int col, char c) {
    write_cell(FB_NUM_COLS * row + col, c);
}

// Sets the cursor location in the framebuffer.
void set_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
    cursor_pos = pos;
}

// Writes a character at the cursor position.
void fb_print_byte(char c) {
    write_cell(cursor_pos, c);
    set_cursor(cursor_pos + 1);
}

// Writes a string at the cursor position.
void fb_print_string(char const *str) {
    while(*str != '\0')
        fb_print_byte(*str++);
}

void fb_set_cursor(unsigned int row, unsigned col) {
    set_cursor(FB_NUM_COLS * row + col);
}

void fb_clear() {
    unsigned int i, j;
    for (i = 0; i < FB_NUM_ROWS; i++) {
        for (j = 0; j < FB_NUM_COLS; j++) {
            write_at(i, j, ' ');
        }
    }
    set_cursor(0);
}

// Initializes the framebuffer.
void fb_init() {
    fb_clear();
}
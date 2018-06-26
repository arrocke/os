#include "io.h"
#include "fb.h"
#include "log.h"

// The memory address of the framebuffer
#define FB_MEMORY 0x000B8000
// The length of the framebuffer
#define FB_SIZE (FB_NUM_COLS * FB_NUM_ROWS)
// The I/O ports
#define COMMAND_PORT         0x3D4
#define DATA_PORT            0x3D5
// The I/O port commands
#define HIGH_BYTE    14
#define LOW_BYTE     15
// The default color
#define DEFAULT_COLOR CREATE_COLOR(FB_GREEN, FB_BLACK)
// Macros
#define CREATE_COLOR(fg, bg) (((bg & 0x0F) << 4) | (fg & 0x0F))
#define POS_TO_ADDR(row, col) (FB_NUM_COLS * row + col)

// Internal framebuffer data
static char *fb = (char *) FB_MEMORY;
static unsigned int cursor_pos;
static char color;

// Writes a character to the framebuffer at the given position with the set colors.
// This does not move the cursor
static void write_index(unsigned int i, char c) {
    fb[2 * i] = c;
    fb[2 * i + 1] = color;
}

// Writes a character at the given row and column of the framebuffer.
static void write_pos(unsigned int row, unsigned int col, char c) {
    write_index(POS_TO_ADDR(row, col), c);
}

// Sets the framebuffer cursor to the index.
static void set_cursor(unsigned int pos) {
    outb(COMMAND_PORT, HIGH_BYTE);
    outb(DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(COMMAND_PORT, LOW_BYTE);
    outb(DATA_PORT,    pos & 0x00FF);
    cursor_pos = pos;
}

// Scrolls the screen to make room for a new row.
static void scroll() {
    unsigned int i, j, k, m;
    for (i = 1; i < FB_NUM_ROWS; i++) {
        for (j = 0; j < FB_NUM_COLS; j++) {
            k = 2 * POS_TO_ADDR(i, j);
            m = k - (2 * FB_NUM_COLS);
            fb[m] = fb[k];
            fb[m + 1] = fb[k + 1];
        }
    }
    for (j = 0; j < FB_NUM_COLS; j ++) {
        write_pos(FB_NUM_ROWS - 1, j, ' ');
    }
    fb_set_cursor(FB_NUM_ROWS - 1, 0);
}

// Clears the framebuffer and moves the cursor back to the top corner.
void fb_clear() {
    unsigned int i, j;
    for (i = 0; i < FB_NUM_ROWS; i++) {
        for (j = 0; j < FB_NUM_COLS; j++) {
            write_pos(i, j, ' ');
        }
    }
    set_cursor(0);
}

// Initializes the framebuffer with its default colors.
void fb_init() {
    color = DEFAULT_COLOR;
    fb_clear();
    log_println("VGA framebuffer initialized.", LOG_INFO);
}

// Writes a byte to the framebuffer and moves the cursor.
void fb_print_byte(char b) {
    write_index(cursor_pos, b);
    set_cursor(cursor_pos + 1);
    if (cursor_pos >= FB_SIZE) {
        scroll();
    }
}

// Writes a null terminated string to the framebuffer.
void fb_print_string(char const *str) {
    while (*str != '\0') {
        fb_print_byte(*str++);
    }
}

// Sets the cursor to a row and column.
void fb_set_cursor(unsigned int row, unsigned col) {
    set_cursor(POS_TO_ADDR(row, col));
}
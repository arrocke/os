#include "fb.h"
#include "serial.h"

int kmain() {
    fb_init();
    serial_init(COM1);

    return 0xDEADDEAD;
}
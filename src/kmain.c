#include "fb.h"
#include "gdt.h"
#include "log.h"

int kmain() {
    log_init();
    gdt_init();
    fb_init();

    return 0xDEADDEAD;
}
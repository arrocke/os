#include "fb.h"
#include "log.h"

int kmain() {
    log_init();
    fb_init();

    return 0xDEADDEAD;
}
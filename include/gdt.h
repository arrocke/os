#ifndef INCLUDE_GTD_H
#define INCLUDE_GTD_H

#include "stdint.h"

// GDT privilege levels.
enum GDT_PL {
    PL0 = 0,
    PL1,
    PL2,
    PL3
};

// Initializes the GTD table.
void gdt_init();

#endif
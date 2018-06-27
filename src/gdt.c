#include "gdt.h"
#include "log.h"

// A GDT segment base address and size limit.
#define SEGMENT_BASE    0
#define SEGMENT_LIMIT   0xFFFF

// The size of the GDT table.
#define GDT_NUM_ENTRIES 3

// GDT segment access types.
#define CODE_RX_TYPE    0xA
#define DATA_RW_TYPE    0x2

struct gdt_entry {
    uint16_t limit_low;     // The lower 16 bits of the limit
    uint16_t base_low;      // The lower 16 bits of the base
    uint8_t  base_mid;      // The next 8 bits of the base
    uint8_t  access;        // Contains access flags
    uint8_t  granularity;   // Specify granularity, and 4 bits of limit
    uint8_t  base_high;     // The last 8 bits of the base
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
    uint16_t limit;          // Size of gdt table in bytes.
    uint32_t base;           // Address to the first gdt entry.
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

// GDT table of entries.
gdt_entry_t gdt_table[GDT_NUM_ENTRIES];

// Assembly function to load and set the GDT table and pointers.
void gdt_load(uint32_t);

// Creates a GDT entry.
static void gdt_create_entry(uint32_t n, uint8_t pl, uint8_t type)
{
    // Set the GDT entry base address.
    gdt_table[n].base_low = (SEGMENT_BASE & 0xFFFF);        // The first 16 bits.
    gdt_table[n].base_mid = (SEGMENT_BASE >> 16) & 0xFF;    // The second 8 bits.
    gdt_table[n].base_high = (SEGMENT_BASE >> 24) & 0xFF;   // The last 8 bits.


    // Set the GDT entry size limit.
    gdt_table[n].limit_low = (SEGMENT_LIMIT & 0xFFFF);

    // Set the granularty flags.
    gdt_table[n].granularity  |=
        (0x01 << 7) |                       // 1 = segment unit of 4kB.
        (0x01 << 6) |                       // 1 = work with 32 bits at a time.
        ((SEGMENT_LIMIT >> 16) & 0xFF);     // Last 4 bits of segment size limit.

    // Set the access flags.
    gdt_table[n].access =
        (0x01 << 7) |                       // 1 = segment is in memory
        ((pl & 0x03) << 5) |                // set the priviledge level
        (0x01 << 4) |                       // descriptor type: 1 = code or data, 0 = system
        (type & 0x0F);                      // set the access type
}


void gdt_init() {
    // Initialize the gdt_ptr to the gdt_table location and size.
    gdt_ptr_t gdt_ptr;
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_NUM_ENTRIES;
    gdt_ptr.base = (uint32_t)&gdt_table;

    // Create NULL segement.
    gdt_create_entry(0, 0, 0);
    // Create code segment.
    gdt_create_entry(1, PL0, CODE_RX_TYPE);
    // Create data segment.
    gdt_create_entry(2, PL0, DATA_RW_TYPE);

    // Set GDT table.
    gdt_load((uint32_t)&gdt_ptr);

    log_println("GDT table initialized.", LOG_INFO);
}
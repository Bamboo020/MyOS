#ifndef GDT_H
#define GDT_H

struct GDTEntry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

static_assert(sizeof(GDTEntry) == 8);

/**
 * Initializes the Global Descriptor Table
 * and loads it into the CPU.
 */
void gdt_init();

#endif // GDT_H
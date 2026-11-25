#ifndef GDT_FLUSH_H
#define GDT_FLUSH_H

struct GDTPointer {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

static_assert(sizeof(GDTPointer) == 6);

extern "C" void gdt_flush(const GDTPointer* ptr);

#endif
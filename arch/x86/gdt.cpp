#include "gdt_flush.h"
#include "gdt.h"

#define GDT_ENTRY_COUNT 5

/* The GDT itself */
static GDTEntry gdt_entries[GDT_ENTRY_COUNT];

/* The pointer to the GDT, which is loaded into the GDTR register */
static GDTPointer gdt_ptr;

/**
 * Configures an individual GDT segment descriptor.
 *
 * @param index       The index of the GDT entry.
 * @param base        The base address of the segment.
 * @param limit       The encoded segment limit.
 * @param access      The access byte of the segment.
 * @param granularity The granularity and control flags.
 */
static void gdt_set_entry(
    unsigned int index,
    unsigned int base,
    unsigned int limit,
    unsigned char access,
    unsigned char granularity)
{
    /* Set the segment base address */
    gdt_entries[index].base_low = base & 0xFFFF;

    gdt_entries[index].base_middle = (base >> 16) & 0xFF;

    gdt_entries[index].base_high = (base >> 24) & 0xFF;

    /* Set the segment limit */
    gdt_entries[index].limit_low = limit & 0xFFFF;

    gdt_entries[index].granularity = (limit >> 16) & 0x0F;

    /* Set granularity and control flags */
    gdt_entries[index].granularity |= granularity & 0xF0;

    /* Set access permissions */
    gdt_entries[index].access = access;
}

void gdt_init()
{
    /* Configure the GDT pointer */
    gdt_ptr.limit = sizeof(gdt_entries) - 1;

    gdt_ptr.base =
        reinterpret_cast<unsigned int>(&gdt_entries[0]);

    /* Null descriptor */
    gdt_set_entry(0, 0, 0, 0, 0);

    /* Kernel code segment */
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);

    /* Kernel data segment */
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

    /* User code segment */
    gdt_set_entry(3, 0, 0xFFFFF, 0xFA, 0xCF);

    /* User data segment */
    gdt_set_entry(4, 0, 0xFFFFF, 0xF2, 0xCF);

    /* Load GDT and reload segment registers */
    gdt_flush(&gdt_ptr);
}

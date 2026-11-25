#include "drivers/vga/framebuffer.h"
#include "serial/serial.h"
#include "arch/x86/gdt.h"

extern "C" void kernel_main()
{
    /* Initialize COM1 */
    serial_init(SERIAL_COM1_BASE);

    serial_write(
        SERIAL_COM1_BASE,
        "Initializing GDT...\n"
    );

    /* Initialize GDT */
    gdt_init();

    /* Test serial output */
    serial_write(
        SERIAL_COM1_BASE,
        "GDT initialized successfully!\n"
    );

    /* Test framebuffer output */
    fb_write("GDT initialized successfully!");

    while (true) {
        asm volatile("hlt");
    }
}


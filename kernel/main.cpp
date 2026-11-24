#include "drivers/vga/cursor.h"
#include "drivers/vga/framebuffer.h"
#include "serial/serial.h"

extern "C" void kernel_main()
{
    // Initialize COM1
    serial_init(SERIAL_COM1_BASE);

    // Send text through serial port
    serial_write(
        SERIAL_COM1_BASE,
        "Hello from C++ kernel!\n"
    );

    volatile unsigned short* video_memory =
    reinterpret_cast<volatile unsigned short*>(0xB8000);

    video_memory[0] = 0x0F41;  // A
    video_memory[1] = 0x0F42;  // B
    video_memory[2] = 0x0F43;  // C
    
    enable_cursor();

    move_cursor(0, 3);

    while (true) {
        asm volatile("hlt");
    }
}


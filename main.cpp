#include "output/mmio.h"
#include "output/io.h"

volatile unsigned short* video_memory =
    reinterpret_cast<volatile unsigned short*>(0xB8000);

extern "C" void kernel_main()
{
    video_memory[0] = 0x0F41;
    video_memory[1] = 0x0F42;
    video_memory[2] = 0x0F43;

    move_cursor(1, 0);

    while (true) {
        asm volatile("hlt");
    }
}


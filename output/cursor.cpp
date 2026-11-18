#include "io.h"

void enable_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x0E);

    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x0F);
}


void move_cursor(unsigned short row, unsigned short col) {
    unsigned short pos = row * 80 + col;

    outb(0x3D4, 14);
    outb(0x3D5, ((pos >> 8) & 0x00FF));
    outb(0x3D4, 15);
    outb(0x3D5, (pos & 0x00FF));
}
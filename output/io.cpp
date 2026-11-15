#include "io.h"

void move_cursor(unsigned short row, unsigned short col) {
    unsigned short pos = row * 80 + col;

    outb(0x3D4, 14);
    outb(0x3D5, ((pos >> 8) & 0xFF));
    outb(0x3D4, 15);
    outb(0x3D5, (pos & 0xFF));
}
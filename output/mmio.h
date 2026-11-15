char *fb = (char *)0x000B8000;

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_call(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = (bg & 0x0F) << 4 | (fg & 0x0F);
}

void put_char(unsigned int row, unsigned int col, char c, unsigned char fg, unsigned char bg) {
    unsigned int index = (row * 80 + col) * 2;
    fb_write_call(index, c, fg, bg);
}
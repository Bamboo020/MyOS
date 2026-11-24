#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/**
 * Writes a character to a specified position on the screen.
 *
 * @param row The row position (0-24).
 * @param col The column position (0-79).
 * @param c   The character to display.
 * @param fg  The foreground (text) color.
 * @param bg  The background color.
 */
void put_char(unsigned int row, unsigned int col, char c, unsigned char fg, unsigned char bg);

/** fb_write:
 *  Writes a null-terminated string to the framebuffer. The string is written
 *  starting from the top-left corner of the screen. If the string contains
 *  newline characters, they will be handled appropriately. The cursor will be
 *  moved to the position after the last character written.
 *
 *  @param str  The null-terminated string to write
 */
void fb_write(const char* str);

#endif
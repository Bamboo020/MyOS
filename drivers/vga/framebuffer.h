/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_call(unsigned int i, char c, unsigned char fg, unsigned char bg);

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
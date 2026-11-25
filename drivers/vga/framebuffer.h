#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

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
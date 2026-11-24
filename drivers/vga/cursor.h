#ifndef _CURSOR_H
#define _CURSOR_H

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param row The new row of the cursor
 *  @param col The new column of the cursor
 */
void move_cursor(unsigned short row, unsigned short col);

/** enable_cursor:
 *  Enables the cursor of the framebuffer
 */
void enable_cursor();

#endif

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
extern "C" void outb(unsigned short port, unsigned char data);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param row The new row of the cursor
 *  @param col The new column of the cursor
 */
void move_cursor(unsigned short row, unsigned short col);

#endif
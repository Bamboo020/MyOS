#ifndef SERIAL_H
#define SERIAL_H

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */
#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */

#define SERIAL_DATA_PORT(base)           (base)
#define SERIAL_FIFO_COMMAND_PORT(base)   (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)   (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)  (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)    (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/** serial_init:
 *  Initializes the given serial port. The baud rate is set to 38400 bits/s,
 *  the line is set to have a data length of 8 bits, no parity bits, one stop
 *  bit and break control disabled. The FIFO is enabled, clear the transmit
 *  and receive FIFO queues, and an interrupt trigger level of 14 bytes is
 *  set. The Data Terminal Ready and Request to Send lines are enabled, and
 *  the auxilliary output #2 is set high, which is required for interrupts to
 *  work.
 *
 *  @param com  The serial port to initialize
 */
void serial_init(unsigned short com);

/** serial_write:
 *  Writes a string of characters to the given serial port.
 *
 *  @param com  The serial port to write to
 *  @param str  The string to write
 */
void serial_write(unsigned short com, const char *str);

#endif
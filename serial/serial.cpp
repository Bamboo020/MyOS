#include "serial.h"
#include "arch/x86/io.h"

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    /* Enable DLAB */
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

    /* Send the lower 8 bits */
    outb(SERIAL_DATA_PORT(com), divisor & 0xFF);

    /* Send the higher 8 bits */
    outb(SERIAL_DATA_PORT(com) + 1, (divisor >> 8) & 0xFF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_fifo:
 *  Configures the FIFO of the given serial port. The FIFO is enabled, clear
 *  the transmit and receive FIFO queues, and an interrupt trigger level of
 *  14 bytes is set.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_fifo(unsigned short com)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem of the given serial port. The Data Terminal Ready
 *  and Request to Send lines are enabled, and the auxilliary output #2 is
 *  set high, which is required for interrupts to work.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_modem(unsigned short com)
{
    /* Bit:      7  6  5   4   3    2    1    0
     * Content:  r  r  af  lb  ao2  ao1  rts  dtr
     * Value:    0  0  0   0   0    0    1    1 = 0x03
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not.
 *
 *  @param com  The serial port to check
 *  @return     True if the transmit FIFO queue is empty, false otherwise
 */
int serial_is_transmit_fifo_empty(unsigned short com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_init(unsigned short com)
{
    /* Disable UART interrupts */
    outb(com + 1, 0x00);

    serial_configure_baud_rate(com, 3);
    serial_configure_line(com);
    serial_configure_fifo(com);
    serial_configure_modem(com);
}

/** serial_write_char:
 *  Writes a single character to the given serial port.
 *
 *  @param com  The serial port to write to
 *  @param c    The character to write
 */
void serial_write_char(unsigned short com, char c)
{
    while (!serial_is_transmit_fifo_empty(com)) {
        /* Wait */
    }

    outb(SERIAL_DATA_PORT(com),
         static_cast<unsigned char>(c));
}

void serial_write(unsigned short com, const char *str)
{
    while (*str != '\0') {
        serial_write_char(com, *str);
        ++str;
    }
}
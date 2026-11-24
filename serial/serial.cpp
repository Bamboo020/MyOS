#include "serial.h"
#include "arch/x86/io.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    // Enable DLAB
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);

    // Send the lower 8 bits
    outb(SERIAL_DATA_PORT(com), divisor & 0xFF);

    // Send the higher 8 bits
    outb(SERIAL_DATA_PORT(com) + 1, (divisor >> 8) & 0xFF);
}

void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo(unsigned short com)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
    /* Bit:      7  6  5   4   3    2    1    0
     * Content:  r  r  af  lb  ao2  ao1  rts  dtr
     * Value:    0  0  0   0   0    0    1    1 = 0x03
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_init(unsigned short com)
{
    // Disable UART interrupts
    outb(com + 1, 0x00);

    serial_configure_baud_rate(com, 3);
    serial_configure_line(com);
    serial_configure_fifo(com);
    serial_configure_modem(com);
}

void serial_write_char(unsigned short com, char c)
{
    while (!serial_is_transmit_fifo_empty(com)) {
        // Wait
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
#include "framebuffer.h"
#include "cursor.h"

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
void fb_write_call(
    unsigned int i, 
    char c, 
    unsigned char fg, 
    unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = (bg & 0x0F) << 4 | (fg & 0x0F);
}

/**
 * Writes a character to a specified position on the screen.
 *
 * @param row The row position (0-24).
 * @param col The column position (0-79).
 * @param c   The character to display.
 * @param fg  The foreground (text) color.
 * @param bg  The background color.
 */
void put_char(
    unsigned int row, 
    unsigned int col, 
    char c, 
    unsigned char fg, 
    unsigned char bg) 
{
    unsigned int index = (row * 80 + col) * 2;
    fb_write_call(index, c, fg, bg);
}

void fb_write(const char* str)
{
    unsigned int row = 0;
    unsigned int col = 0;

    while (*str != '\0')
    {
        if (*str == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            put_char(row, col, *str, 15, 0);
            col++;

            if (col >= 80)
            {
                col = 0;
                row++;
            }
        }

        if (row >= 25)
        {
            break;
        }

        str++;
    }

    enable_cursor();

    move_cursor(row, col);
}
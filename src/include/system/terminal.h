
#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <system/vga.h>

namespace nstd
{
    class terminal
    {
    private:
        // The terminal's row.
        size_t terminal_row;
        // The terminal's column.
        size_t terminal_column;
        // The terminal's color.
        uint8_t terminal_color;
        // The terminal's buffer.
        uint16_t *terminal_buffer;

    public:
        terminal()
        {
            initialize();
        }

        // Gets the length of a string.
        size_t strlen(const char *str);

        // Gets the length of a buffer.
        size_t buflen(const uint16_t *buf);

        // Initializes the terminal.
        void initialize(void);

        // Sets the terminal's color.
        void set_color(uint8_t color);

        // Puts an entry at a specific location.
        void put_entryat(char c, uint8_t color, size_t x, size_t y);

        // Clears a line.
        void clear_line(size_t y);

        // Shifts the terminal's buffer.
        void shift_rowsup();

        // Clears the current line.
        void clear_currentline();

        // Clears the terminal's buffer.
        void clear_buffer();

        // Writes a character to the terminal.
        void put_char(char c);

        // Write a string given string and size
        void write(const char *data, size_t size);

        // Writes a string to the terminal.
        void write_string(const char *data);

        // Writes a centered string to the terminal.
        void write_centeredstring(const char *data);

        // Prints the splash screen.
        void print_splash();

        // Getters
        size_t get_row();
        size_t get_column();
        uint8_t get_color();
        uint16_t *get_buffer();
    };
}

#endif // _TERMINAL_H_


#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <vga.h>

size_t strlen(const char *str);
size_t buflen(const uint16_t *buf);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_clearline(size_t y);
void terminal_clearcurrentline();
void terminal_clearscreen();
void shift_terminalrowsup();
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
size_t *get_terminal_row();
size_t *get_terminal_column();
uint8_t *get_terminal_color();
uint16_t *get_terminal_buffer();
void terminal_writecenteredstring(char *data);

#endif // _TERMINAL_H_

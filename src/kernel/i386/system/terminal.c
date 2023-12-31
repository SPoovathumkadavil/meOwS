
#include "system/terminal.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

size_t buflen(const uint16_t *buf)
{
	size_t len = 0;
	while (buf[len])
		len++;
	return len;
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t *)0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_clearline(size_t y)
{
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
	terminal_column = 0;
}

void terminal_clearcurrentline()
{
	terminal_clearline(terminal_row);
}

void terminal_clearbuffer()
{
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		terminal_clearline(y);
	}
}

void shift_terminalrowsup()
{
	// Index Calc = y * VGA_WIDTH + x
	for (size_t i = 0; i < VGA_HEIGHT * VGA_WIDTH; i += VGA_WIDTH)
	{
		for (size_t j = 0; j < VGA_WIDTH; j++)
		{
			terminal_buffer[i + j] = terminal_buffer[i + j + VGA_WIDTH];
		}
	}

	terminal_clearline(VGA_HEIGHT - 1);
}

void terminal_putchar(char c)
{
	// First Increment and do checks
	if (terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;
		terminal_row++;
	}
	else if (c == '\n')
	{
		terminal_column = 0; // FIXME!!!
		terminal_row++;
		return;
	}

	if (terminal_row == VGA_HEIGHT)
	{
		shift_terminalrowsup();
		terminal_row--;
	}

	// Then Put Entry
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

	terminal_column++;
}

void terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char *data)
{
	terminal_write(data, strlen(data));
}

size_t *get_terminal_row()
{
	return &terminal_row;
}

size_t *get_terminal_column()
{
	return &terminal_column;
}

uint8_t *get_terminal_color()
{
	return &terminal_color;
}

uint16_t *get_terminal_buffer()
{
	return terminal_buffer;
}

void terminal_writecenteredstring(char *data)
{
	size_t len = strlen(data);
	if (len > VGA_WIDTH - 1)
		return;
	size_t offset = (size_t)((VGA_WIDTH / 2) - (len / 2));
	for (size_t i = 0; i < offset; i++)
		terminal_putchar(' ');
	for (size_t i = 0; i < len; i++)
		terminal_putchar(data[i]);
}

void terminal_printsplash()
{
	terminal_clearbuffer();
	terminal_setcolor(VGA_COLOR_LIGHT_RED);
	terminal_row = VGA_HEIGHT / 2 - 2;
	terminal_writecenteredstring("                 ___            ____  \n");
	terminal_writecenteredstring(" _ __ ___   ___ / _ \\__      __/ ___| \n");
	terminal_writecenteredstring("| '_ ` _ \\ / _ \\ | | \\ \\ /\\ / /\\___ \\ \n");
	terminal_writecenteredstring(" | | | | | |  __/ |_| |\\ V  V /  ___) | \n");
	terminal_writecenteredstring("|_| |_| |_|\\___|\\___/  \\_/\\_/  |____/ \n");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);
}

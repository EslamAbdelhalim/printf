#include "main.h"

unsigned int conv_c(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_percent(va_list args, buffer_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);

/**
 * conv_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_c(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	char g;
	unsigned int rt = 0;

	(void)p;
	(void)lenn;

	g = va_arg(args, int);

	rt += print_width(output, rt, flags, width);
	rt += _memcpy(output, &g, 1);
	rt += print_neg_width(output, rt, flags, width);

	return (rt);
}

/**
 * conv_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int conv_percent(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	char perc = '%';
	unsigned int rt = 0;

	(void)args;
	(void)p;
	(void)lenn;

	rt += print_width(output, rt, flags, width);
	rt += _memcpy(output, &perc, 1);
	rt += print_neg_width(output, rt, flags, width);

	return (rt);
}

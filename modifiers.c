#include "main.h"

unsigned int print_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int print_string_width(buff_t *output,
		unsigned char flags, int width, int p, int sz);
unsigned int print_neg_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width);

/**
 * print_width - Stores leading spaces to a buffer for a width modifier.
 * @output: A buff_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int rt = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0;)
			rt += _memcpy(output, &wid, 1);
	}

	return (rt);
}

/**
 * print_string_width - Stores leading spaces to a buffer for a width modifier.
 * @output: A buff_t struct containing a character array.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_string_width(buff_t *output,
		unsigned char flags, int width, int p, int sz)
{
	unsigned int rt = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (p == -1) ? sz : p;
		for (; width > 0; width--)
			rt += _memcpy(output, &wid, 1);
	}

	return (rt);
}

/**
 * print_neg_width - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buff_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_neg_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int rt = 0;
	char wid = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			rt += _memcpy(output, &wid, 1);
	}

	return (rt);
}

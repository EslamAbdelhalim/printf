#include "main.h"

unsigned int conv_sbase(buff_t *output, long int numm, char *base,
		unsigned char flags, int width, int p);
unsigned int conv_ubase(buff_t *output,
		unsigned long int numm, char *base,
		unsigned char flags, int width, int p);

/**
 * conv_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: A buff_t struct containing a character array.
 * @numm: A signed long to be converted.
 * @base: Pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_sbase(buff_t *output, long int numm, char *base,
		unsigned char flags, int width, int p)
{
	int sz;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (sz = 0; *(base + sz);)
		sz++;

	if (numm >= sz || numm <= -sz)
		ret += conv_sbase(output, numm / sz, base,
				flags, width - 1, p - 1);

	else
	{
		for (; p > 1; p--, width--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(numm < 0 ? -1 : 1) * (numm % sz)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * conv_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @numm: An unsigned long to be converted.
 * @base: Pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @p: Precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_ubase(buff_t *output, unsigned long int numm, char *base,
		unsigned char flags, int width, int p)
{
	unsigned int sz, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (sz = 0; *(base + sz);)
		sz++;

	if (numm >= sz)
		ret += conv_ubase(output, numm / sz, base,
				flags, width - 1, p - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			width -= 2;
			p -= 2;
		}
		for (; p > 1; p--, width--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(numm % sz)];
	_memcpy(output, &digit, 1);

	return (ret);
}

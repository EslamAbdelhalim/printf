#include "main.h"

unsigned int conv_di(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_b(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_u(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_o(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);

/**
 * conv_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_di(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	long int dd, co;
	unsigned int rt = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (lenn == LONG)
		dd = va_arg(args, long int);
	else
		dd = va_arg(args, int);
	if (lenn == SHORT)
		dd = (short)dd;

	/* Handle space flag */
	if (SPACE_FLAG == 1 && dd >= 0)
		rt += _memcpy(output, &space, 1);

	if (p <= 0 && NEG_FLAG == 0) /* Handle width  */
	{
		if (dd == LONG_MIN)
			count += 19;
		else
		{
			for (co = (dd < 0) ? -dd : dd; co > 0; co /= 10)
				count++;
		}
		count += (dd == 0) ? 1 : 0;
		count += (dd < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && dd >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && dd >= 0) ? 1 : 0;

		/* Handle plus flag when zero flag is active */
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && dd >= 0)
			rt += _memcpy(output, &plus, 1);
		/*Print negative sign when zero flag is active */
		if (ZERO_FLAG == 1 && dd < 0)
			rt += _memcpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
			rt += _memcpy(output, &pad, 1);
	}

	/* Print negative sign when zero flag is not active */
	if (ZERO_FLAG == 0 && dd < 0)
		rt += _memcpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && dd >= 0))
		rt += _memcpy(output, &plus, 1);

	if (!(dd == 0 && p == 0))
		rt += convert_sbase(output, dd, "0123456789",
				flags, 0, p);

	rt += print_neg_width(output, rt, flags, width);

	return (rt);
}

/**
 * conv_b - Converts an unsigned int argument to binary
 *             and stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_b(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	unsigned int numm;

	numm = va_arg(args, unsigned int);

	(void)lenn;

	return (convert_ubase(output, numm, "01", flags, width, p));
}

/**
 * conv_o - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_o(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	unsigned long int numm;
	unsigned int rt = 0;
	char zero = '0';

	if (lenn == LONG)
		numm = va_arg(args, unsigned long int);
	else
		numm = va_arg(args, unsigned int);
	if (lenn == SHORT)
		numm = (unsigned short)numm;

	if (HASH_FLAG == 1 && numm != 0)
		rt += _memcpy(output, &zero, 1);

	if (!(numm == 0 && p == 0))
		rt += convert_ubase(output, numm, "01234567",
				flags, width, p);

	rt += print_neg_width(output, rt, flags, width);

	return (rt);
}

/**
 * conv_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @p: A precision modifier.
 * @lenn: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_u(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	unsigned long int numm;
	unsigned int rt = 0;

	if (lenn == LONG)
		numm = va_arg(args, unsigned long int);
	else
		numm = va_arg(args, unsigned int);
	if (lenn == SHORT)
		numm = (unsigned short)numm;

	if (!(numm == 0 && p == 0))
		rt += convert_ubase(output, numm, "0123456789",
				flags, width, p);

	rt += print_neg_width(output, rt, flags, width);

	return (rt);
}

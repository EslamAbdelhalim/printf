#include "main.h"

unsigned int conv_c(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len);
unsigned int conv_percent(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len);
unsigned int conv_p(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len);
/**
 * conv_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @p: Precision modifier.
 * @len: A length modifier.
 * @output: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_c(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len)
{
	char g;
	unsigned int ret = 0;

	(void)p;
	(void)len;

	g = va_arg(args, int);

	ret += print_width(output, ret, flags, width);
	ret += _memcpy(output, &g, 1);
	ret += print_neg_width(output, ret, flags, width);

	return (ret);
}

/**
 * conv_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @p: Precision modifier.
 * @len: Length modifier.
 * @output: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int conv_percent(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)args;
	(void)p;
	(void)len;

	ret += print_width(output, ret, flags, width);
	ret += _memcpy(output, &percent, 1);
	ret += print_neg_width(output, ret, flags, width);

	return (ret);
}

/**
 * conv_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @p: Precision modifier.
 * @len: Length modifier.
 * @output: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_p(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += convert_ubase(output, address, "0123456789abcdef",
			flags, width, p);
	ret += print_neg_width(output, ret, flags, width);

	return (ret);
}

#include "main.h"

unsigned int conv_s(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);

/**
 * conv_s - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @p: Precision modifier.
 * @lenn: Length modifier.
 * @output: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_s(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn)
{
	char *str, *null = "(null)";
	int sz;
	unsigned int ret = 0;

	(void)flags;
	(void)lenn;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (sz = 0; *(str + sz);)
		sz++;

	ret += print_string_width(output, flags, width, p, sz);

	p = (p == -1) ? sz : p;
	while (*str != '\0' && p > 0)
	{
		ret += _memcpy(output, str, 1);
		p--;
		str++;
	}

	ret += print_neg_width(output, ret, flags, width);

	return (ret);
}

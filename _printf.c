#include "main.h"

void cleanup(va_list args, buff_t *output);
int run_printf(const char *format, va_list args, buff_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for _printf
 * @args: va_list of arguments provided to _printf
 * @output: buff_t struct
 */
void cleanup(va_list args, buff_t *output)
{
	va_end(args);
	write(1, output->start1, output->len);
	free_buffer(output);
}

/**
 * run_printf - Reads through the format string for _printf
 * @format: Character string to print - may contain directives
 * @output: A buff_t struct containing a buffer
 * @args: A va_list of arguments
 *
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list args, buff_t *output)
{
	int y, width, p, ret = 0;
	char tmmpp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buff_t *,
			unsigned char, int, int, unsigned char);

	for (y = 0; *(format + y); y++)
	{
		len = 0;
		if (*(format + y) == '%')
		{
			tmmpp = 0;
			flags = handle_flags(format + y + 1, &tmmpp);
			width = handle_width(args, format + y + tmmpp + 1, &tmmpp);
			p = handle_precision(args, format + y + tmmpp + 1,
					&tmmpp);
			len = handle_length(format + y + tmmpp + 1, &tmmpp);

			f = handle_specifiers(format + y + tmmpp + 1);
			if (f != NULL)
			{
				y += tmmpp + 1;
				ret += f(args, output, flags, width, p, len);
				continue;
			}
			else if (*(format + y + tmmpp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + y), 1);
		y += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (ret);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buff_t *output;
	va_list args;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	ret = run_printf(format, args, output);

	return (ret);
}

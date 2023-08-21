#include "main.h"

void cleanup(va_list args, buff_t *output);
int run_printf(const char *format, va_list args, buff_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - Peforms cleanup operations for _printf
 * @args: A va_list of arguments provided to _printf
 * @output: A buff_t struct
 */
void cleanup(va_list args, buff_t *output)
{
	va_end(args);
	write(1, output->start1, output->lenn);
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
	int j, width, p, rt = 0;
	char tmmpp;
	unsigned char flags, lenn;
	unsigned int (*f)(va_list, buff_t *,
			unsigned char, int, int, unsigned char);

	for (j = 0; *(format + j); j++)
	{
		lenn = 0;
		if (*(format + j) == '%')
		{
			tmmpp = 0;
			flags = handle_flags(format + j + 1, &tmmpp);
			width = handle_width(args, format + j + tmmpp + 1, &tmmpp);
			p = handle_precision(args, format + j + tmmpp + 1,
					&tmmpp);
			lenn = handle_length(format + j + tmmpp + 1, &tmmpp);

			f = handle_specifiers(format + j + tmmpp + 1);
			if (f != NULL)
			{
				j += tmmpp + 1;
				rt += f(args, output, flags, width, p, lenn);
				continue;
			}
			else if (*(format + j + tmmpp + 1) == '\0')
			{
				rt = -1;
				break;
			}
		}
		rt += _memcpy(output, (format + j), 1);
		j += (lenn != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (rt);
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
	int rt;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	rt = run_printf(format, args, output);

	return (rt);
}

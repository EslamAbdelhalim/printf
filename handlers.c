#include "main.h"

int handle_precision(va_list args, const char *modifier, char *ind);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_specifiers - Matches specifier with
 *                     a corresponding conversion function.
 * @specifier: Is a pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char)
{
	int j;
	conv_t converters[] = {
		{'c', conv_c},
		{'s', conv_s},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_percent},
		{0, NULL}
	};

	for (j = 0; converters[j].func; j++)
	{
		if (converters[j].specifier == *specifier)
			return (converters[j].func);
	}

	return (NULL);
}

#include "main.h"

unsigned char handle_flags(const char *flag, char *ind);
unsigned char handle_length(const char *modifier, char *ind);
int handle_width(va_list args, const char *modifier, char *ind);
int handle_precision(va_list args, const char *modifier, char *ind);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - Matches flags with corresponding values.
 * @flag: Pointer to a potential string of flags.
 * @ind: Index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_flags(const char *flag, char *ind)
{
	int y, x;
	unsigned char ret = 0;
	f_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (y = 0; flag[y]; y++)
	{
		for (x = 0; flags[x].flag != 0; x++)
		{
			if (flag[y] == flags[x].flag)
			{
				(*ind)++;
				if (ret == 0)
					ret = flags[x].value;
				else
					ret |= flags[x].value;
				break;
			}
		}
		if (flags[x].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - Matches length modifiers with their corresponding value.
 * @modifier: Pointer to a potential length modifier.
 * @ind: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_length(const char *modifier, char *ind)
{
	if (*modifier == 'h')
	{
		(*ind)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*ind)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: Pointer to a potential width modifier.
 * @ind: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int handle_width(va_list args, const char *modifier, char *ind)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*ind)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: Pointer to a potential precision modifier.
 * @ind: Index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int handle_precision(va_list args, const char *modifier, char *ind)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*ind)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*ind)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*ind)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @specifier: Pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char)
{
	int y;
	conv_t converters[] = {
		{'c', conv_c},
		{'s', conv_s},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_percent},
		{'b', conv_b},
		{'u', conv_u},
		{'o', conv_o},
		{'x', conv_x},
		{'X', conv_X},
		{'S', conv_S},
		{'p', conv_p},
		{'r', conv_r},
		{'R', conv_R},
		{0, NULL}
	};

	for (y = 0; converters[y].func; y++)
	{
		if (converters[y].specifier == *specifier)
			return (converters[y].func);
	}

	return (NULL);
}

#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buff_s - A new type to defining buffer struct
 * @buff: A pointer to a character array
 * @star1t: A pointer to the start of buffer
 * @lenn: The length of the string stored in buffer
 */
typedef struct buff_s
{
	char *buff;
	char *start1;
	unsigned int lenn;
} buff_t;

/**
 * struct conv_s - A new type defining converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
*/
typedef struct conv_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buff_t *,
			unsigned char, int, int, unsigned char);
} conv_t;

/**
 * struct f_s - A new type defining flags struct.
 * @f: A character representing flag.
 * @value: The integer value of the flag.
*/
typedef struct f_s
{
	unsigned char f;
	unsigned char value;
} f_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int conv_c(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_s(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_di(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int conv_percent(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int convert_b(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int convert_u(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);
unsigned int convert_o(va_list args, buff_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);

/* Handlers */
unsigned char handle_flags(const char *flags, char *ind);
unsigned char handle_length(const char *modifier, char *ind);
int handle_width(va_list args, const char *modifier, char *ind);
int handle_precision(va_list args, const char *modifier, char *ind);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int print_string_width(buff_t *output,
		unsigned char flags, int width, int p, int sz);
unsigned int print_neg_width(buff_t *output, unsigned int printed,
		unsigned char flags, int width);

/* Helper Functions */
buff_t *init_buffer(void);
void free_buffer(buff_t *output);
unsigned int _memcpy(buff_t *output, const char *src, unsigned int k);
unsigned int convert_sbase(buff_t *output, long int numm, char *base,
		unsigned char flags, int width, int p);
unsigned int convert_ubase(buff_t *output, unsigned long int numm, char *base,
		unsigned char flags, int width, int p);

#endif

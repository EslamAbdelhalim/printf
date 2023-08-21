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
 * @spec: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
*/
typedef struct conv_s
{
	unsigned char spec;
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
unsigned int conv_percent(va_list args, buffer_t *output,
		unsigned char flags, int width, int p, unsigned char lenn);

/* Handlers */
unsigned int (*handle_specifiers(const char *spec))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/* Helper Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

#endif

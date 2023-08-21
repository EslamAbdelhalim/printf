#include "main.h"

unsigned int _memcpy(buff_t *output, const char *src, unsigned int k);
void free_buffer(buff_t *output);
buff_t *init_buffer(void);

/**
 * _memcpy - Copies n bytes from memory area src to
 *           the buffer contained in a buff_t struct.
 * @output: A buffer_t struct.
 * @src: A pointer to the memory area to copy.
 * @k: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(buff_t *output, const char *src, unsigned int k)
{
	unsigned int ind;

	for (ind = 0; ind < n; ind++)
	{
		*(output->buffer) = *(src + ind);
		(output->lenn)++;

		if (output->lenn == 1024)
		{
			write(1, output->start1, output->lenn);
			output->buffer = output->start1;
			output->lenn = 0;
		}

		else
			(output->buffer)++;
	}

	return (k);
}

/**
 * free_buffer - Frees a buffer_t struct.
 * @output: The buff_t struct to be freed.
 */
void free_buffer(buff_t *output)
{
	free(output->start1);
	free(output);
}

/**
 * init_buffer - Initializes a variable of struct type buff_t.
 *
 * Return: A pointer to the initialized buff_t.
 */
buff_t *init_buffer(void)
{
	buff_t *output;

	output = malloc(sizeof(buff_t));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start1 = output->buffer;
	output->lenn = 0;

	return (output);
}

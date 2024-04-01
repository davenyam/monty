#include "monty.h"

bus_t bus = {NULL, NULL, NULL, 0};

/* custom_getline - custom implementation of getline function */
ssize_t custom_getline(lineptr, n, stream)
char **lineptr;
size_t *n;
FILE *stream;
{
	size_t capacity = *n;
	size_t i = 0;
	int c;
	char *tmp;

	if (*lineptr == NULL)
	{
		*lineptr = malloc(capacity);
		if (*lineptr == NULL)
		{
			return -1;
		}
	}

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i + 1 >= capacity)
		{
			capacity *= 2;
			tmp = realloc(*lineptr, capacity);
			if (tmp == NULL)
			{
				return -1;
			}
			*lineptr = tmp;
		}
		(*lineptr)[i++] = c;
	}

	(*lineptr)[i] = '\0';
	*n = capacity;
	return i;
}

/**
 * main - monty code interpreter
 * @argc: number of arguments
 * @argv: monty file location
 * Return: 0 on success
 */
int main(argc, argv)
int argc;
char *argv[];
{
	char *content;
	FILE *file;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;
	unsigned int counter = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	bus.file = file;
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		content = NULL;
		read_line = custom_getline(&content, &size, file);
		bus.content = content;
		counter++;
		if (read_line > 0)
		{
			execute(content, &stack, counter, file);
		}
		free(content);
	}
	free_stack(stack);
	fclose(file);
	return (0);
}

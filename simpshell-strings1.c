#include "shell.h"

/**
 * File name: simpshell-strings1.c
 * Tokenize a string for Shell Program, part of Simple Shell Team Project on ALX 
 * OG and CambridgeMM
 */

// Functions Declarations
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Function that locates the delimiter index marking the end
 *             of 1st token within a string.
 * @str: String to be searched.
 * @delim: Delimiter character.
 *
 * Return: Delimiter index marking the end of the1st token pointed.
 */

int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - Function that counts the No of delimited
 *                words within a string.
 * @str: String to be searched.
 * @delim: Delimiter character.
 *
 * Return: No of words contained within str.
 */

int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Function that tokenizes a string.
 * @line: String.
 * @delim: Delimiter character to tokenize String by.
 *
 * Return: Pointer to an array containing the tokenized words.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

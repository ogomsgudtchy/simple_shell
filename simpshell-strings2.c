#include "shell.h"


/**
 * File name: simpshell-strings2.c
 * Handles Lenght of Strings for Shell Program, part of Simple Shell Team Project on ALX 
 * OG and CambridgeMM
 */

// Functions Declaration
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Func that returns Length of String.
 * @s: Pointer to Characters-string.
 *
 * Return: Length of the Characters-string.
 */

int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - Func that copies String pointed to by src, including the
 *           terminating null byte, to the buffer pointed by destination.
 * @dest: Pointer to the Destination-string.
 * @src: Pointer to Source-string.
 *
 * Return: Pointer to dest.
 */

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Func that concantenates two strings.
 * @dest: Pointer to Destination-string.
 * @src: Pointer to Source-string.
 *
 * Return: Pointer to Destination-string.
 */

char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Func that concantenates two strings where n number
 *            of bytes are copied from Source.
 * @dest: Pointer to Destination-string.
 * @src: Pointer to Source-string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}

#include "shell.h"

/**
 * _strchr - Function to locate a character in a string.
 * @s: String to be searched.
 * @c: Character to be located.
 *
 * Return: Pointer to the 1st occurence - If c is found.
 *              NULL -  If c is not found.
 */

char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _strspn - Function that  gets the length of a prefix substring.
 * @s: String to be searched.
 * @accept: Prefix to be measured.
 *
 * Return: No of bytes in which consist only of bytes from accept index.
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - Function that compare 2 strings.
 * @s1: The 1st string to be compared.
 * @s2: The 2nd string to be compared.
 *
 * Return: +ve byte difference if s1 > s2
 *               0 if s1 = s2
 *              -ve byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - Function that compare two strings.
 * @s1: Pointer to string.
 * @s2: Pointer to string.
 * @n: The 1st n bytes of strings to compare.
 *
 * Return: -ve No  if s1 is shorter than s2.
 *              0 if s1 and s2 match.
 *              +ve No if s1 is longer than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}

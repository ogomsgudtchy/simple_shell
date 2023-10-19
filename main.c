#include "main.h"

/**
 * main - main function
 * @ac: number received
 * @argv: character
 *
 * Description-
 * Return:0
 */

int main(int ac, char **argv)
{
char *prompt = "(simple_shell) $ ";
char *lineptr = NULL;
char *lineptr_copy = NULL;
size_t n = 0;
ssize_t nchars;
const char *delim = " \n";
int n_tokens = 0;
char *token;
int j;

(void)ac;

while (1)
{
printf("%s", prompt);
nchars = getline(&lineptr, &n, stdin);

if (nchars == -1)
{
printf("Exiting ..\n");
return (-1);
}

lineptr_copy = malloc(sizeof(char) * n_tokens);
if (lineptr_copy == NULL)
{
perror("memory allocation error");
return (-1);
}

strcpy(lineptr_copy, lineptr);

token = strtok(lineptr, delim);

while (token != NULL)
{
n_tokens++;
token = strtok(NULL, delim);
}
n_tokens++;

argv = malloc(sizeof(char*) * n_tokens);
token = strtok(lineptr_copy, delim);

for (j = 0; token != NULL; j++)
{
argv[j] = malloc(sizeof(char) * strlen(token));
strcpy(argv[j], token);
token = strtok(NULL, delim);
}
argv[j] = NULL;

execu(argv);
}
printf("%s\n", lineptr);

free(lineptr_copy);
free(lineptr);

return(0);
}

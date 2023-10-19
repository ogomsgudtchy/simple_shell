#include "main.h"

/**
 * execu - executes the code
 * @argv: received
 *
 * Description-
 *
 */

void execu(char **argv)
{
char *command = NULL;
char *actual_command = NULL;

if (argv)
{
command = argv[0];
actual_command = get_location(command);

if (execve(actual_command, argv, NULL) == -1)
{
perror("Error:");
};
}
}

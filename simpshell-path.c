#include "shell.h"

/*
 * File name: simpshell-path.c
 * Shell Program that handles PATH, part of Simple Shell Team Project on ALX 
 * OG and CambridgeMM
 */


// Function Declarations
char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);
int execute_command(char **args, char **front, char **environ);

/**
 * get_location - Function to locate command in the PATH.
 * @command: Command to locate.
 *
 * Return: NULL - If Error occurs or Command cannot be located.
 *         Otherwise - the full Pathname of Command.
 */

char *get_location(char *command)
{
char *path_var = *_getenv("PATH") + 5;
char *path_copy = fill_path_dir(path_var);

if (!path_copy)
return NULL;

char **dirs = _strtok(path_copy, ":");
free(path_copy);

if (!dirs)
return NULL;

char *result = NULL;

for (int i = 0; dirs[i] != NULL && result == NULL; i++)
{
char *temp = malloc(_strlen(dirs[i]) + _strlen(command) + 2);
if (!temp)
{
	free(dirs);
return NULL;
}
		_strcpy(temp, dirs[i]);
		_strcat(temp, "/");
_strcat(temp, command);

		if (access(temp, F_OK) == 0)
result = temp;
	else
free(temp);
   	}
free(dirs);
return result;
}

/**
 * fill_path_dir - Function that copies PATH and equally replaces leading/sandwiched/trailing
 *		   colons (:) with the current working directory.
 * @path: Colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Function that tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: Colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */

list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

/**
 * execute_command - Function which executes command in a child process.
 * @args: Array of arguments.
 * @front: Double-pointer to the beginning of args.
 * @environ: The environment variables.
 *
 * Return: The exit value of the executed command.
 */
int execute_command(char **args, char **front, char **environ);
{
	char *command = args[0];

	if (command == NULL || access(command, F_OK) == -1)
	{
		if (command)
			create_error(args, 127);
		return 127;
	}
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error child:");

		return 1;
	}
	if (child_pid == 0)
	{
		execve(command, args, environ);

		// If execve fails, free resources and exit with Errorcode
		create_error(args, 126);
		free_env();
		free_args(args, front);
		free_alias_list(aliases);
		_exit(126);
	}
	else
	{
		int status;
		wait(&status);
		return WEXITSTATUS(status);
	}
}

#include "shell.h"

/**
 ** File name: simpshell-main.c
 * UNIX Command-line Interpreter, Simple Shell Team Project on ALX
 * OG and CambridgeMM
 * sig_handler - Function that handles signals, particularly SIGINT (Ctrl+C).
 * @sig: The Signal.
 * get_builtin - Function that matches Command with a corresponding
 *               shellby built-in function.
 * @command: Command to match.
 *
 * Return: Function pointer to the corresponding built-in.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - Function that causes normal process termination
 *                for Shellby shell.
 * @args: Array of arguments containing the Exitvalue.
 * @front: Double-pointer to the beginning of args.
 *
 * Return: -3 - If there are no arguments.
 *	        2 -  If the given exit value is invalid.
 *              Otherwise, exits with the given status value.
 *  Description: Upon returning -3, the program exits back in  Main function.
 */

int shellby_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shellby_cd - Function that changes current directory of Shellby process.
 * @args: Array of arguments.
 * @front: Double-pointer to the beginning of args.
 *
 * Return:  2 - If the given string is not a Directory.
 *              -1 - If an error occurs.
 *              Otherwise, 0.
 */
int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
		chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(oldpwd);
free(pwd);
free(dir_info);
return (0);
}

/**
 * shellby_help - Function that displays info about Shellby built-in commands.
 * @args: Array of arguments.
 * @front: A pointer to beginning of args.
 *
 * Return: -1 If an error occurs, and otherwise - 0.
 */

int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
help_all();
else if (_strcmp(args[0], "alias") == 0)
help_alias();
else if (_strcmp(args[0], "cd") == 0)
help_cd();
else if (_strcmp(args[0], "exit") == 0)
help_exit();
else if (_strcmp(args[0], "env") == 0)
help_env();
else if (_strcmp(args[0], "setenv") == 0)
help_setenv();
else if (_strcmp(args[0], "unsetenv") == 0)
help_unsetenv();
else if (_strcmp(args[0], "help") == 0)
help_help();
else
write(STDERR_FILENO, name, _strlen(name));
return (0);
}

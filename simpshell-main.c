#include "shell.h"

/*
 * File name: simpshell-main.c
 * UNIX Command-line Interpreter, Simple Shell Team Project on ALX
 * OG and CambridgeMM
 */

Function Declarations
void sig_handler(int sig);
int execute(char **args, char **front);
int main(int argc, char *argv[]);

/**
 * sig_handler - Function that handles signals, particularly SIGINT (Ctrl+C).
 * @sig: The Signal.
 */

void sig_handler(int sig)
{
	Define a new prompt for readability
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Function to execute Command in a Child process.
 * @args: Array of arguments.
 * @front: Double-pointer to the beginning of args.
 *
 * Return: Exit Status for executed command.
 */

int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, exit_status = 0;
	char *command = args[0];

	 If command is not an absolute or relative path, attempt to locate it
	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	 Check if the command exists and is accessible
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			exit_status = (create_error(args, 126));
		else
			exit_status = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				exit_status = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(exit_status);
		}
		else
		{
			wait(&status);
			exit_status = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (exit_status);
}

/**
 * main - Function to run a simple UNIX command interpreter.
 * @argc: Number of arguments supplied to program.
 * @argv: Array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */

int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}

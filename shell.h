#ifndef _SHELL_H_
#define _SHELL_H_


/*
 * File name: shell.h
 * HEADER file for Simple Shell Team Project on ALX
 * OG and CambridgeMM
 */


#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>


#define END_OF_FILE -2
#define EXIT -3


/* GLOBAL VARIABLES */
/* Global Environs */
extern char **environ;
/* Global Program Name */
char *name;
/* Global History Counter */
int hist;


/**
 * struct list_s - New struct type that defines a linked list.
 * @dir: Directory Path.
 * @next: Points to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


/**
 * struct builtin_s - New struct type that defines builtin commands.
 * @name: Name of the builtin command.
 * @f: Function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;


/**
 * struct alias_s - New struct defining aliases.
 * @name: Name of the alias.
 * @value: Value of the alias.
 * @next: Pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;


/**
 * Global Aliases Linked List.
 */
alias_t *aliases;


/* Main Helpers */
list_t *get_path_dir(char *path);
void free_list(list_t *head);
int execute(char **args, char **front);
char **_strtok(char *line, char *delim);
char *_itoa(int num);
char *get_location(char *command);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


/* Input Helpers */
char **replace_aliases(char **args);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
void variable_replacement(char **args, int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
void handle_line(char **line, ssize_t read);
int run_args(char **args, char **front, int *exe_ret);


/* String Functions */
int _strspn(char *s, char *accept);
char *_strchr(char *s, char c);
char *_strncat(char *dest, const char *src, size_t n);char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);


/* Builtin Helpers */
char **_getenv(const char *var);
char **_copyenv(void);
void free_env(void);


/* Error Handling */
int create_error(char **args, int err);
char *error_126(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_syntax(char **args);
char *error_127(char **args);


/* Linked List Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);


void help_all(void);
void help_env(void);
void help_alias(void);
void help_unsetenv(void);
void help_setenv(void);
void help_history(void);
void help_cd(void);
void help_help(void);
void help_exit(void);


int proc_file_commands(char *file_path, int *exe_ret);


#endif


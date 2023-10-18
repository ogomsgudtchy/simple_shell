#include "shell.h"

/**
 * File name: simpshell-lists.c
 * Manages Linked Lists for Shell Program, part of Simple Shell Team Project on ALX 
 * OG and CambridgeMM
 * add_alias_end - Function to add a node to the end of alias_t linked list.
 * @head: Pointer to head of the list_t list.
 * @name: Name of the new alias to be added.
 *
 * @value: Value of the new alias to be added.
 *
 * Return: NULL - If an error occurs, and otherwise - a pointer to the new node.
 */

alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Function to add a node to the end of a list_t linked list.
 * @head: Pointer to the head of the list_t list.
 * @dir: Directory path for the new node to contain.
 *
 *  Return: NULL - If an error occurs, and otherwise - a pointer to the new node.
 */

list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - Function to free a alias_t linked list.
 * @head: Head of the alias_t list.
 */

void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Function to free list_t linked list.
 * @head: Head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

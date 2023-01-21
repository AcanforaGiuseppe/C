#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "linkedlist.h"

list_node_t* list_get_tail(list_node_t** head)
{
	list_node_t* current_node = *head;
	list_node_t* last_node = NULL;

	while (current_node)
	{
		last_node = current_node;
		current_node = current_node->next;
	}
	return last_node;
}

list_node_t* list_append(list_node_t** head, list_node_t* item)
{
	list_node_t* tail = list_get_tail(head);

	if (!tail)
		*head = item;
	else
		tail->next = item;

	item->next = NULL;
	return item;
}

list_node_t* list_reverse(list_node_t** head)
{
	list_node_t* new_head = list_get_tail(head);
	list_remove(head, new_head);

	while (*head)
	{
		list_node_t* to_append = list_get_tail(head);
		list_remove(head, to_append);
		list_append(&new_head, to_append);
	}

	*head = new_head;
	return new_head;
}

int list_remove(list_node_t** head, list_node_t* item)
{
	list_node_t* current_node = *head;

	if (current_node == item)
	{
		list_pop(head);
		return 0;
	}

	list_node_t* last_node = NULL;
	list_node_t* next_node = NULL;

	while (current_node)
	{
		next_node = current_node->next;
		if (current_node == item)
		{
			last_node->next = next_node;
			current_node->next = NULL;
			return 0;
		}
		last_node = current_node;
		current_node = current_node->next;
	}
	return -1;
}

list_node_t* list_pop(list_node_t** head)
{
	list_node_t* current_head = *head;

	if (!current_head)
		return NULL;

	*head = (*head)->next;
	current_head->next = NULL;
	return current_head;
}



string_item_t* string_item_new(const char* string)
{
	string_item_t* item = malloc(sizeof(string_item_t));

	if (!item)
		return NULL;

	item->string = string;
	return item;
}
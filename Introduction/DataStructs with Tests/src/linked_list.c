#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

ListNode* list_get_tail(ListNode** head)
{
	if (*head == NULL)
		return NULL;

	ListNode* current_node = *head;
	ListNode* last_node = NULL;

	while (current_node)
	{
		last_node = current_node;
		current_node = current_node->next;
	}
	return last_node;
}

ListNode* list_append(ListNode** head, ListNode* item)
{
	ListNode* tail = list_get_tail(head);

	if (!tail)
		*head = item;
	else
		tail->next = item;

	item->next = NULL;
	return item;
}

ListNode* list_pop(ListNode** head)
{
	if (*head == NULL) return NULL;
	ListNode* current_head = *head;

	if (!current_head)
		return NULL;

	*head = (*head)->next;
	current_head->next = NULL;
	return current_head;
}

ListNode* list_remove(ListNode** head, cString* item)
{
	if (head == NULL) return NULL;
	if (*head == NULL) return NULL;
	ListNode* current_item = *head;
	StringItem* current_string = (StringItem*)current_item;
	ListNode* previous_item = NULL;

	if (strcmp(current_string->string, item) == 0)
	{
		*head = current_item->next;
		current_item->next = NULL;
		return current_item;
	}

	while (strcmp(current_string->string, item) != 0)
	{
		if (!current_item->next)
			return NULL;

		previous_item = current_item;
		current_item = current_item->next;
		current_string = (StringItem*)current_item;
		printf("string: %s\n", current_string->string);
	}
	previous_item->next = current_item->next;
	return current_item;
}

StringItem* string_item_new(cString* string)
{
	StringItem* item = allocate_size_of_string;

	if (!item)
		return NULL;

	item->string = string;
	return item;
}
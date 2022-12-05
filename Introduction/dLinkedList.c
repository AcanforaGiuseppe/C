#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "doubleLinked.h"
#include "linkedList.h"

#define RAND(upper,lower) ((rand() % (upper - lower + 1)) + lower) 

dlist_node_t* dlist_get_tail(dlist_node_t** head)
{
	dlist_node_t* current_node = *head;
	dlist_node_t* last_node = NULL;

	while (current_node)
	{
		last_node = current_node;
		current_node = current_node->next;
	}
	return last_node;
}

dInt_item_t* dInt_create(int n)
{
	dInt_item_t* item = malloc(sizeof(dInt_item_t));

	if (!item)
		return NULL;

	item->n = n;
	return item;
}

void dList_print(dInt_item_t* list)
{
	while (list)
	{
		printf("%d\n", list->n);
		list = (dInt_item_t*)list->node.next;
	}
}

int dList_get_lenght(dInt_item_t* list)
{
	int counter = 0;

	while (list)
	{
		counter++;
		list = (dInt_item_t*)list->node.next;
	}
	return counter;
}

void dList_remove(dlist_node_t** head, dlist_node_t* item)
{
	if (*head == item)
	{
		*head = item->next;
		return;
	}

	if (item == dlist_get_tail(head))
	{
		item->prev->next = NULL;
		return;
	}

	if (dList_contain(head, item))
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}
	else
	{
		perror("list doesn't contain items");
	}

}

int dList_insert_before(dlist_node_t** head, dlist_node_t* before_this, dlist_node_t* item)
{
	if (dList_contain(head, item))
	{
		printf("Item is already on the list\n");
		return -1;
	}

	if (dList_contain(head, before_this))
	{
		dlist_node_t* prev_node = before_this->prev;

		if (!prev_node)
		{
			*head = item;
			item->next = before_this;
			item->prev = NULL;
			before_this->prev = item;
			return 0;
		}
		else
		{
			prev_node->next = item;
			item->prev = prev_node;
			item->next = before_this;
			before_this->prev = item;
			return 0;
		}
	}
	printf("Selected element not in list");
	return -1;
}

int dList_insert_after(dlist_node_t** head, dlist_node_t* after_this, dlist_node_t* item)
{
	if (dList_contain(head, item))
	{
		printf("Item is already on the list\n");
		return -1;
	}

	if (dList_contain(head, after_this))
	{
		dlist_node_t* next_node = after_this->next;

		if (!next_node)
		{
			item->next = NULL;
		}
		else
		{
			item->next = next_node;
			next_node->prev = item;
		}
		after_this->next = item;
		item->prev = after_this;
		return 0;
	}
	else
	{
		return -1;
	}
}

int dList_contain(dlist_node_t** head, dlist_node_t* item)
{
	dlist_node_t* current_node = *head;
	dlist_node_t* last_node = NULL;

	while (current_node)
	{
		if (current_node == item)
			return 1;

		last_node = current_node;
		current_node = current_node->next;
	}
	return 0;
}

dlist_node_t* dlist_append(dlist_node_t** head, dlist_node_t* item)
{
	dlist_node_t* tail = dlist_get_tail(head);

	if (!tail)
		*head = item;
	else
		tail->next = item;

	item->prev = tail;
	item->next = NULL;
	return item;
}

void dList_destroy(dlist_node_t** head)
{
	dInt_item_t* tail = (dInt_item_t*)dlist_get_tail(head);
	while (tail)
	{
		dList_remove(head, (DNODE_P)tail);
		free(tail);
		tail = (dInt_item_t*)dlist_get_tail(head);
	}
}

dInt_item_t* dList_shuffle(dlist_node_t** head)
{
	dInt_item_t* list = (dInt_item_t*)*head;
	int l = dList_get_lenght(list);
	int* saved_value = malloc(l * sizeof(int));

	for (int i = 0; i < l; i++)
	{
		saved_value[i] = list->n;
		list = (dInt_item_t*)list->node.next;
	}
	srand(time(0));
	int upper = l - 1;
	int lower = 0;

	if (upper < 0)
	{
		perror("Negative upper value");
		return NULL;
	}

	for (int i = 0; i < l; i++)
	{
		int r = RAND(upper, lower);
		int tmp = saved_value[r];
		saved_value[r] = saved_value[i];
		saved_value[i] = tmp;
	}

	dInt_item_t* newList = NULL;

	for (int i = 0; i < l; i++)
	{
		dInt_item_t* newItem = dInt_create(saved_value[i]);
		dlist_append((DNODE_PP)&newList, (DNODE_P)newItem);
	}
	free(saved_value);
	return newList;
}
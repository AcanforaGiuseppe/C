#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sets.h"

size_t djb33x_hash(const char* key, const size_t keylen)
{
	size_t hash = 5381;

	for (size_t i = 0; i < keylen; i++)
		hash = ((hash << 5) + hash) ^ key[i];

	return hash;
}

set_table_t* set_table_new(const size_t hashmap_size)
{
	set_table_t* table = malloc(sizeof(set_table_t));

	if (!table)
		return NULL;

	table->hashmap_size = hashmap_size;
	table->nodes = calloc(table->hashmap_size, sizeof(set_node_t*));

	if (!table->nodes)
	{
		free(table);
		return NULL;
	}
	return table;
}

set_node_t* set_contain(set_table_t* table, const char* key, const size_t key_len)
{
	size_t hash = djb33x_hash(key, key_len);
	size_t index = hash % table->hashmap_size;
	set_node_t* node = table->nodes[index];
	if (node)
	{
		set_node_t* sel_node = node;
		while (sel_node)
		{
			if (sel_node->key_len == key_len)
			{
				if (strcmp(sel_node->key, key) == 0)
					return sel_node;
			}
			sel_node = sel_node->next;
		}
	}
	return NULL;
}

void set_print(set_table_t* table)
{
	printf("{");
	for (size_t i = 0; i < table->hashmap_size; i++)
	{
		set_node_t* node = table->nodes[i];

		if (node)
		{
			while (node)
			{
				printf("%s, ", node->key);
				node = node->next;
			}
		}
	}
	printf("}");
}

void set_remove(set_table_t* table, const char* key)
{
	size_t len = strlen(key);
	set_node_t* node = set_contain(table, key, len);
	size_t hash = djb33x_hash(key, len);
	size_t index = hash % table->hashmap_size;

	if (node)
	{
		set_node_t* prev = node->prev;
		set_node_t* next = node->next;
		if (!prev && !next)
			table->nodes[index] = NULL;

		if (!prev)
			table->nodes[index] = node->next;

		if (!next)
			prev->next = NULL;

		node->next = NULL;
		node->prev = NULL;
		return;
	}
}

set_node_t* set_insert(set_table_t* table, const char* key, const size_t key_len)
{
	if (set_contain(table, key, key_len))
		return NULL;

	size_t hash = djb33x_hash(key, key_len);
	size_t index = hash % table->hashmap_size;
	set_node_t* head = table->nodes[index];

	if (!head)
	{
		table->nodes[index] = malloc(sizeof(set_node_t));

		if (!table->nodes[index])
			return NULL;

		table->nodes[index]->key = key;
		table->nodes[index]->key_len = key_len;
		table->nodes[index]->next = NULL;
		table->nodes[index]->prev = NULL;
		return table->nodes[index];
	}
	set_node_t* new_item = malloc(sizeof(set_node_t));

	if (!new_item)
		return NULL;

	new_item->key = key;
	new_item->key_len = key_len;
	new_item->next = NULL;
	set_node_t* tail = head;

	while (head)
	{
		tail = head;
		head = head->next;
	}
	tail->next = new_item;
	new_item->prev = tail;
	return new_item;
}
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "dictionary.h"

typedef struct dic_node
{
	set_node_t node;
	data_t data;

} dictionary_node_t;

typedef struct dic
{
	set_table_t table;
} dictionary_t;

size_t djb33x_hash(const char* key, const size_t keylen)
{
	size_t hash = 5381;

	for (size_t i = 0; i < keylen; i++)
		hash = ((hash << 5) + hash) ^ key[i];

	return hash;
}

dictionary_t* dictionary_new(const size_t hashmap_size)
{
	dictionary_t* table = malloc(sizeof(dictionary_t));

	if (!table)
		return NULL;

	(SET table)->hashmap_size = hashmap_size;
	(SET table)->nodes = calloc((SET table)->hashmap_size, sizeof(dictionary_node_t*));
	(SET table)->_collisions = 0;

	if (!(SET table)->nodes)
	{
		free(table);
		return NULL;
	}
	return table;
}

dictionary_node_t* dictionary_insert(dictionary_t** table, const char* key, const size_t key_len, const data_t data)
{
	if ((SET(*table))->hashmap_size * 0.75f <= (SET(*table))->_collisions)
		_rehash(SET_ADDRESS table, sizeof(dictionary_t), sizeof(dictionary_node_t*));

	const size_t hash = djb33x_hash(key, key_len);
	const size_t index = hash % (SET(*table))->hashmap_size;
	linked_list_node_t* head = (SET(*table))->nodes[index];

	if (!head)
	{
		(SET(*table))->nodes[index] = malloc(sizeof(dictionary_node_t));

		if (!(SET(*table))->nodes[index])
			return NULL;

		(SET_NODE(SET(*table))->nodes[index])->key = key;
		(SET_NODE(SET(*table))->nodes[index])->key_len = key_len;
		(DICTIONARY_NODE(SET(*table))->nodes[index])->data = data;
		(SET(*table))->nodes[index]->next = NULL;

		return DICTIONARY_NODE(SET(*table))->nodes[index];
	}
	dictionary_node_t* new_item = malloc(sizeof(dictionary_node_t));

	if (!new_item)
		return NULL;

	(SET_NODE new_item)->key = key;
	(SET_NODE new_item)->key_len = key_len;
	new_item->data = data;
	(NODE new_item)->next = NULL;
	linked_list_node_t* tail = head;

	while ((head))
	{
		if ((SET_NODE head)->key == key)
			return NULL;

		tail = head;
		head = head->next;
	}

	tail->next = NODE new_item;
	(SET(*table))->_collisions++;
	return new_item;
}

dictionary_node_t* dictionary_search(dictionary_t* table, const char* key, const size_t key_len)
{
	return DICTIONARY_NODE set_search(SET table, key, key_len);
}

void dictionary_delete(dictionary_t** table)
{
	set_delete(SET_ADDRESS table);
}

int dictionary_remove_key(dictionary_t** table, const char* key, const size_t key_len)
{
	return set_remove_key(SET_ADDRESS table, key, key_len);
}
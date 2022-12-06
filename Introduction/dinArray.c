#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dinArray.h>

int dynarray_init(dynarray_t* array, const size_t size_of_element)
{
	array->number_of_elements = 0;
	array->size_of_element = size_of_element;
	array->data = NULL;
	array->tmp_data = malloc(size_of_element);

	if (!array->tmp_data)
		return -1;

	return 0;
}

void dynarray_clear(dynarray_t* array)
{
	array->number_of_elements = 0;
	free(array->data);
	array->data = NULL;
	free(array->tmp_data);
	array->tmp_data = NULL;
}

int dynarray_append(dynarray_t* array, const void* value)
{
	const size_t new_size = array->number_of_elements + 1;
	uint8_t* new_ptr = realloc(array->data, new_size * array->size_of_element);

	if (!new_ptr)
		return -1;

	array->data = new_ptr;
	size_t offset = array->number_of_elements * array->size_of_element;
	memcpy(array->data + offset, value, array->size_of_element);
	array->number_of_elements = new_size;
	return 0;
}

size_t dynarray_len(const dynarray_t* array)
{
	return array->number_of_elements;
}

int dynarray_get(const dynarray_t* array, const size_t index, void* value)
{
	if (index >= array->number_of_elements)
		return -1;

	const size_t offset = index * array->size_of_element;
	memcpy(value, array->data + offset, array->size_of_element);
	return 0;
}

int dynarray_remove(dynarray_t* array, const size_t index)
{
	if (index >= array->number_of_elements)
		return -1;

	const size_t offset = index * array->size_of_element;

	if (index < array->number_of_elements - 1)
	{
		memcpy(array->tmp_data, array->data + offset, array->size_of_element);
		memmove(array->data + offset, array->data + offset + array->size_of_element, (array->number_of_elements - index) * array->size_of_element);
	}

	const size_t new_size = array->number_of_elements - 1;
	uint8_t* new_ptr = realloc(array->data, new_size * array->size_of_element);
	if (!new_ptr)
	{
		if (index < array->number_of_elements - 1)
		{
			memmove(array->data + offset + array->size_of_element, array->data + offset, (array->number_of_elements - index) * array->size_of_element);
			memcpy(array->data + offset, array->tmp_data, array->size_of_element);
		}
		return -1;
	}

	array->data = new_ptr;
	array->number_of_elements = new_size;
	return 0;
}
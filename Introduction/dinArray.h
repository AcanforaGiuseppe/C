#include <stdint.h>

typedef struct dynarray
{
	size_t number_of_elements;
	size_t size_of_element;
	size_t capacity;
	uint8_t* data;
	uint8_t* tmp_data;
} dynarray_t;

int dynarray_init(dynarray_t* array, const size_t size_of_element);
#define dynarray_init_type(array, type) dynarray_init(array, sizeof(type));
void dynarray_clear(dynarray_t* array);
int dynarray_append(dynarray_t* array, const void* value);
size_t dynarray_len(const dynarray_t* array);
int dynarray_get(const dynarray_t* array, const size_t index, void* value);
int dynarray_remove(dynarray_t* array, const size_t index);
#include <stdlib.h>
#include <string.h>

/*
	From value to pointer "&"
	From pointer to value "*"
*/

struct vec3
{
	float x;
	float y;
	float z;
};

struct list
{
	size_t size;
	size_t allocated_size;
	void* data;
};

void vec3_add(struct vec3* dest, struct vec3* src)
{
	/* An Arrow operator (->) in C allows to access elements in Structures and Unions.
	It is used with a pointer variable pointing to a structure or union. */
	dest->x += src->x;
	dest->y += src->y;
	dest->z += src->z;
}

int main(int argc, char** argv)
{
	struct vec3 a = { 1, 2, 3 };
	a.x = 1;
	a.y = 2;
	a.z = 3;

	struct vec3 b = { 4,5,6 };
	vec3_add(&a, &b);

	struct vec3 vectors[100];

	struct list dummy_list;
	dummy_list.size = 0;
	dummy_list.allocated_size = 2;
	dummy_list.data = malloc(sizeof(int) * dummy_list.allocated_size);
}

struct list_append(struct list* my_list, const int value)
{
	if (my_list-> >= my_list->allocated_size)
	{
		void new_data = realloc(my_list->data, sizeof(int) * my_list->allocated_size + 1)
			// Checking errors - missing part not needed for the example
			my_list->data = new_data;
	}
	((int*)my_list->data)[my_list->size] = value;
	my_list->size++;
	my_list->allocated_size++;
}

struct set_item
{
	const char* string;
	int hash;
};

const char *test()
{
	struct set_item items[100];
	const char* pippo = "hello";
	int new_hash = 1000;

	for (int i = 0; i < 100; i++)
	{
		if (!strcmp(items[i].string, pippo))
			return items[i].string;
	}
	return NULL;
}
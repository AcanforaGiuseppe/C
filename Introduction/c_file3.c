// Libraries included in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char** environ)
{
	// Writes "ciao"
	puts("ciao");

	/* Placeholders are :
		%d -> integer
		%u -> unsigned int
		%s -> string
		%c -> character
	*/

	// \n means end of line, printf is a function that prints a string with given arguments (included placeholders)
	printf("i got %d arguments \n", argc);

	for (int i = 0; i < argc; i++)
		printf("arg %d is %s\n", i, argv[i]);

	puts("waiting for keyboard...");
	// getchar -> Waits for an input from the keyboard
	int input = getchar();
	// Converts it from lower to upper case
	printf("pressed %d %c\n", input, input - 32);

	char** environ_copy = environ;
	char* env;
	// Loop without limitations (infinite loop)
	// Iterathing a collection: first method

	/*
	for (;;)
	{
		char* env = *environ_copy++;
		// Checking the env's integrity
		if (!env)
			break;
		printf("env: %s\n", env);
	}
	*/

	// Iterathing a collection: Second method
	while ((env = *environ_copy++))
	{
		printf("env: %s\n", env);
	}


	// Allocation, Reallocation and Freeing data
	char* data = malloc(1024);
	if (!data)
		return -1;

	char* new_data = realloc(data, 2048);
	if (!new_data)
		return -1;

	data = new_data;
	free(data);

	// String manipulation
	const char* source = "hello world";
	// Allocating the length of source, + 1 becouse we need to allocate the "0" that indicates the end of the string
	char* dest = malloc(strlen(source + 1));
	strcpy(dest, source);

	free(dest);

	return 0;
}
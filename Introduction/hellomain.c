#include <stdio.h>
#include <windows.h>

const char* hello_world();

int main(int argc, char **argv)
{
	MessageBeep(MB_OK);
	int ret = MessageBoxA(NULL, "Hello World", "TITLE OF WINDOW", MB_CANCELTRYCONTINUE);
	printf("pressed button %d\n", ret);
	printf("string from library: %s\n", hello_world());
}
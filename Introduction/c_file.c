// using the "#include "funcs.h"" for calling all the definitions from the file "funcs.h"
#include "funcs.h"

int main(int argc, char** argv)
{
	return dummy_adder(argc + 123, 1, 2);
}

int dummy_adder(int a, int b, int c)
{
	return a + b + c;
}

/*
With clang.exe:
	Compiling:
		clang.exe -c -o c_file.o c_file.c
	Linking:
		clang.exe -o first.exe c_file.o
	Executing linker:
		.\first.exe
	Checking the exit code:
		echo $LASTEXITCODE
	Compiling & linking together:
		clang.exe -o first.exe c_file.c
*/
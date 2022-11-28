#ifdef _WIN32
#define EXPORTFUNC __declspec(dllexport)
#else
#define EXPORTFUNC
#endif

// Compiling with:
//clang.exe -shared -o libfoo.dll .\libfoo.c
//clang.exe -o hellomain.exe .\hellomain.c -llibfoo -luser32

EXPORTFUNC const char* hello_world()
{
	return "hello world";
}
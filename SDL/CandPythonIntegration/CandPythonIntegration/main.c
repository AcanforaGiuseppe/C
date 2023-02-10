#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <Python.h>

static PyModuleDef PyAIV =
{
	PyModuleDef_HEAD_INIT
};

SDL_Rect rect;

static PyObject* PyAIV_Init()
{
	return PyModule_Create(&PyAIV);
}

static PyObject* PyAIV_move(PyObject* self, PyObject* args)
{
	int x = 0, y = 0;

	if (!PyArg_ParseTuple(args, "ii", &x, &y))
		return NULL;

	rect.x = x;
	rect.y = y;

	PyObject* tuple = PyTuple_New(2);
	PyTuple_SetItem(tuple, 0, PyLong_FromLong(5));
	PyTuple_SetItem(tuple, 1, PyLong_FromLong(8));
	return tuple;
}

static PyMethodDef PyAIV_Methods[] =
{
	{"move", PyAIV_move, METH_VARARGS, NULL},
	{NULL}
};

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return -1;
	}
	SDL_Log("SDL is active!");

	// Creation of a new python module
	PyAIV.m_name = "pyaiv";
	PyAIV.m_doc = "Hello";
	PyAIV.m_methods = PyAIV_Methods;
	PyAIV.m_size = -1;
	PyImport_AppendInittab(PyAIV.m_name, PyAIV_Init);

	Py_Initialize();

	SDL_Window* window = SDL_CreateWindow("SDL is active!", 100, 100, 512, 512, 0);
	if (!window)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	int width;
	int heigth;
	int channel;
	unsigned char* pixels = stbi_load("car.png", &width, &heigth, &channel, 4);

	if (!pixels)
	{
		SDL_Log("Unable to open image: %s", stbi__g_failure_reason);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, heigth);
	if (!texture)
	{
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_UpdateTexture(texture, NULL, pixels, width * 4);

	SDL_Vertex vertex[4];
	vertex[0].position.x = 50;
	vertex[0].position.y = 50;
	vertex[0].color.r = 255;
	vertex[0].color.g = 255;
	vertex[0].color.b = 255;
	vertex[0].color.a = 255;
	vertex[0].tex_coord.x = 0;
	vertex[0].tex_coord.y = 0;
	vertex[1].position.x = 200;
	vertex[1].position.y = 50;
	vertex[1].color.r = 255;
	vertex[1].color.g = 255;
	vertex[1].color.b = 255;
	vertex[1].color.a = 255;
	vertex[1].tex_coord.x = 1;
	vertex[1].tex_coord.y = 0;
	vertex[2].position.x = 50;
	vertex[2].position.y = 200;
	vertex[2].color.r = 255;
	vertex[2].color.g = 255;
	vertex[2].color.b = 255;
	vertex[2].color.a = 255;
	vertex[2].tex_coord.x = 0;
	vertex[2].tex_coord.y = 1;
	vertex[3].position.x = 200;
	vertex[3].position.y = 200;
	vertex[3].color.r = 255;
	vertex[3].color.g = 255;
	vertex[3].color.b = 255;
	vertex[3].color.a = 255;
	vertex[3].tex_coord.x = 1;
	vertex[3].tex_coord.y = 1;

	int index[6] = { 0, 1, 2, 1, 3, 2 };

	rect.x = 0;
	rect.y = 0;
	rect.w = 128;
	rect.h = 128;

	//PyObject* pystring = PyUnicode_FromString("Hello");
	//PyObject* pySys = PyImport_ImportModule("sys");
	//PyObject_SetAttrString(pySys, "StringPy", pystring);
	//Py_DECREF(pystring);

	PyObject* pySys = PyImport_ImportModule("sys");
	PyObject* pyList = PyObject_GetAttrString(pySys, "path");
	PyObject* pyString = PyUnicode_FromString("C:/Users/acanf/Desktop");
	PyList_Append(pyList, pyString);
	PyObject* pyGameloop = PyImport_ImportModule("gameloop");
	PyObject* pyTick = PyObject_GetAttrString(pyGameloop, "tick");

	int running = 1;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
		}

		SDL_RenderClear(renderer);
		//PyRun_SimpleString("import sys;print(sys.__dict__)");
		//rect.x++;
		//SDL_RenderGeometry(renderer, texture, vertex, 4, index, 6);
		PyObject* tickRetVal = PyObject_CallFunction(pyTick, NULL);

		if (tickRetVal != NULL)
		{
			Py_DECREF(tickRetVal);
			/*PyObject* pyXvalue = PyObject_GetAttrString(pyGameloop, "x");
			PyObject* pyYvalue = PyObject_GetAttrString(pyGameloop, "y");
			rect.x = PyLong_AsLong(pyXvalue);
			rect.y = PyLong_AsLong(pyYvalue);*/
		}
		else
		{
			PyErr_Print();
		}

		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Py_Finalize();
	SDL_Quit();
	return 0;
}
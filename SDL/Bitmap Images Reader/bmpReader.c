#include <SDL.h>

SDL_Surface* image;
SDL_Surface* tryload;

tryload = SDL_LoadBMP(“image.bmp”);

if (tryload == NULL)
{
	printf(“Unable to load bitmap : % s\n”, SDL_GetError());
	return 1;
}

image = SDL_DisplayFormat(tryload);
SDL_FreeSurface(tryload);
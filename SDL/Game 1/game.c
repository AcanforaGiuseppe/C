#define SDL_MAIN_HANDLED
#include <SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Compiling with CLANG:
// clang.exe -I .\SDL2-2.26.0\include\ -o game.exe .\game.c -L .\SDL2-2.26.0\lib\x64\ -lSDL2

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL is active!", 100, 100, 512, 512, 0);
    if (!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int width, height, channels;
    unsigned char* pixels = stbi_load("emoji.png", &width, &height, &channels, 4);
    if (!pixels)
    {
        SDL_Log("Unable to open image");
        SDL_Quit();
        return 0;
    }
    SDL_Log("Image width: %d height: %d channels: %d", width, height, channels);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
    
    SDL_UpdateTexture(texture, NULL, pixels, width * 4);

    int running = 1;
    int x = 100;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // CTRL + C for exiting the application
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect target_rect = {x++, 0, width, height};
        SDL_RenderCopy(renderer, texture, NULL, &target_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}
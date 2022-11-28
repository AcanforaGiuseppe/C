#define SDL_MAIN_HANDLED
#include <SDL.h>

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

    int running = 1;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // CTRL + C for exiting the application
            if (event.type == SDL_Quit)
            {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}
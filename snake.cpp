#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "globalstuff.h"

int main(int argc, char *argv[])
{
    std::map<int, Color> colors = {
        {1, Color{255, 255, 255, 255}},
        {2, Color{255, 0, 0, 255}}};

    bool running = true;
    int gridSize = 10;
    
    CreateEmptyMap(10, 10);

    srand(time(0));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake", 0, 0, gridSize * columns, gridSize * rows, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < columns * rows; i++)
    {
        if(map[i] == 0){
            continue;
        }
        Color color = colors[map[i]];
        Vector2 tilePosition = IndexToGridPos(i);
        SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
        SDL_Rect rectangle = {tilePosition.x * gridSize, tilePosition.x * gridSize, gridSize, gridSize};
        SDL_RenderFillRect(renderer, &rectangle);
    }
    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                goto done;
        }
    }
done:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
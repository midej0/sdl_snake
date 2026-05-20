#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "structs.h"
#include "player.h"
#include "map.h"
#include "spawn.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    CreateEmptyMap(30, 20);

    Player player(Vector2{columns / 2, rows / 2}, Vector2{0, -1}, 100, 1, 500);
    std::map<int, Color> colors = {
        {1, Color{255, 255, 255, 255}},
        {2, Color{255, 0, 0, 255}}};

    bool running = true;
    int gridSize = 35;

    SpawnFruit();

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake", 0, 0, gridSize * columns, gridSize * rows, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                goto done;

            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    player.SetVelocity(Vector2{0, -1});
                    break;
                case SDLK_DOWN:
                    player.SetVelocity(Vector2{0, 1});
                    break;
                case SDLK_LEFT:
                    player.SetVelocity(Vector2{-1, 0});
                    break;
                case SDLK_RIGHT:
                    player.SetVelocity(Vector2{1, 0});
                    break;
                }
            }
        }

        player.Tick(SDL_GetTicks64());

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < columns * rows; i++)
        {
            if (map[i] == 0)
            {
                continue;
            }
            Color color = colors[map[i]];
            Vector2 tilePosition = IndexToGridPos(i);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
            SDL_Rect rectangle = {tilePosition.x * gridSize, tilePosition.y * gridSize, gridSize, gridSize};
            SDL_RenderFillRect(renderer, &rectangle);
        }
        SDL_RenderPresent(renderer);

        if (!player.GetAlive())
        {
            goto done;
        }
    }
done:
    DeleteMapPointer();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
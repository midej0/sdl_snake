#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{

    bool running = true;
    int columns = 10;
    int rows = 10;
    int gridSize = 40;
    int map[10][10];

    // Create empty map
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            map[i][j] = rand() % 2;
        }
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake", 0, 0, gridSize * columns, gridSize * rows, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            int value = map[i][j];
            if (value == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }
            else if (value == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
            std::cout << "x: " << i * gridSize << " Y: " << j * gridSize << " Value: " << map[i][j] << "\n";
            SDL_Rect rectangle = {i * gridSize, j * gridSize, gridSize, gridSize};
            SDL_RenderFillRect(renderer, &rectangle);
        }
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
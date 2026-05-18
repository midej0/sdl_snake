#include <cstdlib>
#include "structs.h"
#include "map.h"
#include "player.h"

Player player(Vector2{5, 5}, Vector2{0, -1}, 50, 20);

void Tick(uint64_t timeElapsed)
{
    if (timeElapsed >= player.GetLastMoveTime() + player.GetMoveTime())
    {
        player.Move(timeElapsed);
    }
}

void SpawnFruit()
{
    map[rand() % (columns * rows)] = 2;
}
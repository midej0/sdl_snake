#include <cstdlib>
#include "structs.h"
#include "map.h"

void SpawnFruit()
{
    map[rand() % (columns * rows)] = 2;
}
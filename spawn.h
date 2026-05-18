#pragma once

#include <cstdlib>
#include "map.h"


void SpawnFruit()
{
    int pos = rand() % (columns * rows);
    while(map[pos] != 0){
        pos = rand() % (columns * rows);
    }
    map[pos] = 2;
}
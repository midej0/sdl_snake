#pragma once

#include "structs.h"

int columns;
int rows;
int *map;

Vector2 IndexToGridPos(int index)
{
    return Vector2{index / rows, index % rows};
}

int GridPosToIndex(Vector2 pos)
{
    return (pos.x * rows) + pos.y;
}

void CreateEmptyMap(int c, int r)
{
    columns = c;
    rows = r;
    map = new int[c * r];
    for (int i = 0; i < c * r; i++)
    {
        map[i] = 0;
    }
}

void DeleteMapPointer()
{
    delete[] map;
}
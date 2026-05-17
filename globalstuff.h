#include <cmath>

int columns;
int rows;
int *map;

struct Color
{
    int red;
    int green;
    int blue;
    int alpha;
};

struct Vector2
{
    int x;
    int y;
};

Vector2 IndexToGridPos(int index)
{
    return Vector2{index/rows, index % rows};
}

void CreateEmptyMap(int r, int c)
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
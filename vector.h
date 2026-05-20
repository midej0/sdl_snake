#include <cmath>

class Vector2
{
    int x;
    int y;

    Vector2(int x, int y){
        this->x = x;
        this->y = y;
    }

    float Magnitude(){
        return sqrt(pow(x, 2), pow(y, 2));
    }
};
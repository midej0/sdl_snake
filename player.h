#pragma once

#include <cstdlib>
#include <vector>
#include "spawn.h"
#include "structs.h"
#include "map.h"

class Player
{
private:
    Vector2 headPosition;
    Vector2 velocity;
    Vector2 sceduledVelocity = Vector2{0, 0};
    uint64_t lastMoveTime = 0;
    int moveTime;
    int length;
    std::vector<Vector2> bodyPositions;

public:
    Player(Vector2 headPosition, Vector2 velocity, int moveTime, int length)
    {
        this->headPosition = headPosition;
        this->velocity = velocity;
        this->moveTime = moveTime;
        this->length = length;
        bodyPositions.resize(length, headPosition);
    }

    void Move(uint64_t time)
    {
        velocity = sceduledVelocity;
        headPosition.x += velocity.x;
        headPosition.y += velocity.y;

        map[GridPosToIndex(bodyPositions.back())] = 0;
        if (map[GridPosToIndex(headPosition)] != 2)
        {
            bodyPositions.pop_back();
        }
        else if (map[GridPosToIndex(headPosition)] == 2)
        {
            length++;
            SpawnFruit();
        }
        bodyPositions.insert(bodyPositions.begin(), headPosition);
        map[GridPosToIndex(headPosition)] = 1;
        lastMoveTime = time;
    }

    void SetVelocity(Vector2 newVel)
    {
        if (velocity.x == 0 && newVel.x != 0)
        {
            sceduledVelocity = newVel;
        }
        else if (velocity.y == 0 && newVel.y != 0)
        {
            sceduledVelocity = newVel;
        }
    }

    int GetMoveTime()
    {
        return moveTime;
    }

    uint64_t GetLastMoveTime()
    {
        return lastMoveTime;
    }

    std::vector<Vector2> GetBodyPositions()
    {
        return bodyPositions;
    }
};
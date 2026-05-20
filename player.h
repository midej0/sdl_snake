#pragma once

#include <cstdlib>
#include <vector>
#include "spawn.h"
#include "structs.h"
#include "map.h"

class Player
{
private:
    std::vector<Vector2> bodyPositions;
    Vector2 headPosition;
    Vector2 velocity;
    Vector2 sceduledVelocity;
    uint64_t lastMoveTime = 0;
    int graceTime;
    int graceTriggerTime;
    int moveTime;
    int length;
    bool alive;
    bool hittingObstacle;

public:
    Player(Vector2 headPosition, Vector2 velocity, int moveTime, int length, int graceTime)
    {
        this->headPosition = headPosition;
        this->velocity = velocity;
        this->sceduledVelocity = velocity;
        this->moveTime = moveTime;
        this->length = length;
        this->graceTime = graceTime;
        hittingObstacle = false;
        alive = true;
        bodyPositions.resize(length, headPosition);
    }

    void Tick(uint64_t time)
    {
        if (time >= lastMoveTime + moveTime)
        {
            Move(time);
        }
        TickGrace(time);
    }

    void Move(uint64_t time)
    {
        Vector2 newHeadPos = headPosition;
        velocity = sceduledVelocity;
        newHeadPos.x += velocity.x;
        newHeadPos.y += velocity.y;

        if (map[GridPosToIndex(newHeadPos)] == 1 || newHeadPos.x * newHeadPos.y < 0 || newHeadPos.y >= rows || newHeadPos.x >= columns)
        {
            TriggerGrace(time);
        }
        else
        {
            hittingObstacle = false;
        }

        if (!hittingObstacle)
        {
            headPosition = newHeadPos;
            map[GridPosToIndex(bodyPositions.back())] = 0;
            switch (map[GridPosToIndex(headPosition)])
            {
            case 0:
                bodyPositions.pop_back();
                break;
            case 2:
                length++;
                SpawnFruit();
                break;
            }
            if (map[GridPosToIndex(headPosition)] != 2)
            {
            }
            else if (map[GridPosToIndex(headPosition)] == 2)
            {
            }
            bodyPositions.insert(bodyPositions.begin(), headPosition);
            map[GridPosToIndex(headPosition)] = 1;
        }
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

    void TriggerGrace(uint64_t time)
    {
        if (!hittingObstacle)
        {
            hittingObstacle = true;
            graceTriggerTime = time;
        }
    }

    void TickGrace(uint64_t time)
    {
        if (time >= graceTriggerTime + graceTime && hittingObstacle)
        {
            alive = false;
        }
    }

    int GetMoveTime()
    {
        return moveTime;
    }

    bool GetAlive()
    {
        return alive;
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
#pragma once

#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct TransformComponent
{
    com::Vec2i position;
    com::Vec2i positionPrev = position;
    com::Vec2i positionTarget = position;
    com::Vec2i size;

    void MoveToTarget();
    auto InterpolatedPosition(double time, double timeMax);
};

///////////////////////////////////////////////////////////

void TransformComponent::MoveToTarget()
{
    positionPrev = position; //!

    auto deltaX = positionTarget.x - position.x;
    auto deltaY = positionTarget.y - position.y;
    f32 spd = 4;

    if (deltaX > 0) 
    {
        position.x += spd;
        auto tmpX = positionTarget.x - position.x;
        if (tmpX <= 0)
            position.x = positionTarget.x;
    }
    else if (deltaX < 0)
    {
        position.x -= spd;
        auto tmpX = positionTarget.x - position.x;
        if (tmpX >= 0)
            position.x = positionTarget.x;
    } 

    if (deltaY > 0) 
    {
        position.y += spd;
        auto tmpY = positionTarget.y - position.y;
        if (tmpY <= 0)
            position.y = positionTarget.y;
    }
    else if (deltaY < 0)
    {
        position.y -= spd;
        auto tmpY = positionTarget.y - position.y;
        if (tmpY >= 0)
            position.y = positionTarget.y;
    } 

    //test
    if (position == positionTarget)
    {
        positionTarget.x = rand() % 600;
        positionTarget.y = rand() % 400;
    }
}

///////////////////////////////////////////////////////////

auto TransformComponent::InterpolatedPosition(double time, double timeMax)
{
    i32 x = positionPrev.x + (position.x - positionPrev.x) * (time / timeMax);
    i32 y = positionPrev.y + (position.y - positionPrev.y) * (time / timeMax);
    return com::Vec2i { x, y };
}

///////////////////////////////////////////////////////////

}//ns
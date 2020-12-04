#pragma once

#include <cmath>
#include "com/Vec.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct TransformComponent
{
    Vec2i position;
    Vec2i positionPrev = position;
    Vec2i positionTarget = position;
    Vec2i size;

    void MoveToTarget();
    auto InterpolatedPosition(double time, double timeMax);
};

///////////////////////////////////////////////////////////

void TransformComponent::MoveToTarget()
{
    positionPrev = position; //!

    auto deltaX = positionTarget.x - position.x;
    auto deltaY = positionTarget.y - position.y;
    f32 spd = 1;

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
        positionTarget.x = rand() % app::windowWidth / 2;
        positionTarget.y = rand() % app::windowHeight / 2;
    }
}

///////////////////////////////////////////////////////////

auto TransformComponent::InterpolatedPosition(double time, double timeMax)
{
    f32 x = positionPrev.x + (position.x - positionPrev.x) * (time / timeMax);
    f32 y = positionPrev.y + (position.y - positionPrev.y) * (time / timeMax);
    return Vec2f { x, y };
}

///////////////////////////////////////////////////////////

}//ns
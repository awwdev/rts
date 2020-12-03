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
    Vec2i size;
    Vec2i positionTarget = position;

    void MoveToTarget();
};

///////////////////////////////////////////////////////////

void TransformComponent::MoveToTarget()
{
    auto delta = positionTarget - position;
    if (delta.x > 0) position.x++;
    if (delta.x < 0) position.x--;
    if (delta.y > 0) position.y++;
    if (delta.y < 0) position.y--;

    //test
    if (position == positionTarget)
    {
        positionTarget.x = rand() % app::windowWidth;
        positionTarget.y = rand() % app::windowHeight;
    }
}

///////////////////////////////////////////////////////////

//TODO lockstep
//TODO delta time (interpolation)

}//ns
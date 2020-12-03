#pragma once

#include <cmath>
#include "com/Vec.hpp"

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
}

///////////////////////////////////////////////////////////

//TODO lockstep
//TODO delta time for interpolation

}//ns
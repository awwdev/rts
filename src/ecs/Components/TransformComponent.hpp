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
    position.x += delta.x / 10.f; //this is not precise since int
    position.y += delta.y / 10.f;
}

///////////////////////////////////////////////////////////

//TODO fixed point math, lockstep
//TODO delta time for interpolation

}//ns
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

    auto delta = positionTarget - position;
    if (delta.x > 0) position.x += 4;
    if (delta.x < 0) position.x -= 4;
    if (delta.y > 0) position.y += 4;
    if (delta.y < 0) position.y -= 4;

    //test
    //if (position == positionTarget)
    //{
    //    positionTarget.x = rand() % app::windowWidth;
    //    positionTarget.y = rand() % app::windowHeight;
    //}
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
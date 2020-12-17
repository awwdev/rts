#pragma once

#include "com/Vec.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct RenderComponent
{
    u32 texIndex;
    u32 texIndexEnd = 4;
    f32 time = 0;
    f32 frameTime = 0.2;

    void Animate();
};

///////////////////////////////////////////////////////////

void RenderComponent::Animate()
{
    time += app::Time::dt;
    if (time > frameTime)
    {
        time = 0;
        texIndex += 1;
        texIndex %= texIndexEnd;
    } 
}

///////////////////////////////////////////////////////////

}//ns
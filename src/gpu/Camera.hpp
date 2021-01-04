#pragma once

#include "com/Vec.hpp"
#include "gpu/RenderData.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct Camera 
{
    i32 spd = 1;
    com::Vec2i pos {};
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void Camera::Update(RenderData& rd)
{
    if (app::IsKeyHeld('W'))
        pos.y += 1 * spd;
    if (app::IsKeyHeld('S'))
        pos.y -= 1 * spd;
    if (app::IsKeyHeld('A'))
        pos.x += 1 * spd;
    if (app::IsKeyHeld('D'))
        pos.x -= 1 * spd;

    rd.sprites.meta.cameraPos = pos;
}

///////////////////////////////////////////////////////////

//TODO smooth

}//ns
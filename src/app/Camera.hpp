#pragma once

#include "com/Vec.hpp"
#include "gpu/RenderData.hpp"
#include "app/Input/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Camera 
{
    i32 spd = 1;
    com::Vec2i pos {};
    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void Camera::Update(gpu::RenderData& rd)
{
    if (app::Inputs::keyboard.IsKeyHeld('W'))
        pos.y += 1 * spd;
    if (app::Inputs::keyboard.IsKeyHeld('S'))
        pos.y -= 1 * spd;
    if (app::Inputs::keyboard.IsKeyHeld('A'))
        pos.x += 1 * spd;
    if (app::Inputs::keyboard.IsKeyHeld('D'))
        pos.x -= 1 * spd;

    rd.sprites.meta.cameraPos = pos;
}

///////////////////////////////////////////////////////////

//TODO smooth

}//ns
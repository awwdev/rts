#pragma once

#include "com/Vec.hpp"
#include "gpu/RenderData.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct Camera 
{
    com::Vec2i pos;
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void Camera::Update(RenderData& rd)
{
    //TODO check key, update pos
    rd.sprites.meta.cameraOffset = pos;
    rd.sprites.meta.windowWidth  = app::Inputs::window.width;
    rd.sprites.meta.windowHeight = app::Inputs::window.height;
}

///////////////////////////////////////////////////////////

}//ns
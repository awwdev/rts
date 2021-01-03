#pragma once

#include "gpu/RenderDataSprites.hpp"
#include "gpu/RenderDataUI.hpp"
#include "gpu/RenderDataPost.hpp"
#include "gpu/RenderDataWire.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderData 
{
    RenderDataSprites sprites;
    RenderDataPost    post;
    RenderDataUI      ui;
    RenderDataWire    wire;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderData::Clear()
{
    sprites.Clear();
    post.Clear();
    ui.Clear();
    wire.Clear();
}

///////////////////////////////////////////////////////////

}//ns
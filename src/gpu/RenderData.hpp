#pragma once

#include "gpu/RenderDataSprites.hpp"
#include "gpu/RenderDataUI.hpp"
#include "gpu/RenderDataPost.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderData 
{
    RenderDataSprites sprites;
    RenderDataPost    post;
    RenderDataUI      ui;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderData::Clear()
{
    sprites.Clear();
    post.Clear();
    ui.Clear();
}

///////////////////////////////////////////////////////////

}//ns
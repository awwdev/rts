#pragma once

#include "gpu/RenderDataDefault.hpp"
#include "gpu/RenderDataUI.hpp"
#include "gpu/RenderDataPost.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderData 
{
    RenderData_Default renderDataDefault;
    RenderDataPost     renderDataPost;
    RenderDataUI       renderDataUI;

    void Clear();
};

///////////////////////////////////////////////////////////

void RenderData::Clear()
{
    renderDataDefault.Clear();
    renderDataPost.Clear();
    renderDataUI.Clear();
}

///////////////////////////////////////////////////////////

}//ns
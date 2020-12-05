#pragma once

#include "gpu/RenderData_Default.hpp"
#include "gpu/RenderData_UI.hpp"
#include "gpu/RenderData_Post.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderData 
{
    RenderData_Default rd_Default;
    RenderData_Post    rd_Post;
    RenderData_UI      rd_UI;
};

///////////////////////////////////////////////////////////

}//ns
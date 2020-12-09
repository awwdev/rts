#pragma once

#include "com/POD_Array.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderDataUI
{
    struct PushMeta
    {
        i32 windowHeight;
        i32 windowWidth;
    };

    struct UniformQuadData
    {
        Recti rect;
        Col4f col;
        u32   texId;
    };

    static constexpr auto QUAD_COUNT_MAX = 1000;
    com::POD_Array<UniformQuadData, QUAD_COUNT_MAX> quadData;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataUI::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
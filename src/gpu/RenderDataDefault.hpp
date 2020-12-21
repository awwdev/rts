#pragma once

#include "com/POD_Array.hpp"
#include "com/Rect.hpp"
#include "com/Color.hpp"

#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderDataDefault
{
    struct PushMeta
    {
        i32 windowWidth;
        i32 windowHeight;
    };

    struct UniformQuadData
    {
        com::Recti rect;
        com::Col4n col;
        u32 texId;
    };

    com::POD_Array<UniformQuadData, ecs::ENTITY_COUNT_MAX> quadData;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataDefault::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
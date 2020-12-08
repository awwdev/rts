#pragma once

#include "com/Vec.hpp"
#include "com/POD_Array.hpp"
#include "ecs/EntityID.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderData_Default
{
    struct Push_Meta
    {
        i32 windowWidth;
        i32 windowHeight;
    };

    struct Uniform_QuadData
    {
        Recti rect;
        Col4f col;
        u32   texId;
    };

    com::POD_Array<Uniform_QuadData, ecs::ENTITY_COUNT_MAX> quadData;

    void Clear();
};

///////////////////////////////////////////////////////////

void RenderData_Default::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
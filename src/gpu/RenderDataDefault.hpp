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
        com::Vec2f origin;
        u32 texId;
        f32 rot;
    };

    struct UniformShadowData
    {
        f32 rotation;
        f32 strength;
    };

    com::POD_Array<UniformQuadData, ecs::ENTITY_COUNT_MAX> quadData;
    UniformShadowData shadowData;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataDefault::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
#pragma once

#include "com/Array.hpp"
#include "com/Rect.hpp"
#include "com/Color.hpp"

#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderDataSprites
{
    struct PushMeta
    {
        i32 windowWidth;
        i32 windowHeight;
    };

    struct UniformQuadData
    {
        com::Rectf rect;
        com::Col4n col;
        com::Vec2f origin;
        u32 texId;
        f32 rot;
        bool flipped;
    };

    struct UniformShadowData
    {
        f32 rotation;
        f32 strength;
    };

    com::Array<UniformQuadData, ecs::ENTITY_COUNT_MAX> quadData;
    UniformShadowData shadowData;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataSprites::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
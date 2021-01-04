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
    struct PushContext
    {
        i32 windowWidth;
        i32 windowHeight;
    };

    struct UniformMeta
    {
        com::Vec2i cameraPos;
    };

    struct UniformQuad
    {
        com::Rectf rect;
        com::Col4n col;
        com::Vec2f origin;
        u32 texId;
        f32 rot;
        bool flipped;
    };

    struct UniformSun
    {
        f32 rotation;
        f32 strength;
    };

    com::Array<UniformQuad, ecs::ENTITY_COUNT_MAX> quads;
    UniformSun sun;
    UniformMeta meta;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataSprites::Clear()
{
    quads.count = 0;
}

///////////////////////////////////////////////////////////

}//ns
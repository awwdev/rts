#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderDataSprites.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderDataSprites& rd, f32 stepProgress)
{
    auto& mainComponents = arrays.mainComponents;
    auto& dense = mainComponents.dense;

    //?animate
    FOR_ARRAY(dense, i)
    {
        auto& mainComponent = dense[i];
        mainComponent.sprite.Animate();
    }

    //?shadow
    //rd.shadowData.rotation += app::Time::dt;
    rd.sun.rotation = 5;
    rd.sun.strength = 0.5;

    //?sort
    for(idx_t i = 0; i < dense.count - 1; ++i)
    {
        auto j = i;
        while (dense[j].transform.pos.y > dense[j+1].transform.pos.y)
        {
            mainComponents.Swap(j, j+1);
            if (j == 0) break;
            j -= 1;
        }
    }

    //?default
    FOR_ARRAY(dense, i)
    {
        auto& mainComponent = dense[i];
        auto& trans  = mainComponent.transform;
        auto lerpPos = trans.posPrev + (trans.pos - trans.posPrev) * stepProgress;
        auto& sprite = mainComponent.sprite;
        com::Rectf rect { lerpPos, trans.size }; 
        com::Col4n COLOR { 1, 1, 1, 1 };
        bool flipped = trans.delta.x < 0;
        rd.quads.Append(rect, COLOR, com::Vec2f { 0.5, 0.5 }, sprite.texIdx, trans.rot, flipped);
    }
}

///////////////////////////////////////////////////////////

}//ns
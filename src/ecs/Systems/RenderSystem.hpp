#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderDataDefault.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderDataDefault& rd)
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
    static f32 shadowRot = 3.14 * 3.f;
    shadowRot += app::Time::dt;

    FOR_ARRAY(dense, i)
    {
        auto& mainComponent = dense[i];
        auto& trans  = mainComponent.transform;
        auto& sprite = mainComponent.sprite;

        com::Vec2i pos { trans.pos.x, trans.pos.y + 10 };
        com::Recti rect { pos, trans.size }; 
        com::Col4n COLOR { 0, 0, 0, 1 };
        rd.quadData.Append(rect, COLOR, com::Vec2f { 0.5, 0.75 }, sprite.texIdx, shadowRot);
    }

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
        auto& sprite = mainComponent.sprite;
        com::Recti rect { trans.pos, trans.size }; 
        com::Col4n COLOR { 1, 1, 1, 1 };
        rd.quadData.Append(rect, COLOR, com::Vec2f { 0.5, 0.5 }, sprite.texIdx, trans.rot);
    }
}

///////////////////////////////////////////////////////////

}//ns
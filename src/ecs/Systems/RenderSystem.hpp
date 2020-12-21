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

    //sort
    for(idx_t i = 0; i < dense.count - 1; ++i)
    {
        auto j = i;
        while (dense[j].pos.y > dense[j+1].pos.y)
        {
            mainComponents.Swap(j, j+1);
            if (j == 0) break;
            j -= 1;
        }
    }

    //add render data
    FOR_ARRAY(dense, i)
    {
        auto& mainComponent = dense[i];
        com::Recti rect { mainComponent.pos, mainComponent.size }; 
        com::Col4n COLOR { 1, 1, 1, 1 };
        rd.quadData.Append(rect, COLOR, mainComponent.texIdx);
    }
}

///////////////////////////////////////////////////////////

}//ns
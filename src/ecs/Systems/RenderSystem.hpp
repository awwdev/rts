#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "app/Lockstep.hpp"
#include "com/Print.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

inline com::POD_Array<ID, ecs::ENTITY_COUNT_MAX> depthSorted [1024];
inline double time = 0;

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderData& renderData, app::Lockstep& lockstep)
{
    auto& transformComponents = arrays.transformComponents;
    auto& renderComponents = arrays.renderComponents;

    /*
    FOR_ARRAY(renderComponents.dense, denseID)
    {
        auto& renderComponent = renderComponents.dense[denseID];
        auto  entityID = renderComponents.GetEntity(denseID);
        auto& transformComponent = transformComponents.GetComponent(entityID);

        Recti rect { transformComponent.position, transformComponent.size };
        Col4f COLOR = { 1, 1, 1, 1 };
        auto texId = renderComponent.texIndex;

        renderData.renderDataDefault.ubo.Append(rect, COLOR, texId);
    }
    */


    FOR_C_ARRAY(depthSorted, i)
    {
        depthSorted[i].count = 0;
    }
    FOR_ARRAY(transformComponents.dense, i)
    {
        auto& transformComponent = transformComponents.dense[i];
        auto  y = (i32)(transformComponent.position.y + transformComponent.size.y);
        //subtract the camera pos to "normalize"
        if (y < 0 || y >= 1024) continue; //basic culling
        depthSorted[y].Append(transformComponents.GetEntity(i));
    }
    FOR_C_ARRAY(depthSorted, y)
    {
        auto& entityIDs = depthSorted[y];
        FOR_ARRAY(entityIDs, i)
        {
            auto& entityID = entityIDs[i];
            auto& transformComponent = transformComponents.GetComponent(entityID);

            if (time < lockstep.stepTimePrev)
                time += app::glo::dt;
            time = com::Min(time, lockstep.stepTimePrev);
            if (lockstep.nextStep)
                time = 0;
                
            auto  p = transformComponent.InterpolatedPosition(time, lockstep.stepTimePrev);
            auto& s = transformComponent.size;
            Recti rect { p, s };

            auto& renderComponent = arrays.renderComponents.GetComponent(entityID);
            renderComponent.Animate();
            auto& t = renderComponent.texIndex;

            constexpr Col4f COLOR = { 1, 1, 1, 1 };
            renderData.renderDataDefault.quadData.Append(rect, COLOR, t);
        }
    }
}

///////////////////////////////////////////////////////////

//! coupling of y array size and max window heigth
//! size depends much on max entity count

}//ns
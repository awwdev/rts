#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "app/Lockstep.hpp"
#include "com/Print.hpp"
#include "com/Utils.hpp"
#include "mem/Memory.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct RenderSystem
{
    struct DepthSorted { com::POD_Array<ID, ecs::ENTITY_COUNT_MAX> depthSorted [1024]; };
    mem::BlockPtr<DepthSorted> ptrDepthSorted;
    double time = 0;

    void Update(ComponentArrays&, gpu::RenderData&, app::Lockstep&);
    RenderSystem();
};

///////////////////////////////////////////////////////////

RenderSystem::RenderSystem()
{
    ptrDepthSorted = mem::ClaimBlock<DepthSorted>();
}

///////////////////////////////////////////////////////////

void RenderSystem::Update(ComponentArrays& arrays, gpu::RenderData& renderData, app::Lockstep& lockstep)
{
    auto& depthSorted = ptrDepthSorted->depthSorted;
    auto& transformComponents = arrays.transformComponents;
    auto& renderComponents = arrays.renderComponents;

    /*
    FOR_ARRAY(renderComponents.dense, denseID)
    {
        auto& renderComponent = renderComponents.dense[denseID];
        auto  entityID = renderComponents.GetEntity(denseID);
        auto& transformComponent = transformComponents.GetComponent(entityID);

        com::Recti rect { transformComponent.position, transformComponent.size };
        Col4n COLOR = { 1, 1, 1, 1 };
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
                time += app::Time::dt;
            time = com::Min(time, lockstep.stepTimePrev);
            if (lockstep.nextStep)
                time = 0;
                
            auto  p = transformComponent.InterpolatedPosition(time, lockstep.stepTimePrev);
            auto& s = transformComponent.size;
            com::Recti rect { p, s };

            auto& renderComponent = arrays.renderComponents.GetComponent(entityID);
            renderComponent.Animate();
            auto& t = renderComponent.texIndex;

            constexpr Col4n COLOR = { 1, 1, 1, 1 };
            renderData.renderDataDefault.quadData.Append(rect, COLOR, t);
        }
    }
}

///////////////////////////////////////////////////////////

//! coupling of y array size and max window heigth
//! size depends much on max entity count

}//ns
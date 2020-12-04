#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "app/Lockstep.hpp"
#include "com/Print.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

inline com::Array<ID, ecs::ENTITY_COUNT_MAX> depthSorted [1024];
inline double time = 0;

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderData& renderData, app::Lockstep& lockstep)
{
    auto& vertices = renderData.defaultRenderData.vertices;
    vertices.count = 0;

    auto& transformComponents = arrays.transformComponents.dense;
    auto& renderComponents = arrays.renderComponents.dense;

    FOR_C_ARRAY(depthSorted, i)
    {
        depthSorted[i].count = 0;
    }
    FOR_ARRAY(transformComponents, i)
    {
        auto& transformComponent = transformComponents[i];
        auto  y = transformComponent.position.y + transformComponent.size.y;
        //subtract the camera pos to "normalize"
        if (y < 0) continue;
        //cull objects that are outside camera
        depthSorted[y].Append(arrays.transformComponents.GetEntity(i));
    }
    FOR_C_ARRAY(depthSorted, y)
    {
        auto& entityIDs = depthSorted[y];
        FOR_ARRAY(entityIDs, i)
        {
            auto& entityID = entityIDs[i];
            auto& transformComponent = arrays.transformComponents.GetComponent(entityID);

            if (time < lockstep.stepTimePrev)
                time += app::dt;
            time = com::Min(time, lockstep.stepTimePrev);
            if (lockstep.nextStep)
                time = 0;
            auto p = transformComponent.InterpolatedPosition(time, lockstep.stepTimePrev);

            auto& s = transformComponent.size;
            auto& renderComponent = arrays.renderComponents.GetComponent(entityID);
            auto& t = renderComponent.textureId;

            constexpr Col4f COLOR = { 1, 1, 1, 1 };
            
            vertices.Append(p.x      , p.y      , COLOR, t);
            vertices.Append(p.x + s.x, p.y      , COLOR, t);
            vertices.Append(p.x + s.x, p.y + s.y, COLOR, t);
            vertices.Append(p.x      , p.y + s.y, COLOR, t);
        }
        
    }
}

///////////////////////////////////////////////////////////

//! coupling of y array size and max window heigth
//! size depends much on max entity count

}//ns
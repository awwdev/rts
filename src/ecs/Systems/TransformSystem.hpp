#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void TransformSystem(ComponentArrays& arrays, gpu::RenderData& renderData)
{
    auto& transformComponents = arrays.transformComponents.dense;
    FOR_ARRAY(transformComponents, i)
    {
        auto& transformComponent = transformComponents[i];
        transformComponent.MoveToTarget();
    }
}

///////////////////////////////////////////////////////////

}//ns
#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::ecs {

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderData& renderData)
{
    auto& vertices = renderData.defaultRenderData.vertices;
    auto& mainComponents = arrays.mainComponents.dense;

    vertices.count = 0;
    FOR_ARRAY(mainComponents, i)
    {
        auto& mainComponent = mainComponents[i];
        auto& p = mainComponent.pos;
        auto& s = mainComponent.size;

        vertices.Append(p.x + 0.f, p.y + 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f);
        vertices.Append(p.x + s.x, p.y + 0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f);
        vertices.Append(p.x + s.x, p.y + s.y, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
        vertices.Append(p.x + 0.f, p.y + s.y, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
    }
}

///////////////////////////////////////////////////////////

}//ns
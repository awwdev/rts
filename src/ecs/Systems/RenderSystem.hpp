#pragma once

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void RenderSystem(ComponentArrays& arrays, gpu::RenderData& renderData)
{
    auto& vertices = renderData.defaultRenderData.vertices;
    auto& mainComponents = arrays.mainComponents.dense;

    vertices.count = 0;
    FOR_ARRAY(mainComponents, i)
    {
        //TODO sort by y

        auto& mainComponent = mainComponents[i];
        auto& p = mainComponent.pos;
        auto& s = mainComponent.size;
        auto& t = mainComponent.textureId;

        vertices.Append(p.x + 0.f, p.y + 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, t);
        vertices.Append(p.x + s.x, p.y + 0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, t);
        vertices.Append(p.x + s.x, p.y + s.y, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, t);
        vertices.Append(p.x + 0.f, p.y + s.y, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, t);
    }
}

///////////////////////////////////////////////////////////

}//ns
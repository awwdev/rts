#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"
#include "gpu/vuk/States/Post/Wire/WireVertices.hpp"
#include "gpu/vuk/States/Post/PostUniforms.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePipelineWire(
Pipeline& pipeline, 
FragVertShader& shader, 
VerticesWire& vertices,
UniformsPost& uniforms,
RenderPass& renderPass)
{
    PipelineInfo pipelineInfo;
    pipelineInfo.vertexInput = VertexInput(
        vertices.bindings, array_extent(vertices.bindings), 
        vertices.attributes, array_extent(vertices.attributes)
    );
    pipelineInfo.inputAssembly = InputAssembly(VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
    pipelineInfo.viewportState = ViewportState(renderPass.width, renderPass.height);
    pipelineInfo.multisampling = Multisampling();
    pipelineInfo.rasterization = Rasterization(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, 4.f);
    pipelineInfo.depthStencil  = DepthStencil();
    pipelineInfo.blendState    = BlendStateInfo();
    pipelineInfo.layoutInfo    = PipelineLayout(
        nullptr, 0,
        &uniforms.ctx.rangeInfo, 1
    );

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
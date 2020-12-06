#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"

#include "gpu/vuk/States/UI/UIVertices.hpp"
#include "gpu/vuk/States/UI/UIUniforms.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePipelineUI(
Pipeline& pipeline, 
UIVertices& vertices,
UIUniforms& uniforms,
Shader& shader, 
RenderPass& renderPass)
{
    PipelineInfo pipelineInfo;
    pipelineInfo.vertexInput = VertexInput(vertices.bindings, vertices.attributes);
    pipelineInfo.inputAssembly = InputAssembly();
    pipelineInfo.viewportState = ViewportState(renderPass.width, renderPass.height);
    pipelineInfo.multisampling = Multisampling();
    pipelineInfo.rasterization = Rasterization();
    pipelineInfo.depthStencil = DepthStencil();
    pipelineInfo.blendState = BlendStateInfo();
    pipelineInfo.layoutInfo = PipelineLayout(
        //!&uniforms.descriptors.layout, 1
        //&uniforms.pushConstants.rangeInfo, 1
    );

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
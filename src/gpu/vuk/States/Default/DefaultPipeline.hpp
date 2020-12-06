#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"
#include "gpu/vuk/States/Default/DefaultVertices.hpp"
#include "gpu/vuk/States/Default/DefaultUniforms.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePipelineDefault(
Pipeline& pipeline, 
DefaultVertices& vertices,
DefaultUniforms& uniforms,
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
        &uniforms.descriptors.layout, 1,
        &uniforms.pushConstants.rangeInfo, 1
    );

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
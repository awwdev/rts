#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"

#include "gpu/vuk/States/Post/PostVertices.hpp"
#include "gpu/vuk/States/Post/PostUniforms.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePostPipeline(
Pipeline& pipeline, 
PostVertices& vertices,
PostUniforms& uniforms,
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
    pipelineInfo.layoutInfo = PipelineLayout();

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
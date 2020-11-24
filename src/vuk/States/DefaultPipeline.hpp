#pragma once

#include "vuk/Wrappers/Pipeline.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline void DefaultPipeline(Pipeline& pipeline, Shader& shader, RenderPass& renderPass)
{
    PipelineInfo pipelineInfo
    {
        .vertexInput = VertexInput(),
        .inputAssembly = InputAssembly(),
        .viewportState = ViewportState(renderPass.width, renderPass.height),
        .multisampling = Multisampling(),
        .rasterization = Rasterization(),
        .depthStencil = DepthStencil(),
        .blendState = BlendStateInfo(),
        .layoutInfo = PipelineLayout(),
    };
    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
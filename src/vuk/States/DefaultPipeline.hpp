#pragma once

#include "vuk/Wrappers/Pipeline.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline void DefaultPipeline(Pipeline& pipeline, Shader& shader, RenderPass& renderPass)
{
    PipelineInfo pipelineInfo;
    
    pipelineInfo.vertexInput = VertexInput();
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
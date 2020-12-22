#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"
#include "gpu/vuk/States/Sprites/SpritesUniforms.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePipelineSprites(
Pipeline& pipeline, 
SpritesUniforms& uniforms,
Shader& shader, 
RenderPass& renderPass)
{
    PipelineInfo pipelineInfo;
    
    pipelineInfo.vertexInput   = VertexInput();
    pipelineInfo.inputAssembly = InputAssembly();
    pipelineInfo.viewportState = ViewportState(renderPass.width, renderPass.height);
    pipelineInfo.multisampling = Multisampling();
    pipelineInfo.rasterization = Rasterization();
    pipelineInfo.depthStencil  = DepthStencil();
    pipelineInfo.blendState    = BlendStateInfo();
    pipelineInfo.layoutInfo    = PipelineLayout(
        &uniforms.descriptors.layout, 1,
        &uniforms.metaData.rangeInfo, 1
    );

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
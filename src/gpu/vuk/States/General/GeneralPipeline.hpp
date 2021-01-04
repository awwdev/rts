#pragma once

#include "gpu/vuk/Wrappers/Pipeline.hpp"
#include "gpu/vuk/States/General/Sprites/SpritesUniforms.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreateGeneralPipeline(
Pipeline& pipeline, 
UniformsSprites& uniforms,
FragVertShader& shader, 
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
         uniforms.descriptors.layouts.data, uniforms.descriptors.layouts.count,
        &uniforms.ctx.rangeInfo, 1
    );

    pipeline.Create(shader, renderPass, pipelineInfo);
}

///////////////////////////////////////////////////////////

}//ns
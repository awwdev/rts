#pragma once

#include "gpu/vuk/States/Default/DefaultShader.hpp"
#include "gpu/vuk/States/Default/DefaultPipeline.hpp"
#include "gpu/vuk/States/Default/DefaultRenderPass.hpp"
#include "gpu/vuk/States/Default/DefaultUniforms.hpp"

#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/RenderDataDefault.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateDefault
{
    Pipeline pipeline;
    Pipeline pipelineShadow;
    Pipeline pipelineShadowOff;
    Shader shader;
    Shader shaderShadow;
    Shader shaderShadowOff;
    DefaultRenderPass renderPass;
    DefaultUniforms uniforms;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderDataDefault&);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateDefault::Create(Context& context, Commands& commands, res::Resources& resources)
{
    renderPass.Create(commands.pool, context.swapchain);
    uniforms.Create(commands.pool, resources, renderPass);
    CreateShaderDefault(shader);
    CreateShaderDefaultShadow(shaderShadow);
    CreateShaderDefaultShadowOff(shaderShadowOff);
    CreatePipelineDefault(pipeline, uniforms, shader, renderPass);
    CreatePipelineDefaultShadow(pipelineShadow, uniforms, shaderShadow, renderPass);
    CreatePipelineDefaultShadowOff(pipelineShadowOff, uniforms, shaderShadowOff, renderPass);
}

///////////////////////////////////////////////////////////

void StateDefault::Destroy()
{
    uniforms.Destroy();
    pipeline.Destroy();
    pipelineShadow.Destroy();
    pipelineShadowOff.Destroy();
    renderPass.Destroy();
    shader.Destroy();
    shaderShadow.Destroy();
    shaderShadowOff.Destroy();
}

///////////////////////////////////////////////////////////

void StateDefault::Update(RenderDataDefault& rd)
{
    uniforms.Update(rd);
}

///////////////////////////////////////////////////////////

void StateDefault::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    //?shadow
    vkCmdPushConstants      (cmdBuffer, pipelineShadow.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadow.pipeline);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadow.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.shadowBeginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0); //draw max since one time recording
    vkCmdEndRenderPass      (cmdBuffer);

    //?shadowOff



    //?sprites
    
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);

    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadowOff.pipeline);
    vkCmdDraw               (cmdBuffer, 3, 1, 0, 0);

    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0); //draw max since one time recording

    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
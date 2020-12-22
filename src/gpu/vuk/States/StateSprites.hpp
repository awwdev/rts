#pragma once

#include "gpu/vuk/States/Sprites/SpritesShader.hpp"
#include "gpu/vuk/States/Sprites/SpritesPipeline.hpp"
#include "gpu/vuk/States/Sprites/SpritesRenderPass.hpp"
#include "gpu/vuk/States/Sprites/SpritesUniforms.hpp"

#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/RenderDataSprites.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateSprites
{
    Pipeline pipeline;
    Pipeline pipelineShadow;
    Pipeline pipelineShadowOff;
    Shader shader;
    Shader shaderShadow;
    Shader shaderShadowOff;
    SpritesRenderPass renderPass;
    SpritesUniforms uniforms;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderDataSprites&);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateSprites::Create(Context& context, Commands& commands, res::Resources& resources)
{
    renderPass.Create(commands.pool, context.swapchain);
    uniforms.Create(commands.pool, resources, renderPass);
    CreateShaderSprites(shader);
    CreateShaderSpritesShadow(shaderShadow);
    CreateShaderShadows(shaderShadowOff);
    CreatePipelineSprites(pipeline, uniforms, shader, renderPass);
    CreatePipelineSpritesShadow(pipelineShadow, uniforms, shaderShadow, renderPass);
    CreatePipelineShadows(pipelineShadowOff, uniforms, shaderShadowOff, renderPass);
}

///////////////////////////////////////////////////////////

void StateSprites::Destroy()
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

void StateSprites::Update(RenderDataSprites& rd)
{
    uniforms.Update(rd);
}

///////////////////////////////////////////////////////////

void StateSprites::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    //?shadow
    vkCmdPushConstants      (cmdBuffer, pipelineShadow.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadow.pipeline);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadow.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.shadowBeginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);

    //?sprites
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadowOff.pipeline);
    vkCmdDraw               (cmdBuffer, 3, 1, 0, 0);

    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
#pragma once

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
    Pipeline pipelineSprites;
    Pipeline pipelineSpritesShadows;
    Pipeline pipelineShadows;
    Shader shaderSprites;
    Shader shaderSpritesShadows;
    Shader shaderShadows;
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
    shaderSprites.Create("res/Shaders/spv/sprite.vert.spv", "res/Shaders/spv/sprite.frag.spv");
    shaderSpritesShadows.Create("res/Shaders/spv/spriteShadow.vert.spv", "res/Shaders/spv/spriteShadow.frag.spv");
    shaderShadows.Create("res/Shaders/spv/shadows.vert.spv", "res/Shaders/spv/shadows.frag.spv");
    CreatePipelineSprites(pipelineSprites, uniforms, shaderSprites, renderPass);
    CreatePipelineSprites(pipelineSpritesShadows, uniforms, shaderSpritesShadows, renderPass);
    CreatePipelineSprites(pipelineShadows, uniforms, shaderShadows, renderPass);
}

///////////////////////////////////////////////////////////

void StateSprites::Destroy()
{
    uniforms.Destroy();
    pipelineSprites.Destroy();
    pipelineSpritesShadows.Destroy();
    pipelineShadows.Destroy();
    renderPass.Destroy();
    shaderSprites.Destroy();
    shaderSpritesShadows.Destroy();
    shaderShadows.Destroy();
}

///////////////////////////////////////////////////////////

void StateSprites::Update(RenderDataSprites& rd)
{
    uniforms.Update(rd);
}

///////////////////////////////////////////////////////////

void StateSprites::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdPushConstants      (cmdBuffer, pipelineSprites.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSprites.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    //sprite shadows
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.shadowBeginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSpritesShadows.pipeline);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
    //shadows
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadows.pipeline);
    vkCmdDraw               (cmdBuffer, 3, 1, 0, 0);
    //sprites
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSprites.pipeline);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

//TODO base pipeline / cache (?)

}//ns
#pragma once

#include "gpu/vuk/States/General/GeneralPipeline.hpp"
#include "gpu/vuk/States/General/GeneralRenderPass.hpp"
#include "gpu/vuk/States/General/Sprites/SpritesUniforms.hpp"
#include "gpu/vuk/States/General/Shadow/ShadowRenderPass.hpp"

#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateGeneral
{
    Pipeline pipelineSprites;
    Pipeline pipelineSpritesShadows;
    Pipeline pipelineShadows;
    FragVertShader shaderSprites;
    FragVertShader shaderSpritesShadows;
    FragVertShader shaderShadows;
    RenderPassShadow renderPassShadow;
    RenderPassGeneral renderPassGeneral;
    UniformsSprites uniformsSprites;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderData&, uint32_t);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateGeneral::Create(Context& context, Commands& commands, res::Resources& resources)
{
    renderPassGeneral.Create(commands.pool, context.swapchain);
    renderPassShadow.Create(commands.pool, context.swapchain);
    uniformsSprites.Create(commands.pool, resources, renderPassShadow);
    shaderSprites.Create("res/Shaders/spv/sprite.vert.spv", "res/Shaders/spv/sprite.frag.spv");
    shaderSpritesShadows.Create("res/Shaders/spv/spriteShadow.vert.spv", "res/Shaders/spv/spriteShadow.frag.spv");
    shaderShadows.Create("res/Shaders/spv/shadows.vert.spv", "res/Shaders/spv/shadows.frag.spv");
    CreateGeneralPipeline(pipelineSprites, uniformsSprites, shaderSprites, renderPassGeneral);
    CreateGeneralPipeline(pipelineSpritesShadows, uniformsSprites, shaderSpritesShadows, renderPassGeneral);
    CreateGeneralPipeline(pipelineShadows, uniformsSprites, shaderShadows, renderPassGeneral);
}

///////////////////////////////////////////////////////////

void StateGeneral::Destroy()
{
    uniformsSprites.Destroy();
    pipelineSprites.Destroy();
    pipelineSpritesShadows.Destroy();
    pipelineShadows.Destroy();
    renderPassGeneral.Destroy();
    renderPassShadow.Destroy();
    shaderSprites.Destroy();
    shaderSpritesShadows.Destroy();
    shaderShadows.Destroy();
}

///////////////////////////////////////////////////////////

void StateGeneral::Update(RenderData& rd, u32 imageIndex)
{
    uniformsSprites.Update(rd.sprites, imageIndex);
}

///////////////////////////////////////////////////////////

void StateGeneral::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPassShadow.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    ///////////////////////////////////////////////////////////
    vkCmdPushConstants      (cmdBuffer, pipelineSprites.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniformsSprites.ctx.SIZE, &uniformsSprites.ctx.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSprites.layout, 0, 
                             1, &uniformsSprites.descriptors.sets[imageIndex], 0, nullptr);
    //sprite shadows
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSpritesShadows.pipeline);
    vkCmdDraw               (cmdBuffer, uniformsSprites.quads[imageIndex].COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
    //shadows
    vkCmdBeginRenderPass    (cmdBuffer, &renderPassGeneral.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineShadows.pipeline);
    vkCmdDraw               (cmdBuffer, 3, 1, 0, 0);
    //sprites
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineSprites.pipeline);
    vkCmdDraw               (cmdBuffer, uniformsSprites.quads[imageIndex].COUNT_MAX * 6, 1, 0, 0);
    ///////////////////////////////////////////////////////////
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

//TODO base pipeline / cache (?)

}//ns
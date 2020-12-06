#pragma once

#include "gpu/vuk/States/UI/UIShader.hpp"
#include "gpu/vuk/States/UI/UIPipeline.hpp"
#include "gpu/vuk/States/UI/UIRenderPass.hpp"
#include "gpu/vuk/States/UI/UIUniforms.hpp"

#include "gpu/RenderDataUI.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateUI
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;
    UIUniforms uniforms;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderDataUI&);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateUI::Create(Context& context, Commands& commands, res::Resources& resources)
{
    uniforms.Create(commands.pool, resources);
    CreateShaderUI(shader);
    CreateRenderPassUI(renderPass, context.swapchain);
    CreatePipelineUI(pipeline, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void StateUI::Destroy()
{
    uniforms.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void StateUI::Update(RenderDataUI& rd)
{
    uniforms.Update(rd);
}

///////////////////////////////////////////////////////////

void StateUI::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, uniforms.pushConstants.size, &uniforms.pushConstants.data);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
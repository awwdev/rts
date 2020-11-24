#pragma once

#include "vuk/States/Default/DefaultShader.hpp"
#include "vuk/States/Default/DefaultPipeline.hpp"
#include "vuk/States/Default/DefaultRenderPass.hpp"
#include "vuk/Renderer/Commands.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct DefaultState
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;

    void Create(Context&);
    void Destroy();
    void Record(Commands&, uint32_t);
};

////////////////////////////////////////////////////////////

void DefaultState::Create(Context& context)
{
    DefaultShader(shader);
    DefaultRenderPass(renderPass, context.swapchain);
    DefaultPipeline(pipeline, shader, renderPass);
}

////////////////////////////////////////////////////////////

void DefaultState::Destroy()
{
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

////////////////////////////////////////////////////////////

void DefaultState::Record(Commands& commands, uint32_t imageIndex)
{
    VkCheck(vkBeginCommandBuffer(commands.buffer, &commands.beginInfo));
    vkCmdBeginRenderPass(commands.buffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commands.buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdDraw(commands.buffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(commands.buffer);
    VkCheck(vkEndCommandBuffer(commands.buffer));
}

///////////////////////////////////////////////////////////

}//ns
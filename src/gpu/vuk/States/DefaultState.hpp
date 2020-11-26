#pragma once

#include "gpu/vuk/States/Default/DefaultShader.hpp"
#include "gpu/vuk/States/Default/DefaultPipeline.hpp"
#include "gpu/vuk/States/Default/DefaultRenderPass.hpp"
#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultState
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;

    void Create(Context&);
    void Destroy();
    void Update(RenderData& renderData);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void DefaultState::Create(Context& context)
{
    DefaultShader(shader);
    DefaultRenderPass(renderPass, context.swapchain);
    DefaultPipeline(pipeline, shader, renderPass);
}

///////////////////////////////////////////////////////////

void DefaultState::Destroy()
{
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void DefaultState::Update(RenderData& renderData)
{
    
}

///////////////////////////////////////////////////////////

void DefaultState::Record(VkCommandBuffer cmdBUffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBUffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBUffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdDraw               (cmdBUffer, 3, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBUffer);
}

///////////////////////////////////////////////////////////

}//ns
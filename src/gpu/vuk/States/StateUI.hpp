#pragma once

#include "gpu/vuk/States/UI/UIPipeline.hpp"
#include "gpu/vuk/States/UI/UIRenderPass.hpp"
#include "gpu/vuk/States/UI/UIUniforms.hpp"

#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateUI
{
    Pipeline pipeline;
    RenderPassUI renderPass;
    FragVertShader shader;
    UniformsUI uniforms;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderData&, u32);
    void Record(VkCommandBuffer, u32);
};

///////////////////////////////////////////////////////////

void StateUI::Create(Context& context, Commands& commands, res::Resources& resources)
{
    uniforms.Create(commands.pool, resources);
    renderPass.Create(context.swapchain);
    shader.Create("res/Shaders/spv/ui.vert.spv", "res/Shaders/spv/ui.frag.spv");
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

void StateUI::Update(RenderData& rd, u32 swapIdx)
{
    uniforms.Update(rd.ui, swapIdx);
}

///////////////////////////////////////////////////////////

void StateUI::Record(VkCommandBuffer cmdBuffer, u32 swapIdx)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[swapIdx], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             1, &uniforms.descriptors.sets[swapIdx], 0, nullptr);
    vkCmdDraw               (cmdBuffer, uniforms.quadData[swapIdx].COUNT_MAX * 6, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
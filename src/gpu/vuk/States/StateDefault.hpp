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
    RenderPass renderPass;
    Shader shader;
    DefaultUniforms uniforms;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderData_Default&);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateDefault::Create(Context& context, Commands& commands, res::Resources& resources)
{
    uniforms.Create(commands.pool, resources);
    CreateShaderDefault(shader);
    CreateRenderPassDefault(commands.pool, renderPass, context.swapchain);
    CreatePipelineDefault(pipeline, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void StateDefault::Destroy()
{
    uniforms.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void StateDefault::Update(RenderData_Default& rd)
{
    uniforms.Update(rd);
}

///////////////////////////////////////////////////////////

void StateDefault::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    uniforms.metaData.data.windowWidth  = app::glo::windowWidth;
    uniforms.metaData.data.windowHeight = app::glo::windowHeight;

    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdDraw               (cmdBuffer, uniforms.quadData.COUNT_MAX * 6, 1, 0, 0); //draw max since one time recording
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
#pragma once

#include "gpu/vuk/States/Default/DefaultShader.hpp"
#include "gpu/vuk/States/Default/DefaultPipeline.hpp"
#include "gpu/vuk/States/Default/DefaultRenderPass.hpp"
#include "gpu/vuk/States/Default/DefaultVertices.hpp"
#include "gpu/vuk/States/Default/DefaultUniforms.hpp"

#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultState
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;
    DefaultUniforms uniforms;
    DefaultVertices vertices;

    void Create(Context&);
    void Destroy();
    void Update(RenderData& renderData);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void DefaultState::Create(Context& context)
{
    uniforms.Create();
    vertices.Create();
    CreateDefaultShader(shader);
    CreateDefaultRenderPass(renderPass, context.swapchain);
    CreateDefaultPipeline(pipeline, vertices, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void DefaultState::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void DefaultState::Update(RenderData& renderData)
{
    uniforms.Update(renderData);
    vertices.Update(renderData);
}

///////////////////////////////////////////////////////////

void DefaultState::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, uniforms.pushConstants.size, &uniforms.pushConstants.data);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdBindIndexBuffer    (cmdBuffer, vertices.ibo.activeBuffer->buffer, 0, VK_INDEX_TYPE_UINT32);
    //vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 1, nullptr, 0, nullptr);
    vkCmdDrawIndexed        (cmdBuffer, vertices.ibo.count, 1, 0, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
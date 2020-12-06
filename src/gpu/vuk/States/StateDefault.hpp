#pragma once

#include "gpu/vuk/States/Default/DefaultShader.hpp"
#include "gpu/vuk/States/Default/DefaultPipeline.hpp"
#include "gpu/vuk/States/Default/DefaultRenderPass.hpp"
#include "gpu/vuk/States/Default/DefaultVertices.hpp"
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
    DefaultVertices vertices;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Update(RenderDataDefault& renderData);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StateDefault::Create(Context& context, Commands& commands, res::Resources& resources)
{
    uniforms.Create(commands.pool, resources);
    vertices.Create(commands.pool);
    CreateShaderDefault(shader);
    CreateRenderPassDefault(commands.pool, renderPass, context.swapchain);
    CreatePipelineDefault(pipeline, vertices, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void StateDefault::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void StateDefault::Update(RenderDataDefault& rd)
{
    uniforms.Update(rd);
    vertices.Update(rd);
}

///////////////////////////////////////////////////////////

void StateDefault::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, uniforms.pushConstants.size, &uniforms.pushConstants.data);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdBindIndexBuffer    (cmdBuffer, vertices.ibo.activeBuffer->buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdDrawIndexed        (cmdBuffer, vertices.ibo.COUNT_MAX, 1, 0, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
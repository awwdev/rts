#pragma once

#include "gpu/vuk/States/Post/PostShader.hpp"
#include "gpu/vuk/States/Post/PostPipeline.hpp"
#include "gpu/vuk/States/Post/PostRenderPass.hpp"
#include "gpu/vuk/States/Post/PostVertices.hpp"
#include "gpu/vuk/States/Post/PostUniforms.hpp"

#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/vuk/States/State_Default.hpp"
#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct State_Post
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;
    PostUniforms uniforms;
    PostVertices vertices;

    void Create(Context&, Commands&, res::Resources&, State_Default&);
    void Destroy();
    void Update(RenderData& renderData);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void State_Post::Create(Context& context, Commands& commands, res::Resources& resources, State_Default& defaultState)
{
    uniforms.Create(commands.pool, resources, defaultState.renderPass.offscreen);
    vertices.Create(commands.pool);
    CreatePostShader(shader);
    CreatePostRenderPass(renderPass, context.swapchain);
    CreatePostPipeline(pipeline, vertices, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void State_Post::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void State_Post::Update(RenderData& renderData)
{
    uniforms.Update(renderData);
    vertices.Update(renderData);
}

///////////////////////////////////////////////////////////

void State_Post::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    //vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, uniforms.pushConstants.size, &uniforms.pushConstants.data);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdDraw               (cmdBuffer, vertices.vbo.count, 1, 0, 0);
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
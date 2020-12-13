#pragma once

#include "gpu/vuk/States/Post/PostShader.hpp"
#include "gpu/vuk/States/Post/PostPipeline.hpp"
#include "gpu/vuk/States/Post/PostRenderPass.hpp"
#include "gpu/vuk/States/Post/PostVertices.hpp"
#include "gpu/vuk/States/Post/PostUniforms.hpp"

#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/vuk/States/StateDefault.hpp"
#include "gpu/RenderDataPost.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StatePost
{
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;
    PostUniforms uniforms;
    PostVertices vertices;

    void Create(Context&, Commands&, res::Resources&, StateDefault&);
    void Destroy();
    void Update(RenderDataPost&);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StatePost::Create(Context& context, Commands& commands, res::Resources& resources, StateDefault& defaultState)
{
    uniforms.Create(commands.pool, resources, defaultState.renderPass.offscreen);
    vertices.Create(commands.pool);
    CreateShaderPost(shader);
    CreateRenderPassPost(renderPass, context.swapchain);
    CreatePipelinePost(pipeline, vertices, uniforms, shader, renderPass);
}

///////////////////////////////////////////////////////////

void StatePost::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    pipeline.Destroy();
    renderPass.Destroy();
    shader.Destroy();
}

///////////////////////////////////////////////////////////

void StatePost::Update(RenderDataPost& rd)
{
    uniforms.Update(rd);
    vertices.Update(rd);
}

///////////////////////////////////////////////////////////

void StatePost::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    //vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, uniforms.pushConstants.size, &uniforms.pushConstants.data);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             uniforms.descriptors.sets.count, uniforms.descriptors.sets.data, 0, nullptr);
    vkCmdDraw               (cmdBuffer, vertices.vbo.COUNT_MAX, 1, 0, 0); //draw max since one time recording
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns
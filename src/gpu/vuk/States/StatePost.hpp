#pragma once

#include "gpu/vuk/States/Post/PostPipeline.hpp"
#include "gpu/vuk/States/Post/PostRenderPass.hpp"
#include "gpu/vuk/States/Post/PostVertices.hpp"
#include "gpu/vuk/States/Post/PostUniforms.hpp"
#include "gpu/vuk/States/Post/Wire/WirePipeline.hpp"
#include "gpu/vuk/States/Post/Wire/WireUniforms.hpp"
#include "gpu/vuk/States/Post/Wire/WireVertices.hpp"

#include "gpu/vuk/Commands/Commands.hpp"
#include "gpu/vuk/States/StateGeneral.hpp"
#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StatePost
{
    Pipeline pipeline;
    FragVertShader shader;
    RenderPassPost renderPass;
    UniformsPost uniforms;
    VerticesPost vertices;

    Pipeline pipelineWire;
    FragVertShader shaderWire;
    UniformsWire uniformsWire;
    VerticesWire verticesWire;

    void Create(Context&, Commands&, res::Resources&, StateGeneral&);
    void Destroy();
    void Update(RenderData&, uint32_t);
    void Record(VkCommandBuffer, uint32_t);
};

///////////////////////////////////////////////////////////

void StatePost::Create(Context& context, Commands& commands, res::Resources& resources, StateGeneral& stateSprites)
{
    uniforms.Create(commands.pool, resources, stateSprites.renderPassGeneral.offscreen);
    vertices.Create(commands.pool);
    uniformsWire.Create(commands.pool);
    verticesWire.Create(commands.pool);
    renderPass.Create(context.swapchain);
    shader.Create("res/Shaders/spv/post.vert.spv", "res/Shaders/spv/post.frag.spv");
    shaderWire.Create("res/Shaders/spv/wire.vert.spv", "res/Shaders/spv/wire.frag.spv");
    CreatePipelinePost(pipeline, vertices, uniforms, shader, renderPass);
    CreatePipelineWire(pipelineWire, shaderWire, verticesWire, uniforms, renderPass);
}

///////////////////////////////////////////////////////////

void StatePost::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    uniformsWire.Destroy();
    verticesWire.Destroy();
    pipeline.Destroy();
    pipelineWire.Destroy();
    renderPass.Destroy();
    shader.Destroy();
    shaderWire.Destroy();
}

///////////////////////////////////////////////////////////

void StatePost::Update(RenderData& rd, u32 imageIndex)
{
    uniforms.Update(rd.post);
    vertices.Update(rd.post);
    uniformsWire.Update(rd.wire, imageIndex);
    verticesWire.Update(rd.wire, imageIndex);
}

///////////////////////////////////////////////////////////

void StatePost::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    vkCmdBeginRenderPass    (cmdBuffer, &renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    ///////////////////////////////////////////////////////////
    //fullscreen triangle and blurred quads
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdBindDescriptorSets (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 
                             1, &uniforms.descriptors.sets[imageIndex], 0, nullptr);
    vkCmdDraw               (cmdBuffer, vertices.vbo.COUNT_MAX, 1, 0, 0);
    //wire
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineWire.pipeline);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &verticesWire.vbo[imageIndex].activeBuffer->buffer, &verticesWire.offsets);
    vkCmdDraw               (cmdBuffer, verticesWire.vbo[imageIndex].COUNT_MAX, 1, 0, 0);
    ///////////////////////////////////////////////////////////
    vkCmdEndRenderPass      (cmdBuffer);
}

///////////////////////////////////////////////////////////

//TODO use another baked vbo for the fullscreen triangle and seperate draw call?

}//ns
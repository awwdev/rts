#pragma once

#include "gpu/vuk/States/Wire/WirePipeline.hpp"
#include "gpu/vuk/States/Wire/WireVertices.hpp"
#include "gpu/vuk/States/Wire/WireUniforms.hpp"
#include "gpu/vuk/Renderer/Commands.hpp"
#include "gpu/RenderDataWire.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct StateWire
{
    Pipeline pipeline;
    Shader shader;
    VerticesWire vertices;
    UniformsWire uniforms;

    void Create(Context&, Commands&, RenderPass&); //!
    void Update(RenderDataWire&);
    void Record(VkCommandBuffer, uint32_t);
    void Destroy();
};

///////////////////////////////////////////////////////////

void StateWire::Create(Context& context, Commands& commands, RenderPass& renderPassSprites) //!
{
    shader.Create("res/Shaders/spv/wire.vert.spv", "res/Shaders/spv/wire.frag.spv");
    vertices.Create(commands.pool);
    uniforms.Create(commands.pool);
    CreatePipelineWire(pipeline, shader, vertices, uniforms, renderPassSprites);
}

///////////////////////////////////////////////////////////

void StateWire::Destroy()
{
    uniforms.Destroy();
    vertices.Destroy();
    shader.Destroy();
    pipeline.Destroy();
}

///////////////////////////////////////////////////////////

void StateWire::Update(RenderDataWire& rd)
{
    uniforms.Update(rd);
    vertices.Update(rd);
}

///////////////////////////////////////////////////////////

void StateWire::Record(VkCommandBuffer cmdBuffer, uint32_t imageIndex)
{
    //!using render pass from sprites
    vkCmdPushConstants      (cmdBuffer, pipeline.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, 
                             uniforms.metaData.SIZE, &uniforms.metaData.data);
    vkCmdBindPipeline       (cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
    vkCmdBindVertexBuffers  (cmdBuffer, 0, 1, &vertices.vbo.activeBuffer->buffer, &vertices.offsets);
    vkCmdDraw               (cmdBuffer, vertices.vbo.COUNT_MAX, 1, 0, 0);
}

///////////////////////////////////////////////////////////

}//ns
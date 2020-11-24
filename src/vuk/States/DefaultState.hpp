#pragma once

#include "vuk/States/DefaultShader.hpp"
#include "vuk/States/DefaultPipeline.hpp"
#include "vuk/States/DefaultRenderPass.hpp"

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

}//ns
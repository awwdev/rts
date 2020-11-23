#pragma once

#include "vuk/Context/Swapchain.hpp"
#include "vuk/Wrappers/Buffer.hpp"
#include "vuk/Wrappers/Pipeline.hpp"
#include "vuk/Wrappers/RenderPass.hpp"
#include "vuk/Wrappers/Shader.hpp"

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct DefaultState
{
    Buffer buffer;
    Pipeline pipeline;
    RenderPass renderPass;
    Shader shader;

    void Create(Context&);
    void Destroy();
};

////////////////////////////////////////////////////////////

void DefaultState::Create(Context& context)
{
    shader.Create("res/Shaders/default.vert.spv", "res/Shaders/default.frag.spv");
    renderPass.Create(context.swapchain);
    pipeline.Create(shader, renderPass);
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
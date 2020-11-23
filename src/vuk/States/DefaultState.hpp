#pragma once

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

    void Create();
    void Destroy();
};

////////////////////////////////////////////////////////////

void DefaultState::Create()
{
    shader.Create("res/Shaders/default.vert", "res/Shaders/default.frag");
    renderPass.Create();
    pipeline.Create();
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
#pragma once

#include "vuk/Objects/Buffer.hpp"
#include "vuk/Objects/Pipeline.hpp"
#include "vuk/Objects/RenderPass.hpp"
#include "vuk/Objects/Shader.hpp"

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
    shader.Create();
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
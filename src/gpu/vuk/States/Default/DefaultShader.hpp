#pragma once

#include "gpu/vuk/Wrappers/Shader.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreateShaderDefault(Shader& shader)
{
    shader.Create("res/Shaders/spv/default.vert.spv", "res/Shaders/spv/default.frag.spv");
}

///////////////////////////////////////////////////////////

inline void CreateShaderDefaultShadow(Shader& shader)
{
    shader.Create("res/Shaders/spv/defaultShadow.vert.spv", "res/Shaders/spv/defaultShadow.frag.spv");
}

///////////////////////////////////////////////////////////

inline void CreateShaderDefaultShadowOff(Shader& shader)
{
    shader.Create("res/Shaders/spv/defaultShadowOff.vert.spv", "res/Shaders/spv/defaultShadowOff.frag.spv");
}

///////////////////////////////////////////////////////////

//TODO rename to sprite shader

}//ns
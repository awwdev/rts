#pragma once

#include "vuk/Wrappers/Shader.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline void DefaultShader(Shader& shader)
{
    shader.Create("res/Shaders/default.vert.spv", "res/Shaders/default.frag.spv");
}

///////////////////////////////////////////////////////////

}//ns
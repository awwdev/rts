#pragma once

#include "gpu/vuk/Wrappers/Shader.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePostShader(Shader& shader)
{
    shader.Create("res/Shaders/spv/post.vert.spv", "res/Shaders/spv/post.frag.spv");
}

///////////////////////////////////////////////////////////

}//ns
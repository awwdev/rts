#pragma once

#include "gpu/vuk/Wrappers/Shader.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreateShaderSprites(Shader& shader)
{
    shader.Create("res/Shaders/spv/sprite.vert.spv", "res/Shaders/spv/sprite.frag.spv");
}

///////////////////////////////////////////////////////////

inline void CreateShaderSpritesShadow(Shader& shader)
{
    shader.Create("res/Shaders/spv/spriteShadow.vert.spv", "res/Shaders/spv/spriteShadow.frag.spv");
}

///////////////////////////////////////////////////////////

inline void CreateShaderShadows(Shader& shader)
{
    shader.Create("res/Shaders/spv/shadows.vert.spv", "res/Shaders/spv/shadows.frag.spv");
}

///////////////////////////////////////////////////////////

}//ns
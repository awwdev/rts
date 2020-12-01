#version 450
#extension GL_ARB_separate_shader_objects : enable

///////////////////////////////////////////////////////////

layout(location = 0) in vec4 inCol;
layout(location = 1) in vec2 inTex;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;

///////////////////////////////////////////////////////////

layout(binding = 0) uniform sampler2DArray textures;

///////////////////////////////////////////////////////////

void main() 
{
    const int LAYER = 0;
    vec3 uv = vec3(inTex.x, inTex.y, LAYER);
    vec4 col = texture(textures, uv);
    outCol = col;
}
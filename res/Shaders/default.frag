#version 450
#extension GL_ARB_separate_shader_objects : enable

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outColor;

///////////////////////////////////////////////////////////

layout(location = 0) in vec4 inColors;
layout(binding = 0) uniform sampler2DArray textures;

///////////////////////////////////////////////////////////

void main() 
{
    vec3 uv  = vec3(0, 0, 0);
    vec4 col = texture(textures, uv);
    outColor = col;
}
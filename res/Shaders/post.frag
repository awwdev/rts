#version 450
#extension GL_ARB_separate_shader_objects : enable

///////////////////////////////////////////////////////////

layout(location = 0) in vec2 inTex;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;

///////////////////////////////////////////////////////////

//layout(binding = 0) uniform sampler2D offscreen;

///////////////////////////////////////////////////////////

void main() 
{
    //vec4 col = texture(offscreen, inTex);
    outCol = vec4(1, 0, 0, 1);
}
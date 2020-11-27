#version 450

///////////////////////////////////////////////////////////

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTex;
layout (location = 2) in vec4 inCol;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outColor;

///////////////////////////////////////////////////////////

void main() 
{
    gl_Position = vec4(inPos, 0, 1);
    outColor    = inCol;
}
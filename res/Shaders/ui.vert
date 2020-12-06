#version 450

///////////////////////////////////////////////////////////

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec4 inCol;
layout(location = 2) in uint inTexId;

///////////////////////////////////////////////////////////

layout(push_constant) uniform PushConstants
{
    uint windowWidth;
    uint windowHeight;
} 
meta;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;

///////////////////////////////////////////////////////////   

void main() 
{
    float x = inPos.x / meta.windowWidth  * 2 - 1;
    float y = inPos.y / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);
    
    outCol = inCol;
}
#version 450

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
    vec2 inPos = vec2(0,0);
    vec4 inCol = vec4(1, 1, 1, 1);

    float x = inPos.x / meta.windowWidth  * 2 - 1;
    float y = inPos.y / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);
    
    outCol = inCol;
}
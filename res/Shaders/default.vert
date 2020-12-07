#version 450

///////////////////////////////////////////////////////////

layout(push_constant) uniform PushConstants
{
    uint windowWidth;
    uint windowHeight;
} 
meta;

///////////////////////////////////////////////////////////

struct Uniform
{
    int x;
    int y;
    int w;
    int h;
    
    float r;
    float g;
    float b;
    float a;

    uint texId;
};

///////////////////////////////////////////////////////////  

layout(std430, binding = 1) buffer readonly SBO
{
    Uniform array [];
}
sbo;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;
layout(location = 1) out vec2 outTex;
layout(location = 2) out flat uint outTexId;

///////////////////////////////////////////////////////////

const vec2 quad [6] =
{
    vec2(0, 0),
    vec2(0, 1),
    vec2(1, 1),
    vec2(0, 0),
    vec2(1, 1),
    vec2(1, 0),
};

///////////////////////////////////////////////////////////   

void main() 
{
    //index
    Uniform uni = sbo.array[gl_VertexIndex / 6];
    vec2 q = quad[gl_VertexIndex % 6];

    //position
    float x_px = uni.x + q.x * uni.w;
    float y_px = uni.y + q.y * uni.h;
    float x_dc = x_px / meta.windowWidth  * 2 - 1;
    float y_dc = y_px / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x_dc, y_dc, 0, 1);

    //other
    outCol = vec4(uni.r, uni.g, uni.b, uni.a);
    outTex = q;
    outTexId = uni.texId;
}
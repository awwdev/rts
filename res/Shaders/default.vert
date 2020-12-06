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
    float x;
    float y;
    float w;
    float h;
    
    float r;
    float g;
    float b;
    float a;

    uint texId;
};

///////////////////////////////////////////////////////////  

layout(std430, binding = 1) buffer readonly UBO
{
    Uniform array [];
}
ubo;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;
layout(location = 1) out vec2 outTex;
layout(location = 2) out flat uint outTexId;

///////////////////////////////////////////////////////////

const vec2 TEXTURE_COORD [6] =
{
    vec2(0, 0),
    vec2(0, 1),
    vec2(1, 1),

    vec2(0, 0),
    vec2(1, 1),
    vec2(1, 0),
};

///////////////////////////////////////////////////////////   

#define X 0
#define Y 0
#define S 64
const vec2 quad [6] =
{
    vec2(X, Y),
    vec2(X, Y + S),
    vec2(X + S, Y + S),

    vec2(X, Y),
    vec2(X + S, Y + S),
    vec2(X + S, Y),
};

///////////////////////////////////////////////////////////   

void main() 
{
    Uniform uni = ubo.array[gl_VertexIndex / 6];

    //TODO size
    vec2 inPos = vec2(uni.x, uni.y) + quad[gl_VertexIndex % 6];
    float x = inPos.x / meta.windowWidth  * 2 - 1;
    float y = inPos.y / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);

    outCol = vec4(uni.r, uni.g, uni.b, uni.a);
    outTex = TEXTURE_COORD[gl_VertexIndex % 6];
    outTexId = uni.texId;
}
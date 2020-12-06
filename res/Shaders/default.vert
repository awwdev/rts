

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
    vec2  pos;
    vec2  size;
    vec4  col;
    ivec4 texId;
};

///////////////////////////////////////////////////////////  

layout(binding = 1) uniform UBO
{
    Uniform array [1000];
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

const vec2 TEXTURE_COORD2 [4] =
{
    vec2(0, 1),
    vec2(1, 1),
    vec2(0, 0),
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

const vec2 quad2 [4] =
{
    vec2(X, Y + S),
    vec2(X + S, Y + S),
    vec2(X, Y),
    vec2(X + S, Y),
};

///////////////////////////////////////////////////////////   

void main() 
{
    uint quadIdx = gl_VertexIndex / 4;
    //uint quadIdx = gl_VertexIndex / 6;
    Uniform uni = ubo.array[quadIdx];

    vec2 inPos = uni.pos + quad2[gl_VertexIndex % 4];
    //vec2 inPos = uni.pos + quad[gl_VertexIndex % 6];

    vec4 inCol = { 1, 1, 1, 1 };
    uint inTexId = 0;

    float x = inPos.x / meta.windowWidth  * 2 - 1;
    float y = inPos.y / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);

    outCol = uni.col;

    outTex = TEXTURE_COORD2[gl_VertexIndex % 4];
    //outTex = TEXTURE_COORD[gl_VertexIndex % 6];

    outTexId = uni.texId.x;
}



/*
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
layout(location = 1) out vec2 outTex;
layout(location = 2) out flat uint outTexId;

///////////////////////////////////////////////////////////

const vec2 TEXTURE_COORD [4] =
{
    vec2(0, 0),
    vec2(1, 0),
    vec2(1, 1),
    vec2(0, 1),
};

///////////////////////////////////////////////////////////   

void main() 
{
    float x = inPos.x / meta.windowWidth  * 2 - 1;
    float y = inPos.y / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);

    outCol = inCol;
    outTex = TEXTURE_COORD[gl_VertexIndex % 4];
    outTexId = inTexId;
}
*/
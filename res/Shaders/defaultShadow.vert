//////////////////////////////////////////////////////////

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

    float xo;
    float yo;

    uint texId;
    float rot;
};

///////////////////////////////////////////////////////////  

layout(std430, binding = 0) buffer readonly SBO
{
    Uniform array [];
}
sbo;

///////////////////////////////////////////////////////////

layout(binding = 2) uniform UBO
{
    float rotation;
    float strength;
}
ubo;

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

    //rotation
    float c = cos(ubo.rotation);
    float s = sin(ubo.rotation);
    mat2 rotMat = mat2(c, -s, s, c);
    vec2 rotVec = rotMat * vec2(q.x - uni.xo, q.y - 0.25 - uni.yo);  //! hardcoded

    //position
    float x_px = uni.x + rotVec.x * uni.w;
    float y_px = uni.y + 12 + rotVec.y * uni.h; //! hardcoded
    float x_dc = x_px / meta.windowWidth  * 2 - 1;
    float y_dc = y_px / meta.windowHeight * 2 - 1;
    gl_Position = vec4(x_dc, y_dc, 0, 1);

    //other
    outCol = vec4(0, 0, 0, uni.a);
    outTex = q;
    outTexId = uni.texId;
}
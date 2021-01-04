//////////////////////////////////////////////////////////

layout(push_constant) uniform Context
{
    uint windowWidth;
    uint windowHeight;
} 
context;

///////////////////////////////////////////////////////////

struct Quad
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
    bool flipped;
};

///////////////////////////////////////////////////////////  

layout(std430, binding = 0) buffer readonly Quads
{
    Quad array [];
}
quads;

///////////////////////////////////////////////////////////  

layout(binding = 1) uniform Meta
{
    ivec2 camera;
}
meta;

///////////////////////////////////////////////////////////

layout(binding = 2) uniform Sun
{
    float rotation;
    float strength;
}
sun;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;
layout(location = 1) out vec2 outTex;
layout(location = 2) out flat uint outTexId;

///////////////////////////////////////////////////////////

const vec2 verts [6] =
{
    vec2(0, 0),
    vec2(0, 1),
    vec2(1, 1),
    vec2(0, 0),
    vec2(1, 1),
    vec2(1, 0),
};

///////////////////////////////////////////////////////////

const vec2 vertsFlipped [6] =
{
    vec2(1, 0),
    vec2(1, 1),
    vec2(0, 1),
    vec2(1, 0),
    vec2(0, 1),
    vec2(0, 0),
};

///////////////////////////////////////////////////////////    

void main() 
{
    //index
    Quad quad = quads.array[gl_VertexIndex / 6];
    vec2 vert = verts[gl_VertexIndex % 6];

    //rotation
    float c = cos(sun.rotation);
    float s = sin(sun.rotation);
    mat2 rotMat = mat2(c, -s, s, c);
    vec2 rotVec = rotMat * vec2(vert.x - quad.xo, vert.y - 0.25 - quad.yo);  //! hardcoded

    //position
    float x_px = vert.x + meta.camera.x + rotVec.x * quad.w;
    float y_px = vert.y + meta.camera.y + 12 + rotVec.y * quad.h; //! hardcoded
    float x_dc = x_px / context.windowWidth  * 2 - 1;
    float y_dc = y_px / context.windowHeight * 2 - 1;
    gl_Position = vec4(x_dc, y_dc, 0, 1);

    //other
    outCol = vec4(0, 0, 0, quad.a);
    if (quad.flipped) 
        outTex = vertsFlipped[gl_VertexIndex % 6];
    else
        outTex = vert;
    outTexId = quad.texId;
}
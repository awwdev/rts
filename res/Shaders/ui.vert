///////////////////////////////////////////////////////////

layout(push_constant) uniform Context
{
    int windowWidth;
    int windowHeight;
} 
context;

///////////////////////////////////////////////////////////

struct Quad
{
    int   x, y, w, h;   
    float r, g, b, a;
    uint  texId;
};

///////////////////////////////////////////////////////////  

layout(std430, binding = 0) buffer readonly Quads
{
    Quad array [];
}
quads;

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

void main() 
{
    //index
    Quad quad = quads.array[gl_VertexIndex / 6];
    vec2 vert = verts[gl_VertexIndex % 6];

    //position
    float x_px = quad.x + vert.x * quad.w;
    float y_px = quad.y + vert.y * quad.h;
    float x_dc = x_px / context.windowWidth  * 2 - 1;
    float y_dc = y_px / context.windowHeight * 2 - 1;
    gl_Position = vec4(x_dc, y_dc, 0, 1);

    //other
    outCol = vec4(quad.r, quad.g, quad.b, quad.a);
    outTex = vert;
    outTexId = quad.texId;
}
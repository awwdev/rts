//////////////////////////////////////////////////////////

layout(push_constant) uniform Context
{
    uint windowWidth;
    uint windowHeight;
} 
context;

//////////////////////////////////////////////////////////

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec4 inCol;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;

///////////////////////////////////////////////////////////   

void main() 
{
    float x_px = inPos.x;
    float y_px = inPos.y; 
    float x_dc = x_px / context.windowWidth  * 2 - 1;
    float y_dc = y_px / context.windowHeight * 2 - 1;
    gl_Position = vec4(x_dc, y_dc, 0, 1);
    outCol = inCol;
}
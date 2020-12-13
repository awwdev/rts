//////////////////////////////////////////////////////////

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTex;
layout(location = 2) in int  inBlur;

///////////////////////////////////////////////////////////

layout(location = 0) out vec2 outTex;
layout(location = 1) out flat int outBlur;

///////////////////////////////////////////////////////////   

void main() 
{
    gl_Position = vec4(inPos.x, inPos.y, 0, 1);
    outTex = inTex;
    outBlur = inBlur;
}
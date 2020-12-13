///////////////////////////////////////////////////////////

layout(location = 0) in vec2 inTex;
layout(location = 1) in flat int inBlur;

///////////////////////////////////////////////////////////

layout(location = 0) out vec4 outCol;

///////////////////////////////////////////////////////////

layout(binding = 0) uniform sampler2D offscreen;

///////////////////////////////////////////////////////////

void main() 
{
    if (inBlur == 0)
    {
        vec4 col = texture(offscreen, inTex);
        outCol = col;
    }
    else
    {
        vec2 SIZE = textureSize(offscreen, 0);
        const float DIRECTIONS = 16.0;
        const float PI2 = 6.28;
        const float DISTANCE_MAX = 12.0;
        const float DISTANCE_OFF = 2;

        vec3 sum = vec3(0);
        for(float dir = 0.0; dir < PI2; dir += PI2/DIRECTIONS)
        {
            for(float dist = DISTANCE_OFF; dist < DISTANCE_MAX; dist += 1.0)
            {
                vec2 off = vec2(sin(dir), cos(dir)) / SIZE * dist;
                sum += texture(offscreen, inTex + off).rgb;
            }	
        }

        outCol = vec4(sum / (DIRECTIONS * (DISTANCE_MAX - DISTANCE_OFF)), 1);
    }
}
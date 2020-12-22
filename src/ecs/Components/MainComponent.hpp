#pragma once

#include "com/Vec.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct Transform
{
    com::Vec2i pos;
    com::Vec2i posPrev;
    com::Vec2i posTarget;
    com::Vec2i delta;
    com::Vec2i size;
    f32 rot;
    i32 xspd;
    i32 yspd;
    i32 spd;
    void SetPosition(com::Vec2i const&);
    void CalculateDelta();
};

///////////////////////////////////////////////////////////

void Transform::SetPosition(com::Vec2i const& pos)
{
    this->pos = pos;
    this->posPrev = pos;
    this->posTarget = pos;
}

///////////////////////////////////////////////////////////

void Transform::CalculateDelta()
{
    using namespace com;
    delta = posTarget - pos;
    auto m = Max(Abs(delta.x), Abs(delta.y));
    if (delta.x != 0) xspd = m / delta.x;
    if (delta.y != 0) yspd = m / delta.y;
}

///////////////////////////////////////////////////////////

struct Sprite
{
    u32 texIdx;
    u32 texIdxEnd = 4;
    f32 time;
    void Animate();
};

///////////////////////////////////////////////////////////

void Sprite::Animate()
{
    time += app::Time::dt;
    if (time >= 0.1f)
    {
        texIdx = (texIdx + 1) % texIdxEnd;
        time -= 0.1f;  
    }   
}

///////////////////////////////////////////////////////////

struct MainComponent
{
    Transform transform;
    Sprite sprite;
};

///////////////////////////////////////////////////////////

}//ns
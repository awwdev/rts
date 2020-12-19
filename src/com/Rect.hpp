#pragma once

#include <iostream>
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>

///////////////////////////////////////////////////////////

TEMPLATE
struct Rect
{
    T x, y, w, h;

    Rect() = default;

    Rect(T pX, T pY, T pW, T pH)
    : x { pX }
    , y { pY }   
    , w { pW }   
    , h { pH }   
    {}

    Rect(Vec2<T> const& pos, Vec2<T> const& size)
    : x { pos.x }
    , y { pos.y }   
    , w { size.x }   
    , h { size.y }   
    {}

    bool IsPointInside(auto x, auto y);
    bool IsPointInside(auto vec);
};

///////////////////////////////////////////////////////////

TEMPLATE
bool Rect<T>::IsPointInside(auto px, auto py)
{
    return 
    px > x && px < x+w &&
    py > y && py < y+h;
}

///////////////////////////////////////////////////////////

TEMPLATE
bool Rect<T>::IsPointInside(auto vec)
{
    return 
    vec.x > x && vec.x < x+w &&
    vec.x > y && vec.y < y+h;
}

///////////////////////////////////////////////////////////

using Rectf = Rect<f32>;
using Recti = Rect<i32>;

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns
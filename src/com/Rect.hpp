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

    Rect(auto pX, auto pY, auto pW, auto pH)
        : x { (T) pX }
        , y { (T) pY }   
        , w { (T) pW }   
        , h { (T) pH }   
    {}

    template<typename T1, typename T2>
    Rect(Vec2<T1> const& pos, Vec2<T2> const& size)
        : x { (T) pos.x }
        , y { (T) pos.y }   
        , w { (T) size.x }   
        , h { (T) size.y }   
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
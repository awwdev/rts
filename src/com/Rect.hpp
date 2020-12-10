#pragma once

#include <iostream>
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts {

///////////////////////////////////////////////////////////

template<typename T>
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
};

///////////////////////////////////////////////////////////

using Rectf = Rect<f32>;
using Recti = Rect<i32>;

///////////////////////////////////////////////////////////

}//ns
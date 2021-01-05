#pragma once

#include <iostream>
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

template<typename T>
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

template<typename T>
bool Rect<T>::IsPointInside(auto px, auto py)
{
    return 
    px > x && px < x+w &&
    py > y && py < y+h;
}

///////////////////////////////////////////////////////////

template<typename T>
bool Rect<T>::IsPointInside(auto vec)
{
    return 
    vec.x > x && vec.x < x+w &&
    vec.y > y && vec.y < y+h;
}

///////////////////////////////////////////////////////////

using Rectf = Rect<f32>;
using Recti = Rect<i32>;

///////////////////////////////////////////////////////////

template<typename T>
struct AbsRect
{
    com::Vec2<T> v1;
    com::Vec2<T> v2;
    bool IsPointInside(com::Vec2<T> const&);
};

///////////////////////////////////////////////////////////

template<typename T>
bool AbsRect<T>::IsPointInside(com::Vec2<T> const& vec)
{
    return 
    vec.x > v1.x && vec.x < v2.x &&
    vec.y > v1.y && vec.y < v2.y;
}

///////////////////////////////////////////////////////////

using AbsRectf = AbsRect<f32>;
using AbsRecti = AbsRect<i32>;

///////////////////////////////////////////////////////////

//TODO negative rect v2 swaps v1 

}//ns
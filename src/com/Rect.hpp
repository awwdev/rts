#pragma once

#include <iostream>
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

template<typename T>
struct Rect
{
    com::Vec2<T> p1;
    com::Vec2<T> p2;
    
    bool IsPointInside(com::Vec2<T> const&);
    auto Width()  const { p2.x - p1.x; }
    auto Height() const { p2.y - p1.y; }

    template<typename R>
    operator Rect<R>() const { return Rect<R> { static_cast<com::Vec2<R>>(p1), static_cast<com::Vec2<R>>(p2) }; }
};

///////////////////////////////////////////////////////////

template<typename T>
bool Rect<T>::IsPointInside(com::Vec2<T> const& vec)
{
    auto l = com::Min(p1.x, p2.x);
    auto r = com::Max(p1.x, p2.x);
    auto t = com::Min(p1.y, p2.y);
    auto b = com::Max(p1.y, p2.y);

    return 
    vec.x > l && vec.x < r &&
    vec.y > t && vec.y < b;
}

///////////////////////////////////////////////////////////

using Rectf = Rect<f32>;
using Recti = Rect<i32>;

///////////////////////////////////////////////////////////

}//ns
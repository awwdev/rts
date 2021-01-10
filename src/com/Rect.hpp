#pragma once

#include <iostream>
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

template<typename T>
struct Rect
{
    com::Vec2<T> pos;
    com::Vec2<T> size;

    auto GetPos2() const { return pos + size; }
    bool IsPointInside(com::Vec2<T> const&);
    template<typename R>
    operator Rect<R>() const { return Rect<R> { (com::Vec2<R>)pos, (com::Vec2<R>)size }; }
};

///////////////////////////////////////////////////////////

template<typename T>
bool Rect<T>::IsPointInside(com::Vec2<T> const& vec)
{
    auto l = com::Min(pos.x, pos.x + size.x);
    auto r = com::Max(pos.x, pos.x + size.x);
    auto t = com::Min(pos.y, pos.y + size.y);
    auto b = com::Max(pos.y, pos.y + size.y);

    return 
    vec.x > l && vec.x < r &&
    vec.y > t && vec.y < b;
}

///////////////////////////////////////////////////////////

using Rectf = Rect<f32>;
using Recti = Rect<i32>;

///////////////////////////////////////////////////////////

}//ns
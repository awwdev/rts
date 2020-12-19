#pragma once

#include <iostream>
#include "com/Types.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

template<typename T>
struct Vec2
{
    T x, y;
};

///////////////////////////////////////////////////////////

template<typename T>
auto operator==(Vec2<T> const& v1, Vec2<T> const& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

///////////////////////////////////////////////////////////

template<typename T>
auto operator-(Vec2<T> const& v1, Vec2<T> const& v2)
{
    return Vec2<T>
    { 
        v1.x - v2.x, 
        v1.y - v2.y,
    };
}

///////////////////////////////////////////////////////////

using Vec2f = Vec2<f32>;
using Vec2i = Vec2<i32>;
using Vec2u = Vec2<u32>;

///////////////////////////////////////////////////////////

template<typename T>
std::ostream& operator<<(std::ostream& os, Vec2<T> const& vec)
{
    os << '(' << vec.x << '|' << vec.y << ')';
    return os;
}

///////////////////////////////////////////////////////////

}//ns
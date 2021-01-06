#pragma once

#include <iostream>
#include "com/Types.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>

///////////////////////////////////////////////////////////

TEMPLATE
struct Vec2
{
    T x, y;
    bool operator==(T const& val) { return x == val && y == val; }

    template<typename V>
    operator Vec2<V>() const { return Vec2<V> { static_cast<V>(x), static_cast<V>(y) }; }
};

///////////////////////////////////////////////////////////

TEMPLATE
auto Magnitude(Vec2<T> const& vec)
{
    return FastSqrt(vec.x*vec.x + vec.y*vec.y);
}

///////////////////////////////////////////////////////////

TEMPLATE
auto operator==(Vec2<T> const& v1, Vec2<T> const& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

///////////////////////////////////////////////////////////

TEMPLATE
auto operator-(Vec2<T> const& v1, Vec2<T> const& v2)
{
    return Vec2<T>
    { 
        v1.x - v2.x, 
        v1.y - v2.y,
    };
}

///////////////////////////////////////////////////////////

template<typename T1, typename T2>
auto operator+(Vec2<T1> const& v1, Vec2<T2> const& v2)
{
    using C = std::common_type_t<T1, T2>;
    return Vec2<C>
    { 
        v1.x + v2.x, 
        v1.y + v2.y,
    };
}

///////////////////////////////////////////////////////////

TEMPLATE
auto operator*(Vec2<T> const& vec, auto scalar)
{
    using C = std::common_type_t<T, decltype(scalar)>;
    return Vec2<C> { vec.x * scalar, vec.y * scalar };
}

///////////////////////////////////////////////////////////

using Vec2f = Vec2<f32>;
using Vec2i = Vec2<i32>;
using Vec2u = Vec2<u32>;

///////////////////////////////////////////////////////////

TEMPLATE
std::ostream& operator<<(std::ostream& os, Vec2<T> const& vec)
{
    os << '(' << vec.x << '|' << vec.y << ')';
    return os;
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns
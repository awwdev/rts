#pragma once

#include <cstring>
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

inline auto Min(auto a, auto b)
{
    using T = std::common_type_t<decltype(a), decltype(b)>;
    return static_cast<T>(a < b ? a : b);
}

///////////////////////////////////////////////////////////

inline auto Max(auto a, auto b)
{
    using T = std::common_type_t<decltype(a), decltype(b)>;
    return static_cast<T>(a > b ? a : b);
}

///////////////////////////////////////////////////////////

inline auto Abs(auto val)
{
    return val >= 0 ? val : -val;
}

///////////////////////////////////////////////////////////

inline auto Sign(auto val)
{
    return val >= 0 ? 1 : -1;
}

///////////////////////////////////////////////////////////

inline auto Clamp(auto val, auto min, auto max)
{
    val = Max(min, val);
    val = Min(max, val);
    return val;
}

///////////////////////////////////////////////////////////

template<typename T, auto N>
inline void Swap(T (&arr)[N], idx_t idx1, idx_t idx2)
{
    com::Assert(idx1 < N, "array access out of bounds");
    com::Assert(idx2 < N, "array access out of bounds");

    auto tmp  = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = tmp;
}

///////////////////////////////////////////////////////////

inline float FastSqrt(float number)
{
    //from quake
    float x2 = number * 0.5f;
    float y  = number;

    u32 i;
    std::memcpy(&i, &y, sizeof(float));
    i = 0x5f3759df - (i >> 1);
    std::memcpy(&y, &i, sizeof(float));

    return number * (y * (1.5f - (x2 * y * y)));
}

///////////////////////////////////////////////////////////

inline auto CountDigits(std::integral auto num)
{
    auto digits = 1;
    while(1)
    {
        num /= 10;
        if (num == 0)
            return digits;
        digits++;
    }  
}

///////////////////////////////////////////////////////////

inline auto Pow(auto base, auto exponent)
{
    decltype(base) res = base;
    for(auto i = 1; i < exponent; ++i)
        res *= base;
    return res;
}

///////////////////////////////////////////////////////////

}//ns
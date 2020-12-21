#pragma once

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

}//ns
#pragma once

#include "com/Types.hpp"

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

}//ns
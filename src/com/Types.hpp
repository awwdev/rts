#pragma once

#include <concepts>
#include <cstdint>

///////////////////////////////////////////////////////////

namespace mini {

///////////////////////////////////////////////////////////

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

using f32 = float;
using f64 = double;

using chars_t = char const * const;

#define PUBLIC public:
#define PRIVATE private:

///////////////////////////////////////////////////////////

}//ns
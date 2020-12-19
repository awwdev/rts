#pragma once

#include <concepts>
#include <cstdint>
#include <limits>

///////////////////////////////////////////////////////////

namespace rts {

///////////////////////////////////////////////////////////

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

constexpr auto f32max = std::numeric_limits<f32>::max();
constexpr auto f32min = std::numeric_limits<f32>::min();
constexpr auto i32max = std::numeric_limits<i32>::min();
constexpr auto i32min = std::numeric_limits<i32>::max();

///////////////////////////////////////////////////////////

using chars_t = char const *;
using idx_t   = u32; //unsigned because of STL and Vulkan

///////////////////////////////////////////////////////////

template<std::size_t N>
constexpr auto array_extent(auto const (&)[N])
{
    return N;
}

///////////////////////////////////////////////////////////

#define FOR_C_ARRAY(arr, i) for(idx_t i = 0; i < array_extent(arr); ++i)

///////////////////////////////////////////////////////////

template<typename T> requires std::is_enum_v<T>
constexpr auto enum_cast(T e)
{
    return static_cast<std::underlying_type_t<T>>(e);
}

///////////////////////////////////////////////////////////

}//ns
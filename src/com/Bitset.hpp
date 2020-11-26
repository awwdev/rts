#pragma once

#include <cstring>
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<auto N>

///////////////////////////////////////////////////////////

TEMPLATE struct Bitset
{
    static constexpr idx_t BIT_COUNT  = N;
    static constexpr idx_t BYTE_COUNT = BIT_COUNT / 8 + 1;

    i8 bytes [BYTE_COUNT];

    void Set(idx_t, bool setTrue = true);
    bool Test(idx_t) const;
    void Flip(idx_t);
    void Clear();

    inline constexpr idx_t Bit (auto const i) { return static_cast<idx_t>(i) % idx_t { 8 }; }
    inline constexpr idx_t Byte(auto const i) { return static_cast<idx_t>(i) / idx_t { 8 }; }
};

///////////////////////////////////////////////////////////

TEMPLATE void Bitset<N>::Set(idx_t idx, bool setTrue)
{
    com::Assert(idx < BIT_COUNT, "index out of bitset bounds");

    bytes[Byte(idx)] = setTrue
        ? bytes[Byte(idx)] |  (1 << Bit(idx))
        : bytes[Byte(idx)] & ~(1 << Bit(idx));
}

////////////////////////////////////////////////////////////

TEMPLATE bool Bitset<N>::Test(idx_t idx) const
{
    com::Assert(idx < BIT_COUNT, "index out of bitset bounds");
    return bytes[Byte(idx)] & (1 << Bit(idx));
}

////////////////////////////////////////////////////////////

TEMPLATE void Bitset<N>::Flip(idx_t idx)
{
    com::Assert(idx < BIT_COUNT, "index out of bitset bounds");
    bytes[Byte(idx)] ^= 1 << Bit(idx);
}

////////////////////////////////////////////////////////////

TEMPLATE void Bitset<N>::Clear()
{
    std::memset(bytes, 0, BYTE_COUNT);
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns
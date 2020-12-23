#pragma once

#include "com/Types.hpp"
#include "com/Utils.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

static auto GetRandomNumber(i32 min, i32 max)
{
    constexpr i32 NUMBERS []  { 5,2,1,9,4,0,3,8,2,0,9,3,1,5,7,4,6,7,3,8 };
    constexpr i32 NUMBERS2 [] { 0,1,1,0,1,0,0,1 };
    static i32 idx;
    static i32 idx2;
    auto advanceFn  = [&](i32 step) { idx = (idx + step) % 20;  };
    auto advanceFn2 = [&](i32 step) { idx2 = (idx2 + step) % 8; };
    auto range = max - min;

    advanceFn(1);
    i32 num = NUMBERS[idx];
    auto digits = CountDigits(range);
    for(auto i = 1; i < digits; ++i)
    {
        advanceFn(i);
        i32 tmp = NUMBERS[idx];
        advanceFn2(1);
        tmp *= Pow(10, i) * NUMBERS2[idx2];
        num += tmp;
    }
    return com::Clamp(num + min, min, max);
}

///////////////////////////////////////////////////////////

//TODO very bad

}//ns
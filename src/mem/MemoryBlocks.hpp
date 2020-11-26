#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::mem {

///////////////////////////////////////////////////////////

struct BlockArray
{
    idx_t size;
    idx_t count;
};

////////////////////////////////////////////////////////////
//!define application memory demand here
///////////////////////////////////////////////////////////

constexpr BlockArray BLOCK_ARRAYS [] 
{
    { .size =       100, .count = 1000 },
    { .size =     1'000, .count = 1000 },
    { .size =    10'000, .count = 5    },
    { .size =   100'000, .count = 5    },
    { .size = 1'000'000, .count = 5    },
};

////////////////////////////////////////////////////////////

constexpr auto ALLOCATION_SIZE = []
{
    idx_t size = 0;
    FOR_C_ARRAY(BLOCK_ARRAYS, i)
        size += BLOCK_ARRAYS[i].size * BLOCK_ARRAYS[i].count;
    return size;
}();

////////////////////////////////////////////////////////////

constexpr auto BLOCK_ARRAY_COUNT = array_extent(BLOCK_ARRAYS);
constexpr auto BLOCK_COUNT_TOTAL = []
{
    idx_t count = 0;
    FOR_C_ARRAY(BLOCK_ARRAYS, i)
        count += BLOCK_ARRAYS[i].count;
    return count;
}();

///////////////////////////////////////////////////////////

}//ns
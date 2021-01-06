#pragma once

#include "com/Types.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace rts::mem {

///////////////////////////////////////////////////////////

struct BlockArrayInfo
{
    const idx_t blockSize;
    const idx_t count = 1;
};

///////////////////////////////////////////////////////////
//!define application memory demand here
///////////////////////////////////////////////////////////

//constexpr auto s = sizeof(gpu::vuk::Renderer);
//constexpr auto s = sizeof(app::GameScene);
//constexpr auto s = sizeof(res::Resources);
//constexpr auto s = sizeof(net::Network);
constexpr auto SIZE_NETWORK    = 2'000;
constexpr auto SIZE_RENDERER   = 6'000;
constexpr auto SIZE_RESOURCES  = 80'000;
constexpr auto SIZE_GAME_SCENE = 100'000'000;

constexpr BlockArrayInfo BLOCK_ARRAY_INFOS [] 
{
    { .blockSize =  1'000, .count = 100 },
    { .blockSize = 20'000, .count = 100 },
    { .blockSize = SIZE_NETWORK },
    { .blockSize = SIZE_RENDERER },
    { .blockSize = SIZE_RESOURCES },
    { .blockSize = SIZE_GAME_SCENE },
};

///////////////////////////////////////////////////////////

constexpr auto ALLOCATION_SIZE = []
{
    idx_t size = 0;
    FOR_C_ARRAY(BLOCK_ARRAY_INFOS, i)
        size += BLOCK_ARRAY_INFOS[i].blockSize * BLOCK_ARRAY_INFOS[i].count;
    return size;
}();

///////////////////////////////////////////////////////////

constexpr auto BLOCK_ARRAY_COUNT = array_extent(BLOCK_ARRAY_INFOS);
constexpr auto BLOCK_COUNT_TOTAL = []
{
    idx_t count = 0;
    FOR_C_ARRAY(BLOCK_ARRAY_INFOS, i)
        count += BLOCK_ARRAY_INFOS[i].count;
    return count;
}();

///////////////////////////////////////////////////////////

template<typename T>
constexpr auto GetFittingBlockArray()
{
    FOR_C_ARRAY(BLOCK_ARRAY_INFOS, i)
    {
        if (BLOCK_ARRAY_INFOS[i].blockSize >= (sizeof(T) + alignof(T)))
            return i;
    }    
    //compile time error if no appropriate block size is found
}

///////////////////////////////////////////////////////////

constexpr auto GetBlockArrayBitIndex(idx_t blockArrayIdx)
{
    idx_t count = 0;
    for(idx_t i = 0; i < blockArrayIdx; ++i)
        count += BLOCK_ARRAY_INFOS[i].count;
    return count;
}

///////////////////////////////////////////////////////////

}//ns
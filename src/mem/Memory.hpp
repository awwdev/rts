#pragma once

#include "mem/MemoryInfo.hpp"
#include "mem/MemoryAlloc.hpp"
#include "mem/MemoryBlockPtr.hpp"

///////////////////////////////////////////////////////////

namespace rts::mem {

///////////////////////////////////////////////////////////

template<typename T>
static auto ClaimBlock(auto... args)
{
    constexpr idx_t blockArrayIdx = GetFittingBlockArray<T>();
    constexpr idx_t blockArrayBitIdx = GetBlockArrayBitIndex(blockArrayIdx);

    auto freeBlock = blocksUsed.FindFirstFreeBit(blockArrayBitIdx);
    com::Assert(freeBlock.hasValue, "no free blocks available");

    //TODO

    //search free bit inside bitset with the offset of blockArrayBitIdx
    //alignment
    return BlockPtr<T>{};
}

////////////////////////////////////////////////////////////

static void FreeBlock()
{

}

///////////////////////////////////////////////////////////

}//ns
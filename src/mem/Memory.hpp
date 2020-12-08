#pragma once

#include "mem/MemoryInfo.hpp"
#include "mem/MemoryAlloc.hpp"
#include "mem/MemoryBlockPtr.hpp"

///////////////////////////////////////////////////////////

namespace rts::mem {

///////////////////////////////////////////////////////////

template<typename T>
auto AlignNext(void* ptr)
{
    constexpr auto a = alignof(T) - 1;
    return (T*) (((std::uintptr_t)ptr + a) & ~a);
}

///////////////////////////////////////////////////////////

template<typename T>
static auto ClaimBlock(auto... args)
{
    constexpr idx_t blockArrayIdx = GetFittingBlockArray<T>();
    constexpr idx_t blockArrayBitIdx = GetBlockArrayBitIndex(blockArrayIdx);
    constexpr idx_t blockSize = BLOCK_ARRAY_INFOS[blockArrayIdx].blockSize;

    auto freeBlockTotalIdx = blocksUsed.FindFirstFreeBit(blockArrayBitIdx);
    com::Assert(freeBlockTotalIdx.hasData, "no free block available");
    blocksUsed.Set(*freeBlockTotalIdx);
    auto freeBlockIdx = *freeBlockTotalIdx - blockArrayBitIdx;

    auto blockArrayPtr = blockArrayPtrs[blockArrayIdx];
    auto blockPtr = blockArrayPtr + (freeBlockIdx * blockSize);
    auto aligned = AlignNext<T>(blockPtr);
    auto objPtr = new(aligned) T { args... };

#if 1
    com::PrintColored(com::ConsoleColor::Cyan
        , "\nClaimBlock" 
        , "\nblockArrayIdx", blockArrayIdx
        , "\nblockArrayBitIdx", blockArrayBitIdx
        , "\nblockSize", blockSize
        , "\nfreeBlockTotalIdx", *freeBlockTotalIdx
        , "\nfreeBlockIdx", freeBlockIdx
        , "\nblockArrayPtr", (void*)blockArrayPtr
        , "\nblockPtr", (void*)blockPtr 
        , "\naligned", (void*)aligned 
        , "\nobjPtr", (void*)objPtr
        , "\n"
    );
#endif

    return BlockPtr{ objPtr, *freeBlockTotalIdx };
}

////////////////////////////////////////////////////////////

static void FreeBlock(idx_t)
{
    com::Print("FreeBlock");
}

///////////////////////////////////////////////////////////

}//ns
#pragma once

#ifdef _WIN32
#include "com/Windows.hpp"
#endif

#ifdef __linux__
#include <sys/mman.h>
#endif

#include "mem/BlockPtr.hpp"
#include "mem/MemoryBlocks.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace mini::mem {

///////////////////////////////////////////////////////////

inline i8* blockArrayPtrs [BLOCK_ARRAY_COUNT];
inline com::Bitset<BLOCK_COUNT_TOTAL> blocksUsed;

////////////////////////////////////////////////////////////

static void GlobalAlloc()
{
    com::PrintColored(com::ConsoleColor::Magenta, "Allocation Size", ALLOCATION_SIZE);

    #ifdef _WIN32
    blockArrayPtrs[0] = (i8*) VirtualAlloc
    (NULL, ALLOCATION_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    #endif

    #ifdef __linux__
    blockArrayPtrs[0] = (i8*) mmap(NULL, ALLOCATION_SIZE, PROT_READ | PROT_WRITE, 0, 0, 0);
    #endif

    for(idx_t i = 1; i < BLOCK_ARRAY_COUNT; ++i)
    {
        blockArrayPtrs[i] = blockArrayPtrs[i-1] + BLOCK_ARRAYS[i-1].size * BLOCK_ARRAYS[i-1].count;
    }
}

////////////////////////////////////////////////////////////

static void GlobalDealloc()
{
    #ifdef _WIN32
    VirtualFree(blockArrayPtrs[0], 0, MEM_RELEASE);
    #endif
    #ifdef __linux__
    munmap(blockArrayPtrs[0], ALLOCATION_SIZE);
    #endif
}

///////////////////////////////////////////////////////////

}//ns
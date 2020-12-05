#pragma once

#ifdef _WIN32
#include "com/Windows.hpp"
#endif

#ifdef __linux__
#include <sys/mman.h>
#endif

#include "mem/MemoryInfo.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace rts::mem {

///////////////////////////////////////////////////////////

inline i8* blockArrayPtrs [BLOCK_ARRAY_COUNT];
inline com::Bitset<BLOCK_COUNT_TOTAL> blocksUsed;

///////////////////////////////////////////////////////////

static void Allocate()
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
        blockArrayPtrs[i] = blockArrayPtrs[i-1] + BLOCK_ARRAY_INFOS[i-1].blockSize * BLOCK_ARRAY_INFOS[i-1].count;
    }
}

///////////////////////////////////////////////////////////

static void Deallocate()
{
    #ifdef _WIN32
    VirtualFree(blockArrayPtrs[0], 0, MEM_RELEASE);
    #endif
    #ifdef __linux__
    munmap(blockArrayPtrs[0], ALLOCATION_SIZE);
    #endif
}

///////////////////////////////////////////////////////////

static void PrintAlloc()
{
    FOR_C_ARRAY(blockArrayPtrs, i)
    {
        auto addr = (std::uintptr_t) blockArrayPtrs[i];
        com::Print("BlockArrayInfo", i, std::hex, addr, std::dec);
    }
}

///////////////////////////////////////////////////////////

}//ns
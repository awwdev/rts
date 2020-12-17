#pragma once

#include <atomic>
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T, auto N>

///////////////////////////////////////////////////////////

TEMPLATE
struct AtomicRingBuffer
{
    inline static constexpr auto RING_BUFFER_MAX = N;
    inline static T data [RING_BUFFER_MAX] {};

    inline static std::atomic<i32> atomicWriteCount;
    inline static std::atomic<i32> atomicReadCount;

    inline static void Write(T const&);
    inline static auto Read();
};

///////////////////////////////////////////////////////////

TEMPLATE
void AtomicRingBuffer<T, N>::Write(T const& event)
{
    auto writeCount = atomicWriteCount.load();
    auto readCount = atomicReadCount.load();

    data[writeCount] = event;
    writeCount = (writeCount + 1) % RING_BUFFER_MAX;
    com::Assert(writeCount + 1 != readCount, "AtomicRingBuffer write count surpasses read count");
    atomicWriteCount.store(writeCount);
}

///////////////////////////////////////////////////////////

TEMPLATE
auto AtomicRingBuffer<T, N>::Read()
{
    auto writeCount = atomicWriteCount.load();
    auto readCount  = atomicReadCount.load();

    if (writeCount == readCount)
        return;

    com::POD_Array<T, RING_BUFFER_MAX> elements;

    auto delta = (writeCount > readCount)
        ? writeCount - readCount
        : writeCount - readCount + RING_BUFFER_MAX;

    for(auto i = 0; i < delta; ++i)
    {
        auto ringIdx = (readCount + i) % RING_BUFFER_MAX;
        auto& element = data[ringIdx];
        elements.Append(element);
    }

    atomicReadCount = (readCount + delta) % RING_BUFFER_MAX;
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns
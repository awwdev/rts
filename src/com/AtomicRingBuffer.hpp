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
    static constexpr auto RING_BUFFER_MAX = N;
    T data [RING_BUFFER_MAX] {};

    std::atomic<i32> atomicWriteCount = 0;
    std::atomic<i32> atomicReadCount = 0;

    void Write(T const&);
    auto Read();
};

///////////////////////////////////////////////////////////

TEMPLATE
void AtomicRingBuffer<T, N>::Write(T const& event)
{
    auto writeCount = atomicWriteCount.load();
    auto readCount = atomicReadCount.load();

    data[writeCount] = event;
    writeCount = (writeCount + 1) % RING_BUFFER_MAX;
    if (writeCount == readCount)
        com::PrintWarning("AtomicRingBuffer write count surpasses read count");
    atomicWriteCount.store(writeCount);
}

///////////////////////////////////////////////////////////

TEMPLATE
auto AtomicRingBuffer<T, N>::Read()
{
    com::POD_Array<T, RING_BUFFER_MAX> buffer;

    auto writeCount = atomicWriteCount.load();
    auto readCount  = atomicReadCount.load();

    if (writeCount == readCount)
        return buffer;

    auto delta = (writeCount > readCount)
        ? writeCount - readCount
        : writeCount - readCount + RING_BUFFER_MAX;

    for(auto i = 0; i < delta; ++i)
    {
        auto ringIdx = (readCount + i) % RING_BUFFER_MAX;
        auto& element = data[ringIdx];
        buffer.Append(element);
    }

    atomicReadCount = (readCount + delta) % RING_BUFFER_MAX;

    return buffer;
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns
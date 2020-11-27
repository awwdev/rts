#pragma once

#include "net/Network.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

constexpr auto MAX_DATAGRAM_SIZE = 65507;

///////////////////////////////////////////////////////////

struct Packet
{
    char data [MAX_DATAGRAM_SIZE];
    i32  size = 0;
    i32  readPos = 0;

    void Write(auto const&...);
    void Read(auto&...);
};

///////////////////////////////////////////////////////////

void Packet::Write(auto const&... pData)
{
    auto writeFn = [&](auto const& pData)
    {
        auto pSize = [&]
        {
            if constexpr(std::is_same_v<const char*, decltype(pData)>)
            return std::strlen(pData) + 1;
            return sizeof(decltype(pData));
        }();

        std::memcpy(data + size, (char*) &pData, pSize);
        size += pSize;
    };

    (writeFn(pData),...);
}

///////////////////////////////////////////////////////////

void Packet::Read(auto&... pData)
{
    auto readFn = [&](auto& pData)
    {
        auto pSize = [&]
        {
            if constexpr(std::is_same_v<const char*, decltype(pData)>)
            return std::strlen(pData);
            return sizeof(decltype(pData));
        }();

        std::memcpy((char*) &pData, data + readPos, pSize);
        readPos += pSize;
    };

    (readFn(pData),...);
}

///////////////////////////////////////////////////////////

}//ns
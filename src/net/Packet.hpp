#pragma once

#include "net/Win32/Win32_Network.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace rts::net {

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

void Packet::Write(auto const&... pDatas)
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

    (writeFn(pDatas),...);
}

///////////////////////////////////////////////////////////

void Packet::Read(auto&... pDatas)
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

    (readFn(pDatas),...);
}

///////////////////////////////////////////////////////////

}//ns
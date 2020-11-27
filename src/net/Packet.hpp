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
    size_t size = 0;

    void Write(auto...);
    void Read();
};

///////////////////////////////////////////////////////////

void Packet::Write(auto... pData)
{
    auto writeFn = [&](auto pData)
    {
        auto pSize = [&]
        {
            if constexpr(std::is_same_v<const char*, decltype(pData)>)
            return std::strlen(pData);
            return sizeof(decltype(pData));
        }();

        std::memcpy(data + size, &pData, pSize);
        size += pSize;
    };

    (writeFn(pData),...);
}

///////////////////////////////////////////////////////////

void Packet::Read()
{

}

///////////////////////////////////////////////////////////

}//ns
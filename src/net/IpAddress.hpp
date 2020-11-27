#pragma once

#include "net/Network.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct IpAddress
{
    chars_t address;
    u16 port;
};

////////////////////////////////////////////////////////////

inline auto CreateIpAddress(IpAddress const& ip)
{
    sockaddr_in sockaddr {};
    sockaddr.sin_family      = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.address);
    sockaddr.sin_port        = htons(ip.port);
    return sockaddr;
}

///////////////////////////////////////////////////////////

}//ns
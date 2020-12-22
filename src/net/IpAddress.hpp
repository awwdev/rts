#pragma once

#include <iostream>
#include "net/Network.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::net {

///////////////////////////////////////////////////////////

struct IpAddress
{
    char str [INET_ADDRSTRLEN];
    u16  port;
};

////////////////////////////////////////////////////////////

inline auto CreateSockAddr(IpAddress const& ip)
{
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ip.port);
    inet_pton(AF_INET, ip.str, &addr.sin_addr);
    return addr;
}

///////////////////////////////////////////////////////////

inline auto CreateIpAddress(sockaddr_in const& addr)
{
    IpAddress ip;
    inet_ntop(AF_INET, &(addr.sin_addr), ip.str, INET_ADDRSTRLEN);
    ip.port = ntohs(addr.sin_port);
    return ip;
}

///////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, IpAddress const& ip)
{
    os << ip.str << ':' << ip.port;
    return os;
}

///////////////////////////////////////////////////////////

}//ns
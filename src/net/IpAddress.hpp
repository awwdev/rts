#pragma once

#include "net/Network.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct IpAddress
{
    char str [INET_ADDRSTRLEN];
    u16  port;
};

////////////////////////////////////////////////////////////

inline auto CreateSockAddr(IpAddress const& ip)
{
    sockaddr_in sockaddr {};
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(ip.port);
    inet_pton(AF_INET, ip.str, &sockaddr.sin_addr);
    return sockaddr;
}

///////////////////////////////////////////////////////////

inline auto CreateIpAddress(sockaddr_in const& sockaddr)
{
    IpAddress ip;
    inet_ntop(AF_INET, &(sockaddr.sin_addr), ip.str, INET_ADDRSTRLEN);
    ip.port = ntohs(sockaddr.sin_port);
    return ip;
}

///////////////////////////////////////////////////////////

}//ns
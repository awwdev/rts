#pragma once

#include "net/UdpSocket.hpp"
#include "com/Type.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

using port_t = u16;
using addr_t = u32;

struct Address
{
    addr_t ip;
    port_t port;

    Address() = default;
    Address(u8,u8,u8,u8);
};

///////////////////////////////////////////////////////////

Address::Address(u8 byte0, u8 byte1, u8 byte2, u8 byte3)
: ip = { htonl }
//m_address(htonl((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3)),

///////////////////////////////////////////////////////////

}//ns
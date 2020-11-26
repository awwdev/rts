#pragma once

#include "net/Win32/Win32_Winsock.hpp"
#include "net/Packet.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct Win32_UdpSocket
{
    using port_t = u16;
    using addr_t = u32;
    static constexpr auto MAX_DATAGRAM_SIZE = 65507;
    bool isBound = false;

    SOCKET sock;

    void Init();
    void Bind(addr_t address = ADDR_ANY, port_t port = 54000);
    void Close();
    void Send(const byte_t* data, i32 size);
    void Receive();
};

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Init()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    u_long blocking = 0;
    com::WinSockAssert(ioctlsocket(sock, FIONBIO, &blocking));
    int broadcast = 0;
    com::WinSockAssert(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast, sizeof(broadcast)));
    Bind();
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Bind(addr_t address, port_t port)
{
    sockaddr_in addr {};
    addr.sin_addr.S_un.S_addr = ADDR_ANY;//htonl(address);
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);

    //inet_pton(AF_INET, "127.0.0.1", &sin_addr);

    com::WinSockAssert(bind(sock, (sockaddr*)&addr, sizeof(addr)));
    isBound = true;
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Close()
{
    if (isBound)
    {
        com::WinSockAssert(closesocket(sock));
        isBound = false;
    }
}        

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Send(const byte_t* data, i32 size)
{
    sockaddr address {};
    com::WinSockAssert(sendto(sock, data, size, 0, &address, sizeof(address)));
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Receive()
{
    sockaddr address {};
    int size = sizeof(address);
    byte_t buffer [MAX_DATAGRAM_SIZE];
    com::WinSockAssert(recvfrom(sock, buffer, MAX_DATAGRAM_SIZE, 0, &address, &size));
}

///////////////////////////////////////////////////////////

}//ns

//ntohs(address.sin_port);
//INADDR_ANY
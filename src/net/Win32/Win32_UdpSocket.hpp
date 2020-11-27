#pragma once

#include "com/Windows.hpp"
#include "net/Packet.hpp"
#include "net/IpAddress.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct Win32_UdpSocket
{
    SOCKET sock;
    bool isBound;

    void Init();
    void Bind(IpAddress const&);
    void Close();

    void Send(IpAddress const&, byte_t* data, i32 size);
    void Receive();
};

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Init()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    WinSockCheck(sock == INVALID_SOCKET);
    u_long nonBlocking = 1;
    WinSockCheck(ioctlsocket(sock, FIONBIO, &nonBlocking));
    int broadcast = 1;
    WinSockCheck(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)));
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Bind(IpAddress const& ip)
{
    auto sockaddr = CreateIpAddress(ip);
    WinSockCheck(bind(sock, (SOCKADDR*) &sockaddr, sizeof(sockaddr)));
    isBound = true;
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Close()
{
    if (isBound)
    {
        WinSockCheck(closesocket(sock));
        isBound = false;
    }
}        

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Send(IpAddress const& ip, byte_t* data, i32 size)
{
    auto sockaddr = CreateIpAddress(ip);
    WinSockCheck(sendto(sock, data, size, 0, (SOCKADDR*) &sockaddr, sizeof(sockaddr)));
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Receive()
{
    /*
    sockaddr address {};
    int size = sizeof(address);
    byte_t buffer [MAX_DATAGRAM_SIZE];
    WinSockCheck(recvfrom(sock, buffer, MAX_DATAGRAM_SIZE, 0, &address, &size));
    */
}

///////////////////////////////////////////////////////////

}//ns
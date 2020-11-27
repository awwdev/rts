#pragma once

#include "com/Windows.hpp"
#include "net/Packet.hpp"
#include "net/IpAddress.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct Win32_UdpSocket
{
    SOCKET sock;
    bool isBound;
    char receiveBuffer [MAX_DATAGRAM_SIZE];

    void Init();
    void Bind(IpAddress const&);
    void Close();

    void Send(IpAddress const&, Packet const&);
    bool Receive();
};

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Init()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    WinSockCheck(sock != INVALID_SOCKET);
    u_long nonBlocking = 1;
    WinSockCheck(ioctlsocket(sock, FIONBIO, &nonBlocking));
    int broadcast = 1;
    WinSockCheck(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)));
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Bind(IpAddress const& ip)
{
    auto sockaddr = CreateSockAddr(ip);
    WinSockCheck(bind(sock, (SOCKADDR*) &sockaddr, sizeof(sockaddr)));
    isBound = true;
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Close()
{
    if (!isBound) return;
    WinSockCheck(closesocket(sock));
    isBound = false;
}        

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Send(IpAddress const& ip, Packet const& packet)
{
    if (packet.size <= 0) return;
    auto sockaddr = CreateSockAddr(ip);
    auto bytesSent = sendto(sock, packet.data, packet.size, 0, (SOCKADDR*) &sockaddr, sizeof(sockaddr));
    WinSockCheck(bytesSent != SOCKET_ERROR);
    com::Print("send", bytesSent);
}

///////////////////////////////////////////////////////////

bool Win32_UdpSocket::Receive()
{
    sockaddr_in sockaddr;
    int sockaddrSize = sizeof(sockaddr);
    auto bytesRecv = recvfrom(sock, receiveBuffer, array_extent(receiveBuffer), 0, (SOCKADDR*) &sockaddr, &sockaddrSize);
    WinSockCheck(bytesRecv != SOCKET_ERROR);
    auto ip = CreateIpAddress(sockaddr);
    com::Print("received", bytesRecv, "from", ip.str, ip.port);
    return bytesRecv > 0;
}

///////////////////////////////////////////////////////////

}//ns
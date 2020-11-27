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

    void Init();
    void Bind(IpAddress const&);
    void Close();
    auto GetAddress() const -> IpAddress;

    void Send(IpAddress const&, Packet const&);
    auto Receive() -> Packet;
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
    auto addr = CreateSockAddr(ip);
    WinSockCheck(bind(sock, (SOCKADDR*) &addr, sizeof(addr)));
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

auto Win32_UdpSocket::GetAddress() const -> IpAddress
{
    sockaddr_in addr;
    i32 addrSize = sizeof(addr);
    WinSockCheck(getsockname(sock, (SOCKADDR*) &addr, &addrSize));
    return CreateIpAddress(addr);
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Send(IpAddress const& ip, Packet const& packet)
{
    if (packet.size <= 0) return;
    auto addr = CreateSockAddr(ip);
    auto bytesSent = sendto(sock, packet.data, packet.size, 0, (SOCKADDR*) &addr, sizeof(addr));
    WinSockCheck(bytesSent != SOCKET_ERROR);
    com::Print("send", bytesSent);
}

///////////////////////////////////////////////////////////

auto Win32_UdpSocket::Receive() -> Packet
{
    Packet packet {};
    sockaddr_in addr;
    int addrSize = sizeof(addr);
    packet.size = recvfrom(sock, packet.data, array_extent(packet.data), 0, (SOCKADDR*) &addr, &addrSize);
    WinSockCheck(packet.size != SOCKET_ERROR);
    auto ip = CreateIpAddress(addr);
    com::Print("received", packet.size, "from", ip.str, ip.port);
    return packet;
}

///////////////////////////////////////////////////////////

}//ns
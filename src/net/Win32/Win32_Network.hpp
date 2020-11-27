#pragma once

#include "com/Windows.hpp"
#include "net/Win32/Win32_UdpSocket.hpp"
#include "net/IpAddress.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct Win32_Network
{
    Win32_UdpSocket socket;

    Win32_Network();
    ~Win32_Network();

    void Connect(IpAddress const&);
    void Disconnect();
};

///////////////////////////////////////////////////////////

Win32_Network::Win32_Network()
{
    WSADATA wsaData;
    WinSockCheck(WSAStartup(MAKEWORD(2, 2), &wsaData));
    com::PrintColored(com::ConsoleColor::Magenta, "Winsock", 
    (i32)LOBYTE(wsaData.wVersion), (i32)HIBYTE(wsaData.wVersion));

    socket.Init();
    Connect({ "127.0.0.1", 27015 });
    Packet packet;
    packet.Write("Hello");
    packet.Write(42);
    socket.Send({ "127.0.0.1", 27015 }, packet);
}

////////////////////////////////////////////////////////////

Win32_Network::~Win32_Network()
{
    Disconnect();
    WinSockCheck(WSACleanup());
}

///////////////////////////////////////////////////////////

void Win32_Network::Connect(IpAddress const& ip)
{
    socket.Bind(ip);
}

///////////////////////////////////////////////////////////

void Win32_Network::Disconnect()
{
    socket.Close();
}

///////////////////////////////////////////////////////////

}//ns
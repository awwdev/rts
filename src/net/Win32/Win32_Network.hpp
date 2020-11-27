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
    Connect(IpAddress{ "127.0.0.1", 27015 });
    auto myAddress = socket.GetAddress();
    com::Print("I am", myAddress.str, myAddress.port);

    Packet packet;
    packet.Write("Hello");
    packet.Write(int(42));
    socket.Send(IpAddress{ "127.0.0.1", 27015 }, packet);
    
    auto packet2 = socket.Receive();
    if (packet2.size > 0)
    {
        char str [6];
        int  num;
        packet2.Read(str);
        packet2.Read(num);
        com::Print("packet content", str, num);
    }
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
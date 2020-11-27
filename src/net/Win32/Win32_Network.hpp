#pragma once

#include "com/Windows.hpp"
#include "net/Win32/Win32_UdpSocket.hpp"
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
    void Connect();
    void Disconnect();
};

///////////////////////////////////////////////////////////

Win32_Network::Win32_Network()
{
    WSADATA wsaData;
    WinCheck(WSAStartup(MAKEWORD(2, 2), &wsaData));
    com::PrintColored(com::ConsoleColor::Magenta, "Winsock", 
    (i32)LOBYTE(wsaData.wVersion), (i32)HIBYTE(wsaData.wVersion));

    socket.Init();
}

////////////////////////////////////////////////////////////

Win32_Network::~Win32_Network()
{
    Disconnect();
    WinCheck(WSACleanup());
}

///////////////////////////////////////////////////////////

void Win32_Network::Connect()
{
    socket.Bind();
}

///////////////////////////////////////////////////////////

void Win32_Network::Disconnect()
{
    socket.Close();
}

///////////////////////////////////////////////////////////

}//ns
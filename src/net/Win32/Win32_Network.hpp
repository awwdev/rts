#pragma once

#include "com/Windows.hpp"
#include "net/Win32/Win32_UdpSocket.hpp"
#include "net/IpAddress.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"
#include "app/CmdArgs.hpp"

///////////////////////////////////////////////////////////

namespace rts::net {

///////////////////////////////////////////////////////////

struct Win32_Network
{
    Win32_UdpSocket socket;

    Win32_Network(app::CmdArgs const&);
    ~Win32_Network();

    void Connect(IpAddress const&);
    void Disconnect();
};

///////////////////////////////////////////////////////////

Win32_Network::Win32_Network(app::CmdArgs const& args)
{
    WSADATA wsaData;
    WinSockCheck(WSAStartup(MAKEWORD(2, 2), &wsaData));
    com::PrintColored(com::ConsoleColor::Magenta, "Winsock", 
    (i32)LOBYTE(wsaData.wVersion), (i32)HIBYTE(wsaData.wVersion));

    u16 localPort = 27015;
    args.GetLocalPort(localPort);
    IpAddress ip { "127.0.0.1", localPort };
    com::PrintColored(com::ConsoleColor::Magenta, ip);

    socket.Init();
    Connect(ip);
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
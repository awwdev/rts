#pragma once

#include "com/Windows.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

static void InitializeWinsock()
{
    WSADATA wsaData;
    com::WinSockAssert(WSAStartup(MAKEWORD(2, 2), &wsaData));
    com::PrintColored(com::ConsoleColor::Magenta, "Winsock", 
    (i32)LOBYTE(wsaData.wVersion), (i32)HIBYTE(wsaData.wVersion));
}

////////////////////////////////////////////////////////////

static void DestroyWinsock()
{
    com::WinSockAssert(WSACleanup());
}

///////////////////////////////////////////////////////////

}//ns
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
    auto version = MAKEWORD(2, 2);
    WSADATA wsaData;
    auto result = WSAStartup(version, &wsaData);
    com::Assert(result == 0, "WSAStartup failed");
    
    com::PrintColored(com::ConsoleColor::Magenta, "Winsock", 
    (i32)LOBYTE(wsaData.wVersion), (i32)HIBYTE(wsaData.wVersion));
}

////////////////////////////////////////////////////////////

static void DestroyWinsock()
{
    WSACleanup();
}

///////////////////////////////////////////////////////////

}//ns
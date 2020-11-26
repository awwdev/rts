#pragma once

///////////////////////////////////////////////////////////

#ifdef _WIN32
#include "net/Win32/Win32_UdpSocket.hpp"
namespace mini::net
{
    using UdpSocket = Win32_UdpSocket;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
#include "wnd/Unix/X11_Window.hpp"
namespace mini::net 
{
    using UdpSocket = void*;
}
#endif
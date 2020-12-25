#pragma once

///////////////////////////////////////////////////////////

#ifdef _WIN32
#include "net/Win32/Win32_Network.hpp"
namespace rts::net
{
    using Network = Win32_Network;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
    //using Network = X11_Network;
#endif
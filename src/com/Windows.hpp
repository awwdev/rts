#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "com/WindowsUndef.hpp"
#include "com/Print.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd
{
    
inline void WinCheck(auto expr, chars_t msg = "")
{
    if (expr == 0) //for handles and winbool
    {
        auto err = GetLastError();
        com::Assert(false, "WinCheck failed", err, msg);
    }
}

}//ns

////////////////////////////////////////////////////////////

namespace rts::net 
{

inline void WinSockCheck(auto pExpr, chars_t msg = "")
{
    bool expr = [&]
    {
        if constexpr (std::is_pointer_v<decltype(pExpr)>)
        return pExpr != 0; //success on handle
        else
        if constexpr (std::is_same_v<bool, decltype(pExpr)>)
        return pExpr; // bool 
        else 
        return pExpr == 0; //success on int

    }();

    if (!expr)
    {
        auto err = WSAGetLastError();
        com::Assert(false, "WinSockCheck failed", err, msg);
    }
}

}//ns
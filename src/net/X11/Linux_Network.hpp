#pragma once

#include <sys/types.h>
#include <sys/socket.h>

#include "com/Linux.hpp"
#include "net/X11/Linux_UdpSocket.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"
#include "app/CmdArgs.hpp"

///////////////////////////////////////////////////////////

namespace rts::net {

///////////////////////////////////////////////////////////

//TODO probably not needed since we dont need windows alike initialization

struct Linux_Network
{
    Linux_UdpSocket socket;
    Linux_Network(app::CmdArgs const&);
};

Linux_Network::Linux_Network(app::CmdArgs const&)
{
    socket.Init();
    socket.Bind();
}

///////////////////////////////////////////////////////////

}//ns
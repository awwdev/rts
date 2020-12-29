#pragma once

#include <sys/types.h>
#include <sys/socket.h>

#include "com/Unix.hpp"
#include "net/Unix/UnixUdpSocket.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"
#include "app/CmdArgs.hpp"

///////////////////////////////////////////////////////////

namespace rts::net {

///////////////////////////////////////////////////////////

//TODO probably not needed since we dont need windows alike initialization

struct UnixNetwork
{
    Linux_UdpSocket socket;
    UnixNetwork(app::CmdArgs const&);
};

UnixNetwork::UnixNetwork(app::CmdArgs const&)
{
    socket.Init();
    socket.Bind();
}

///////////////////////////////////////////////////////////

}//ns
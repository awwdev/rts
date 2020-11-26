#pragma once

#include "net/UdpSocket.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

//no diff between client and server but unified networking layer

///////////////////////////////////////////////////////////

struct Networking
{
    UdpSocket socket;

    Networking();
    ~Networking();
};

///////////////////////////////////////////////////////////

Networking::Networking()
{
    InitializeWinsock();
    socket.Init();
}

///////////////////////////////////////////////////////////

Networking::~Networking()
{
    socket.Close();
    DestroyWinsock();
}

///////////////////////////////////////////////////////////

}//ns
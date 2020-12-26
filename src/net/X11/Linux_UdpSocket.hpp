#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "com/Linux.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"
#include "app/CmdArgs.hpp"

///////////////////////////////////////////////////////////

namespace rts::net {

///////////////////////////////////////////////////////////

struct Linux_UdpSocket
{
    int sock;

    void Init();
    void Bind();
};

void Linux_UdpSocket::Init()
{
    sock = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP);
    com::Assert(sock != -1, "socket bind failed");

    int broadcast=1;
    int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, 
    &broadcast, sizeof(broadcast));
    com::Assert(ret != -1, "setsockopt failed");
}

void Linux_UdpSocket::Bind()
{
    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    addr.sin_port = htons(50'000);
    auto res = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
    com::Assert(res != -1, "bind failed");
}

///////////////////////////////////////////////////////////

//TODO custom assert

}//ns
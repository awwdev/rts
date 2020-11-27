#pragma once

#include "com/Windows.hpp"
#include "net/Packet.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace mini::net {

///////////////////////////////////////////////////////////

struct Win32_UdpSocket
{
    SOCKET sock;

    void Init();
    void Bind();
    void Close();

    void Send(const byte_t* data, i32 size);
    void Receive();
};

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Init()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    WinCheck(sock == INVALID_SOCKET);
    u_long nonBlocking = 1; //true
    WinCheck(ioctlsocket(sock, FIONBIO, &nonBlocking));
    int broadcast = 1;
    WinCheck(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)));
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Bind()
{
    //inet_addr("127.0.0.1");
    /*
    sockaddr_in addr {};
    addr.sin_addr.S_un.S_addr = ADDR_ANY;//htonl(address);
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);

    //inet_pton(AF_INET, "127.0.0.1", &sin_addr);

    WinCheck(bind(sock, (sockaddr*)&addr, sizeof(addr)));
    isBound = true;
    */
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Close()
{
    /*
    if (isBound)
    {
        WinCheck(closesocket(sock));
        isBound = false;
    }
    */
}        

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Send(const byte_t* data, i32 size)
{
    /*
    sockaddr_in addr {};
    addr.sin_addr.S_un.S_addr = htonl(address);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    WinCheck(sendto(sock, data, size, 0, &address, sizeof(address)));
    */
}

///////////////////////////////////////////////////////////

void Win32_UdpSocket::Receive()
{
    /*
    sockaddr address {};
    int size = sizeof(address);
    byte_t buffer [MAX_DATAGRAM_SIZE];
    WinCheck(recvfrom(sock, buffer, MAX_DATAGRAM_SIZE, 0, &address, &size));
    */
}

///////////////////////////////////////////////////////////

}//ns
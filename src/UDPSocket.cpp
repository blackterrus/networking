#include "UDPSocket.h"

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 5035

UDPSocket::UDPSocket() 
{
    fd_ = 0;
    addr_ = {0};
}

UDPSocket::~UDPSocket()
{

}

int UDPSocket::createSocket()
{
   fd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if(fd_ < 0)
   {
       printf("UDPSocket::createSocket(): Error opening socket. Returning -1\n");
   }
   else
   {
       printf("UDPSocket::createSocket(): Successfully created socket with fd %d\n", fd_);
       addr_.sin_family = AF_INET;
       addr_.sin_port = htons(PORT);
       addr_.sin_addr.s_addr = inet_addr("127.0.0.1");
   }
   return fd_;
}

void UDPSocket::closeSocket()
{
    close(fd_);
}

int UDPSocket::bindSocket()
{
    int bindSock = 0;
    bindSock = bind(fd_, (const struct sockaddr *)&addr_, sizeof(addr_));
    if(bindSock < 0)
    {
        printf("UDPSocket::bindSocket(): Error binding to socket. Returning -1\n");
    }
    else
    {
        printf("UDPSocket::bindSocket(): Successfully bound to new socket.\n");
    }
    return bindSock;
}

int UDPSocket::recvFrom()
{
    ssize_t bytesRcvd = 0;
    char buffer[maxLine_] = {0};
    socklen_t len = (socklen_t)sizeof(addr_);
    bytesRcvd = recvfrom(fd_, (char*)buffer, maxLine_, 0, (struct sockaddr*)&addr_, &len);
    if(bytesRcvd > 0)
    {
        printf("UDPSocket::recvFrom(): Received %d bytes from socket\n", (int)bytesRcvd);
    }   
    else if(bytesRcvd == 0)
    {
        printf("UDPSocket::recvFrom(): No bytes received from socket\n");
    }
    else
    {
        printf("UDPSocket::recvFrom(): Error attempting to receive from socket. ERROR: %d\n", (int)bytesRcvd);
    }
    return (int)bytesRcvd;
}

int UDPSocket::sendTo()
{
    ssize_t bytesSent = 0;
    std::string msg = "This is a test UDP message";
    bytesSent = sendto(fd_, msg.c_str(), msg.size(), 0, (const struct sockaddr *) &addr_, sizeof(addr_));
    if(bytesSent > 0)
    {
        printf("UDPSocket::sendTo(): Successfully sent %d bytes to socket\n", (int)bytesSent);
    }
    else if(bytesSent == 0)
    {
        printf("UDPSocket::sendTo(): No bytes sent to socket\n");
    }
    else
    {
        printf("UDPSocket::sendTo(): ERROR sending bytes to socket. ERROR: %d\n", (int)bytesSent);
    }
    return (int)bytesSent;
}
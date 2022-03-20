#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <netinet/in.h>

class SocketClient
{
public:
    SocketClient();
    virtual ~SocketClient();

    virtual void createSocket() = 0;
    virtual void bindSocket() = 0;
    virtual void recvFrom() = 0;
    virtual void sendTo() = 0;

    int getFileDescriptor(){ return fd_; };
    sockaddr_in getServInfo(){ return servaddr_; };

protected:
    int fd_; // file descriptor
    struct sockaddr_in servaddr_; 
    const unsigned short maxline_ = 1024;
};

#endif

#ifndef SOCKETINTERFACE_H_
#define SOCKETINTERFACE_H_

#include <netinet/in.h>

class SocketInterface
{
public:
    SocketInterface(){};
    virtual ~SocketInterface(){};
    virtual int createSocket() = 0;
    virtual void closeSocket() = 0;
    virtual int bindSocket() = 0;
    virtual int recvFrom() = 0;
    virtual int sendTo() = 0;

    int getFileDescriptor(){ return fd_; };
    sockaddr_in getServInfo(){ return addr_; };

    const unsigned short maxLine_ = 1024;

protected:
    int fd_; // file descriptor
    struct sockaddr_in addr_; 
};

#endif

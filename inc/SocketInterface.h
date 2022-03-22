#ifndef SOCKETINTERFACE_H_
#define SOCKETINTERFACE_H_

#include <netinet/in.h>

class SocketInterface
{
public:
    SocketInterface();
    virtual ~SocketInterface();

    virtual void createSocket() = 0;
    virtual void bindSocket() = 0;
    virtual void recvFrom() = 0;
    virtual void sendTo() = 0;

    int getFileDescriptor(){ return fd_; };
    sockaddr_in getServInfo(){ return servaddr_; };

    static const unsigned short maxLine_ = 1024;

protected:
    int fd_; // file descriptor
    struct sockaddr_in servaddr_; 
};

#endif

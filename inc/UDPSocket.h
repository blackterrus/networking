#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include "SocketInterface.h"

class UDPSocket : public SocketInterface
{
public:
    UDPSocket() override;
    virtual ~UDPSocket();
    int createSocket() override;
    void closeSocket() override;
    int bindSocket() override;
    int recvFrom() override;
    int sendTo() override;
};

#endif
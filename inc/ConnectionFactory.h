#ifndef CONNECTIONFACTORY_H_
#define CONNECTIONFACTORY_H_

#include "UDPSocket.h"

#include "ConnectionTypes.h"

class SocketInterface;
class UDPSocket;

class ConnectionFactory
{
public:
    ~ConnectionFactory();
    static ConnectionFactory* getInstance();
    SocketInterface* newConnection(ConnectionType type);
    unsigned int getNumConnections();

private:
    ConnectionFactory();

private:
    static ConnectionFactory* instance_;
    unsigned int numConnections_;
};

#endif
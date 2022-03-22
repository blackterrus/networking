#ifndef CONNECTIONFACTORY_H_
#define CONNECTIONFACTORY_H_

#include "SocketInterface.h"

#include "ConnectionTypes.h"

class SocketInterface;

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
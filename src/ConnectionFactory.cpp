#include "ConnectionFactory.h"

#include <iostream>

ConnectionFactory* ConnectionFactory::instance_ = 0;

// PRIVATE
ConnectionFactory::ConnectionFactory()
: numConnections_(0)
{

}

ConnectionFactory::~ConnectionFactory()
{

}

ConnectionFactory* ConnectionFactory::getInstance()
{
    if(instance_ == 0)
    {
        instance_ = new ConnectionFactory();
        if(instance_ == 0)
        {
            instance_ = new ConnectionFactory();
        }
    }
    return instance_;
}

SocketInterface* ConnectionFactory::newConnection(ConnectionType type)
{
    SocketInterface* ifptr = 0;

    short connType = (short)type;
    switch(connType)
    {
        case 0:
        {
            printf("ConnectionFactory::newConnection(): Creating new UDPSocket\n");
            ifptr = static_cast<SocketInterface*>(new UDPSocket());
            if(ifptr == 0)
            {
                printf("ConnectionFactory::newConnection(): Error creating new UDPSocket\n");
            }
            numConnections_++;
            break;
        }
        case 1:
        {
            std::cout << "Returning TCP" << std::endl;
            numConnections_++;
            break;
        }
        default:
        {
            std::cout << "Invalid type" << std::endl;
            break;
        }
    }

    return ifptr;
}

unsigned int ConnectionFactory::getNumConnections()
{
    return numConnections_;
}
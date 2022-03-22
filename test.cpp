#include "ConnectionFactory.h"

#include <iostream>

int main()
{
    ConnectionFactory* factory = ConnectionFactory::getInstance();
    if(factory != 0)
    {
        factory->newConnection(ConnectionType::UDP_CONN);
        std::cout << "numConnections_: " << factory->getNumConnections() << std::endl;
        delete factory;
    }
    else
    {
        std::cout << "Unable to get instance of ConnectionFactory..." << std::endl;
    }
    return 0;
}
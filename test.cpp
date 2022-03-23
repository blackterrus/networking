#include "ConnectionFactory.h"

#include <iostream>

int main()
{
    ConnectionFactory* factory = ConnectionFactory::getInstance();
    if(factory != 0)
    {
        SocketInterface* ptr = 0;
        factory->newConnection(ConnectionType::UDP_CONN);
        std::cout << "numConnections_: " << factory->getNumConnections() << std::endl;
        if(ptr != 0)
        {
            // Test receiver side
            printf("\n***** TESTING UDP RECEIVER SIDE *****\n");
            int retVal = 0;
            retVal = ptr->createSocket();
            if(retVal < 0)
            {
                printf("main(): Error creating socket\n");
                return -1;
            }
            else
            {
                retVal = ptr->bindSocket();
                if(retVal < 0)
                {
                    printf("main(): Error binding to socket\n");
                    return -1;
                }
                else
                {
                    ptr->recvFrom();
                    ptr->closeSocket();
                }
            }

            // Test receiver side
            printf("\n***** TESTING UDP SENDER SIDE *****\n");
            retVal = ptr->createSocket();
            if(retVal < 0)
            {
                printf("main(): Error creating socket\n");
                return -1;
            }
            else
            {
                ptr->sendTo();
                ptr->closeSocket();
            }
        }
        else
        {
            printf("main(): Unable to get new object\n");
        }
        
        delete factory;
        delete ptr;

        factory = NULL;
        ptr = NULL;
    }
    else
    {
        std::cout << "Unable to get instance of ConnectionFactory..." << std::endl;
    }
    return 0;
}
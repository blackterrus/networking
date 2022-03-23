#include "ConnectionFactory.h"

#include <iostream>

#include <unistd.h>

int main()
{
    ConnectionFactory* factory = ConnectionFactory::getInstance();
    if(factory != 0)
    {
        SocketInterface* ptr = 0;
        ptr = factory->newConnection(ConnectionType::UDP_CONN);
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
                    ptr->closeSocket();
                    return -1;
                }
                else
                {
                    while(true)
                    {
                        ptr->recvFrom();
                    }
                }
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
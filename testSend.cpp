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
            printf("\n***** TESTING UDP SENDER SIDE *****\n");
            int retVal = 0;
            retVal = ptr->createSocket();
            if(retVal < 0)
            {
                printf("main(): Error creating socket\n");
                return -1;
            }
            else
            {
                unsigned short ctr = 0;
                while(true)
                {
                    ptr->sendTo();
                    ctr++;
                    sleep(1);
                }
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
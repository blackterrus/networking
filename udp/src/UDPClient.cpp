#include "UDPClient.h"

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <winsock2.h>
#include <errno.h>
#include <windows.h>
   
#define PORT    5035
#define MAXLINE 1024
   
// Driver code
int main() 
{
    SOCKET fd;
    char buffer[MAXLINE];
    std::string hello = "THIS IS A UDP DATAGRAM";
    struct sockaddr_in servaddr = {0};
    WSADATA wsa = {0};

    //Initialise winsock
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,1), &wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
   
    // Creating socket file descriptor
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(fd < 0) 
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    
    //Bind
    if(bind(fd, (sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
        closesocket(fd);
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

    int bytesSent = 0;
    unsigned short sent = 0;  
    while(sent < 25)
    {
        bytesSent = sendto(fd, hello.c_str(), hello.size(), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        
        if(bytesSent > 0)
        {
            printf("UDPClient hello message sent.\n");
        }
        else if(bytesSent == 0)
        {
            printf("UDPClient failed to send bytes.\n");
        }
        else
        {
            printf("UDPClient experienced error sending bytes. ERROR CODE: %d -- Exiting...\n", WSAGetLastError());
            break;
        }
        Sleep(1000);
        sent++;
    }
   
    closesocket(fd);
    return 0;
}

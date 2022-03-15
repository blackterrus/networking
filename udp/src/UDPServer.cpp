#include "UDPServer.h"

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <winsock2.h>

#define PORT    5035 // Macro defining which port to open
#define MAXLINE 1024 // Macro defining buffer size

int main(int argc, char* argv[])
{
    SOCKET fd; // File descriptor for socket to be opened
    char buffer[MAXLINE]; // Buffer of 1024 1-bytes elements
    struct sockaddr_in clientaddr = {0}; // Structure to hold data of incoming message's source
    WSADATA wsa = {0};

    //Initialise winsock
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,1), &wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Create file descriptor
    if(fd < 0) // Error in creating socket, so bail out
    {
        perror("Socket creation failed"); // Log error
        exit(EXIT_FAILURE); // Exit with failure
    }

    // Fill in server info
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(PORT);
    clientaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    
    // Bind the socket with the server address
    if(bind(fd, (const struct sockaddr *)&clientaddr, sizeof(clientaddr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        closesocket(fd);
        exit(EXIT_FAILURE);
    }

    int len = (int)sizeof(clientaddr);
    int bytesRcvd = 0; // Number of bytes in message received

    while(true) // Loop until user kills app
    {
        // Receive message from socket
        bytesRcvd = recvfrom(fd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&clientaddr, &len);
        if(bytesRcvd > 0)
        {
            // Got a message from the socket. Print and NULL terminate last character of received bytes
            buffer[bytesRcvd] = '\0';
            printf("UDPServer received %d bytes... Message: %s\n", bytesRcvd, buffer);
        }
        else if(bytesRcvd == 0)
        {
            // No message received. Do nothing and try again.
            printf("UDPServer received 0 bytes. Trying again...\n");
        }
        else
        {
            // Error encountered. Break and quit.
            printf("UDPServer encountered error in receiving from socket. RETURN CODE: %d -- Exiting...\n", bytesRcvd);
            break;
        }
    }

    return 0;
}

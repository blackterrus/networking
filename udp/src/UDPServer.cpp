#include "UDPServer.h"

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <winsock2.h>

#define PORT 5035 // Macro defining which port to open
#define MAXLINE 1024 // Macro defining buffer size

int main(int argc, char* argv[])
{
    SOCKET fd; // File descriptor for socket to be opened
    char buffer[MAXLINE]; // Buffer of 1024 1-bytes elements

    struct sockaddr_in servaddr; // Structure to hold server address data
    struct sockaddr_in clientaddr; // Structure to hold data of incoming message's source

    memset(&servaddr, 0, sizeof(servaddr)); // Zero-initialize data in servaddr
    memset(&clientaddr, 0, sizeof(clientaddr)); // Zero-initialize data in clientaddr
    memset(&buffer, 0, MAXLINE); // Zero-initialize buffer

    fd = socket(AF_INET, SOCK_DGRAM, 0); // Create file descriptor
    if(fd < 0) // Error in creating socket, so bail out
    {
        perror("Socket creation failed"); // Log error
        exit(EXIT_FAILURE); // Exit with failure
    }

    // Fill in server info
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    int len = (int)sizeof(clientaddr);
    int bytesRcvd = 0; // Number of bytes in message received

    unsigned short ii = 0; // Counter for message listening loop
    while(true) // Loop until user kills app
    {
        // Receive message from socket
        bytesRcvd = recvfrom(fd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&clientaddr, &len);
        if(bytesRcvd > 0)
        {
            // Got a message from the socket. Print and NULL terminate last character of received bytes
            printf("UDPServer received %d bytes... Message: %s\n", bytesRcvd, buffer);
            buffer[bytesRcvd] = '\0';
        }
        else if(bytesRcvd == 0)
        {
            // No message received. Do nothing and try again.
            printf("UDPServer received 0 bytes. Trying again...\n");
        }
        else
        {
            // Error encountered. Break and quit.
            printf("UDPServer encountered error in receiving from socket. Exiting...\n");
            break;
        }
    }

    return 0;
}

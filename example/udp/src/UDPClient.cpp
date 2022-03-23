#include "UDPClient.h"

#include <string>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
#define PORT    5035
#define MAXLINE 1024
   
// Driver code
int main() 
{
    int fd;
    char buffer[MAXLINE];
    std::string hello = "THIS IS A UDP DATAGRAM";
    struct sockaddr_in servaddr = {0};
   
    printf("Opening socket\n");
    // Creating socket file descriptor
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(fd < 0) 
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket opened\n");
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
            printf("UDPClient experienced error sending bytes. Exiting...\n");
            break;
        }
        sleep(1);
        sent++;
    }
   
    close(fd);
    return 0;
}

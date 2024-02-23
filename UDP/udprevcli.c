// Client side
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter string: ");
    fgets(buffer, 1024, stdin);
    buffer[strlen(buffer) - 1] = '\0'; // remove newline character

    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // send message to server

    unsigned int len = sizeof(serverAddr);
    int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, &len); // receive message from server
    buffer[n] = '\0';

    printf("Reversed string: %s\n", buffer);

    close(sockfd);
    return 0;
}
 

// Server side
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void reverse_string(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket with server address
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    unsigned int len = sizeof(clientAddr);
    int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &len); // receive message from client
    buffer[n] = '\0';

    reverse_string(buffer);

    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, len); // send message to client

    close(sockfd);
    return 0;
}


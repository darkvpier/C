#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // char *ip = "127.0.0.1";
    int port = 55555;

    char buffer[1024];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-] Socket Failed");
        exit(1);
    }
    printf("[+] Socket Created\n");

    struct sockaddr_in sock_addr;
    socklen_t addr_size;

    memset(&sock_addr, '\0', sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    int status = connect(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (status < 0)
    {
        perror("[-] Connection Failed");
        exit(1);
    }
    printf("[+] Connected to the server\n");

    bzero(buffer, 1024);
    strcpy(buffer, "TEST COMPLETED, CLIENT:)");
    printf("MESSAGE SENT: %s\n", buffer);
    send(sockfd, buffer, strlen(buffer), 0);

    bzero(buffer, 1024);
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("MESSAGE RECIEVED: %s\n", buffer);

    close(sockfd);
    printf("[+] Disconnected From the server");
    return 0;
}
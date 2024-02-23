#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE];
    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) < 0)
        {
            perror("[-]Send error");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main()
{
    int port = 55555;
    char buffer[SIZE];
    FILE *fp;
    char *filename = "test1.txt";

    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-] SOCKET FAILED");
        exit(1);
    }
    printf("[+] SOCKET CREATED\n");

    struct sockaddr_in sock_addr;
    socklen_t addr_size;

    memset(&sock_addr, '\0', sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    int s = connect(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (s < 0)
    {
        perror("[-] CONNECT FAILED");
        exit(1);
    }
    printf("[+] CONNECTED\n");

    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        perror("[-] FILE NOT FOUND");
        exit(1);
    }

    send_file(fp, sockfd);
    printf("[+] Send file success\n");
    close(sockfd);
    printf("[+] Connection Closed");
    return 0;
}
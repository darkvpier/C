#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 1024

void write_file(int sockfd)
{
    char *filename = "file2.txt";
    FILE *fp;
    int n;
    char buffer[SIZE];
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("[-] Error Creating File");
        exit(1);
    }
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
            return;
        }

        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
}

int main()
{
    // char *ip="127.0.0.1";
    int port = 55555;
    char buffer[SIZE];

    int server_sock, client_sock;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] SOCKET FAILED\n");
        exit(1);
    }
    printf("[+] SOCKET CREATED\n");
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int s = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (s < 0)
    {
        perror("[-] BIND FAILED\n");
        exit(1);
    }
    printf("[+] BIND CREATED\n");

    int t = listen(server_sock, 5);
    if (t < 0)
    {
        perror("[-] LISTENING FAILED\n");
        exit(1);
    }
    printf("[+] LISTENING.....\n");

    memset(&client_addr, '\0', sizeof(client_addr));
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("[+] Client Accepted\n");

    write_file(client_sock);
    printf("[+] File Received\n");
    close(client_sock);
    close(server_sock);
    return 0;
}



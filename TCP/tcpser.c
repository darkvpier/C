#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    // char *ip = "127.0.0.1";
    int port = 55555;
    char buffer[1024];

    int server_sock, client_sock;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-] Socket Failed");
        exit(1);
    }
    printf("[+] Socket Created\n");

    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int status = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status < 0)
    {
        perror("[-] Bind Failed");
        exit(1);
    }
    printf("[+] Bind to the Port Number: %d\n", port);

    listen(server_sock, 5);
    printf("Listening....\n");
    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("[+] Client Connected\n");

        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("MESSAGE RECIEVED: %s\n", buffer);

        bzero(buffer, 1024);
        strcpy(buffer, "TEST COMPLETED, SERVER:)");
        printf("MESSAGE SENT: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
        printf("[+] Client disconnected\n");
    }
    close(server_sock);
    printf("[+] Server disconnected\n");
    return 0;
}
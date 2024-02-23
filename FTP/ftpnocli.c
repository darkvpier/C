// Client
#include <stdio.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <arpa/inet.h> 

#define PORT 8080

int main() {
    int socket_desc;
    struct sockaddr_in server;
    char message[200], server_reply[200];

    // Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to remote server
    connect(socket_desc, (struct sockaddr *)&server , sizeof(server));
    
    printf("Enter filename : ");
    scanf("%s",message);

    // Send data
    send(socket_desc, message, strlen(message), 0);

    // Receive a reply from the server
    if(recv(socket_desc, server_reply, sizeof(server_reply), 0) < 0){
        puts("recv failed");
    }

    puts("Server reply :");
    puts(server_reply);

    return 0;
}


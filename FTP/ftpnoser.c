#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>  

#define PORT 8080

int main() {
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    char *message;
    int read_size, write_size;
    FILE *file;
    int ch_count = 0;
    char client_message[200]={0}, server_message[200]={0};
  
    // Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
   
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
   
    // Bind
    bind(socket_desc, (struct sockaddr *)&server , sizeof(server));

    // Listen
    listen(socket_desc, 3);
 
    // Accept client request
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

    // Receive filename from client
    read_size = recv(new_socket, client_message, sizeof(client_message), 0);
  
    // Open file and count characters
    file = fopen(client_message, "r");
    if (file == NULL){
        sprintf(server_message, "Could not open file");
    } else{
        int ch;
        while((ch=fgetc(file)) != EOF) {
            ch_count++;
        }

        sprintf(server_message, "Number of characters: %d", ch_count);
        fclose(file);
    }

    // Send the message back to client
    send(new_socket, server_message, strlen(server_message), 0);

    close(new_socket);
    return 0;
}


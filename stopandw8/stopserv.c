#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main() {
	int server_sock,
	client_sock,
	k = 5,
	m = 1,
	p,
	status;
	int port = 55555;
	char buffer[1024];
	struct sockaddr_in server_addr,
	client_addr;
	socklen_t addrsize;
	addrsize=sizeof(client_addr);
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock < 0) {
		printf("\nsocket creation failed");
		exit(1);
	}
	printf("\nsocket created");
	server_addr.sin_port = htons(port);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Bind() on server_socket has failed\n");
		exit(1);
	}
	int listen1 = listen(server_sock, 5);
	if(listen1 < 0) {
		perror("listen function failed");
		exit(1);
	}
	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrsize);
	if(client_sock == -1) {
		printf("\nerror in socket\n");
		exit(1);
	}

	while(k != 0) {
		if(recv(client_sock, buffer, 1024, 0) < -1) {
			perror("Receive Failed");
			exit(1);
		}
		if (strncmp(buffer, "frame", 5) == 0) {
			printf("\n\nReceived-%d Successfully", m);
		}
		if (m%2==0) {
			strcpy(buffer, "ack");
		}
		else
		{
			strcpy(buffer, "kca");
			printf("\nack lost");
			for(int p = 1; p <= 3; p++) {
				printf("\nwaiting for %d second", p);
			}
			printf("\nRetransmitting ack");
			strcpy(buffer, "ack");
			sleep(3);
		}
		if(send(client_sock, buffer, 1024, 0) == -1) {
			perror("Send Failed");
			exit(1);
		}
		printf("\nSending ack %d", m);
		k--;
		m++;
	}
	close(client_sock);
	return 0;
}
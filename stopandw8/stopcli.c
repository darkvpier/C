#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() {
	int sockfd,
	y = 0,
	x,
	z,
	k = 5,
	m = 1,
	p;
	int port = 55555;
	char buffer[1024];
	struct sockaddr_in server_addr;
	socklen_t addrsize;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	y = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(y < 0) {
		perror("Connect Failed");
		exit(1);
	}
	while(k != 0) {
		if(m <= 5) {
			printf("\n\nSent %d", m);
		}
		if(m%2 == 0) {
			strcpy(buffer, "frame");
		}
		else
		{
			strcpy(buffer, "error");
			printf("\npacket lost");
			for(p = 1; p <= 3; p++) {
				printf("\nwaiting for %d seconds", p);
			}
			printf("\nRetransmitting Packet %d", m);
			strcpy(buffer, "frame");
			sleep(3);
		}
		if(send(sockfd, buffer, 1024, 0) < 0) {
			perror("Error Sending");
			exit(1);
		}
		printf("\nSending Packet %d", m);
		if(recv(sockfd, buffer, 1024, 0) < 0) {
			perror("Received Failed");
			exit(1);
		}
		if(strncmp(buffer, "ack", 3) == 0) {
			printf("\nack Received for %d", m);
		}
		else
		{
			printf("\nack not Received");
		}
		k--;
		m++;
	}
	close(sockfd);
	return 0;
}
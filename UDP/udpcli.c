#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("USAGE: %s <port>", argv[0]);
		exit(1);
	}
	int port = atoi(argv[1]);
	char *ip = "127.0.0.1";

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("[-] SOCKET FAILED");
		exit;
	}

	struct sockaddr_in sock_addr;
	socklen_t addr_size;

	memset(&sock_addr, '\0', sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	sock_addr.sin_addr.s_addr = inet_addr(ip);

	char buffer[1024];
	bzero(buffer, 1024);
	strcpy(buffer, "TEST COMPLETED");
	sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
	printf("[+] Data Send: %s\n", buffer);

	bzero(buffer, 1024);
	addr_size = sizeof(sock_addr);
	recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&sock_addr, &addr_size);
	printf("[+]Data recv: %s\n", buffer);

	return 0;
}
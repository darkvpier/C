#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#define BUF_SIZE 256
int main()
{
	int port = 55555;
	struct sockaddr_in server;

	char str[50] = "hi";
	char mail_f[50], mail_to[50], msg[1024], c;
	int t = 0;
	socklen_t l = sizeof(server);
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		printf("Error in socket();");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	printf("Sending hi to server");
	sleep(1);
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("Error in sendto");
	if (recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l) < 0)
		printf("error in recv");
	printf("\n greetings msg is %s", str);
	if (strncmp(str, "220", 3))
		printf("\n Cannot established \n code 220 expected");
	printf("\nSending HELO");
	strcpy(str, "HELO 127.0.0.1");
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in send to");
	sleep(1);
	printf("Receiving from server");
	if ((recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l)) < 0)
		printf("error in recv");
	if (strncmp(str, "250", 3))
		printf("\n Ok not received from server");
	printf("\n Server has send %s", str);
	printf("\n Enter FROM address\n");
	scanf("%s", mail_f);
	strcpy(str, "MAIL FROM");
	strcat(str, mail_f);
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in send to");
	sleep(1);
	if ((recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l)) < 0)
		printf("error in recv");
	if (strncmp(str, "250", 3))
		printf("Ok not received from server");
	printf("%s", str);
	printf("\n Enter TO address\n");
	scanf("%s", mail_to);
	strcpy(str, "RCPT TO");
	strcat(str, mail_to);
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in send to");
	sleep(1);
	if ((recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l)) < 0)
		printf("error in recv");
	if (strncmp(str, "250", 3))
		printf("\n Ok not received from server");
	printf("\n%s", str);
	printf("\nSending data to server");
	strcpy(str, "DATA");
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in sendto");
	sleep(1);
	if ((recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l)) < 0)
		printf("error in recv");
	if (strncmp(str, "354", 3))
		printf("\n Ok not received from server");
	printf("\n%s", str);
	printf("\n Enter mail body");
	while (l)
	{
		c = getchar();
		if (c == '$')
		{
			msg[t] = '\0';
			break;
		}
		msg[t++] = c;
	}
	if (sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in sendto");
	sleep(1);
	printf("\nSending QUIT to server");
	strcpy(str, "QUIT");
	if (sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("error in send to");
	if ((recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l)) < 0)
		printf("error in recv");
	if (strncmp(str, "221", 3))
		printf("\nOk not received from server");
	printf("\nServer has send GOODBYE...........Closing conn\n");
	printf("\nBye");
	close(sockfd);
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#define BUF_SIZE 256
int main(int argc, char* argv[])
{
	struct sockaddr_in server,client;
	char str[50], msg[20];
	if(argc!=2)
		printf("Input format not correct\n");
	int sockfd = socket(AF_INET, SOCK_DGRAM,0);
	if(sockfd== -1)
		printf("Error in socket()\n");
	server.sin_family =AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	client.sin_port = htons(atoi(argv[1]));
	if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
		printf("Error in bind()!\n");
	socklen_t client_len = sizeof(client);
	printf("Server waiting...\n");
	sleep(3);
	if(recvfrom(sockfd, str,100,0,(struct sockaddr*)&client,&client_len)<0)
		printf("Error in recfrom()!");
	printf("Got message from client: %s\n", str);
	printf("Sending greeting message to client\n");
	strcpy(str,"220 127.0.0.1" );
	sleep(10);
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	sleep(3);
	if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	if(strncmp(str, "HELO", 4))
		printf("\n 'HELO' expected from client...");
	printf("%s", str);
	printf("\nSending response...");
	strcpy(str, "250 ok");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	sleep(3);
	if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	if(strncmp(str, "MAIL FROM ", 9))
		printf("\nMAIL FROM expected from client...");
	printf("\n%s", str);
	printf("\nSending response...");
	strcpy(str, "250 ok");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	sleep(3);
	if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	if(strncmp(str, "RCPT TO ", 7))
		printf("\nRCPT TO expected from client...");
	printf("\n%s", str);
	printf("\nSending response...");
	strcpy(str, "250 ok");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	sleep(3);
	if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	if(strncmp(str, "DATA", 4))
		printf("DATA expected from client...");
	printf("\n%s", str);
	printf("\nSending response...");
	strcpy(str, "354 Go ahead");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	if((recvfrom(sockfd,msg,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	printf("mail body received");
	printf("\n%s",msg);
	if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&client, &client_len)) < 0)
	printf("Error in recv");
	if(strncmp(str,"QUIT ",4))
		printf("\nQuit expected from client...");
	printf("\nSending quit...\n");
	strcpy(str, "221 ok");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&client, sizeof(client))<0)
		printf("Error in send\n");
	close(sockfd);
	return 0;
}

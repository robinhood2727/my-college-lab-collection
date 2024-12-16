#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#define BUF_SIZE 256
int main(int argc, char* argv[])
{
        struct sockaddr_in server,client;
        char str[50] = "hi";
	char mail_f[50], mail_to[50], msg[20],c;
	int t=0;
	socklen_t l = sizeof(server);
        if(argc!=2)
                printf("Input format not correct\n");
        int sockfd = socket(AF_INET, SOCK_DGRAM,0);
        if(sockfd== -1)
                printf("Error in socket()\n");
        server.sin_family =AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(atoi(argv[1]));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
        client.sin_port = htons(atoi(argv[1]));
	printf("Sending hi to server\n");
	sleep(10);
       	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in send to\n");
        if(recvfrom(sockfd, str,sizeof(str),0,(struct sockaddr*)&server,&l)<0)
                printf("Error in recv");
        printf("\nGreeting message is %s\n", str);
	if(strncmp(str, "220", 3))
		printf("\nConn not established\n Code 220 expected");
        printf("\nSending HELO\n");
        strcpy(str,"HELO 127.0.0.1" );
        if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
        sleep(3);
	printf("Receiving from server\n");
        if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&server, &l)) < 0)
        printf("Error in recv");
        if(strncmp(str, "250", 3))
                printf("\n OK not received from server\n");
	printf("Server has send %s\n", str);
	printf("Enter FROM address\n");
        scanf("%s", mail_f);
	strcpy(str, "MAIL FROM");
	strcat(str, mail_f);
        if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
        sleep(3);
        if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&server, &l)) < 0)
        printf("Error in recv");
        if(strncmp(str, "250", 3))
                printf("\nOK not received from server");
        printf("%s", str);
        printf("\nEnter TO address\n");
	scanf("%s", mail_to);
        strcpy(str, "RCPT TO");
	strcat(str, mail_to);
        if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
        sleep(3);
        if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&server, &l)) < 0)
        	printf("Error in recv");
        if(strncmp(str, "250", 3))
                printf("\nOK not received from server");
        printf("\%s", str);
        printf("\nSending DATA to server\n");
        strcpy(str, "DATA");
        if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
        sleep(3);
        if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&server, &l)) < 0)
        	printf("Error in recv");
        if(strncmp(str, "354", 3))
                printf("\nOK not received from server");
        printf("%s\n", str);
        printf("Enter mail body:\n");
	while(1)
	{
		c = getchar();
		if(c == '$')
		{
			msg[t] = '\0';
			break;
		}
		if(c == '\0')
			continue;
		msg[t++] = c;
	}
        if(sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
	sleep(3);
	printf("Sending QUIT to server\n");
	strcpy(str, "QUIT");
	if(sendto(sockfd, str, sizeof(str), 0, (struct sockaddr*)&server, sizeof(server))<0)
                printf("Error in sendto\n");
        if((recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&server, &l)) < 0)
        	printf("Error in recv\n");
	if(strncmp(str, "221", 3))
        	printf("\nOK not received from server");
        printf("\nServer has send GOODBYE...Closing conn\n");
        printf("Bye\n");
        close(sockfd);
        return 0;
}


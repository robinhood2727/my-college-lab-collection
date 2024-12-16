#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>

void main(){
    int sock_fd;
    int buf[5];
    socklen_t len;
    sock_fd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in server;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_family=AF_INET;
    server.sin_port=htons(3031);

    printf("Enter two numbers to add: \n");
    scanf("%d",&buf[0]);
    scanf("%d",&buf[1]);

    len=sizeof(server);
    sendto(sock_fd,buf,5,0,(struct sockaddr*)&server,len);
    recvfrom(sock_fd,buf,5,0,(struct sockaddr*)&server,&len);
    
    printf("sum=%d\n",buf[0]);
    shutdown(sock_fd,2);
}
#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

void main(){
    int sock_fd;
    char buf[100];

    sock_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server;
    socklen_t len;

    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_family=AF_INET;
    server.sin_port=htons(3031);
    len=sizeof(server);

    if (connect(sock_fd,(struct sockaddr*)&server,len)==-1)
    {
        printf("error in connecting\n");
        exit(1);
    }

    recv(sock_fd,buf,sizeof(buf),0);
    printf("clinet1: %s\n",buf);

    
    do{
        printf("waiting for message from client1.\n");
        recv(sock_fd,buf,100,0);
        printf("client1: %s",buf);
        if(strncmp("!EXIT",buf,5)==0){break;}
        printf("Enter the message to send: ");
        fgets(buf,100,stdin);
        send(sock_fd,buf,100,0);
        if(strncmp("!EXIT",buf,5)==0){break;}
        
    }while(1);
    
    


    close(sock_fd);
}
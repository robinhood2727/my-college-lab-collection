#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>

void main(){
    int sock_fd;
    struct sockaddr_in server;
    sock_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sock_fd==-1){
        printf("Error in socket creation");
        exit(1);
    }
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_family=AF_INET;
    server.sin_port=htons(3030);
    
    char buf[100];
    int choice=1;
    do{
        socklen_t len=sizeof(server);
        printf("Enter the message to send: ");
        fgets(buf,100,stdin);
        sendto(sock_fd,buf,100,0,(struct sockaddr*)&server,len);
        if(strncmp("exit",buf,4)==0){break;}
        recvfrom(sock_fd,buf,100,0,(struct sockaddr*)&server,&len);
        printf("%s",buf);
        if(strncmp("exit",buf,4)==0){break;}
        
    }while(1);
    shutdown(sock_fd,2);
}

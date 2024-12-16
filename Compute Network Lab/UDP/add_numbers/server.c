#include<stdio.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

void main(){
    int sock_fd,sum;
    socklen_t len;
    int buf[5];
    struct sockaddr_in client;
    sock_fd=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_family=AF_INET;
    client.sin_port=htons(3031);
   
    len=sizeof(client);
    bind(sock_fd,(struct sockaddr*)&client,sizeof(client));
    recvfrom(sock_fd,buf,5,0,(struct sockaddr*)&client,&len);
    
    sum=buf[0]+buf[1];
    buf[0]=sum;  
    
    sendto(sock_fd,buf,5,0,(struct sockaddr*)&client,len);
    shutdown(sock_fd,2);   
}

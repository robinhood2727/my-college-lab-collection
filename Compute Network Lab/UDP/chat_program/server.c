  #include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>

void main(){
    int sock_fd;
    struct sockaddr_in client,extra;
    sock_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sock_fd==-1){
        printf("Socket creation failed");
        exit(1);
    }
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_family=AF_INET;
    client.sin_port=htons(3030);
    if((bind(sock_fd,(struct sockaddr*)&client,sizeof(client))>0)){
        printf("Error in binding");
        exit(1);
    }
    int choice=1;
    char buf[100];
    
    do{
        socklen_t len=sizeof(extra);
        if(recvfrom(sock_fd,buf,100,0,(struct sockaddr*)&extra,&len)<0){
            printf("Error in receving");
            exit(1);
        }
        
        printf("%s",buf);
        if(strncmp("exit",buf,4)==0){break;}
        printf("Enter the reply message: ");
        fgets(buf,100,stdin);
        if(sendto(sock_fd,buf,100,0,(struct sockaddr*)&extra,len)<0){
            printf("Error in sending");
            exit(1);
        }
        if(strncmp("exit",buf,4)==0){break;}
        
    }while(1);
    shutdown(sock_fd,2);
}

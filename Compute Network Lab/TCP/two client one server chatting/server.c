#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void main(){
    int sock_fd1,temp_sock_fd1,sock_fd2,temp_sock_fd2;
    char buf[100];

    sock_fd1=socket(AF_INET,SOCK_STREAM,0);
    sock_fd2=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in client1,client2;
    socklen_t len1,len2;

    client1.sin_addr.s_addr=INADDR_ANY;
    client1.sin_family=AF_INET;
    client1.sin_port=htons(3030);

    client2.sin_addr.s_addr=INADDR_ANY;
    client2.sin_family=AF_INET;
    client2.sin_port=htons(3031);

    
    if(bind(sock_fd1,(struct sockaddr*)&client1,sizeof(client1))==-1){
        printf("error in binding client1\n");
        exit(1);
    }

    if(listen(sock_fd1,5)==-1){
        printf("error in listening client1\n");
        exit(1);
    }

    len1=sizeof(client1);
    temp_sock_fd1=accept(sock_fd1,(struct sockaddr*)&client1,&len1);
    if(temp_sock_fd1==-1){
        printf("error in accept client1\n");
        exit(1);
    }
    printf("client1 connection established\n");
    send(temp_sock_fd1,"WAIT_FOR_CLIENT2",sizeof("WAIT_FOR_CLIENT2"),0);

    if(bind(sock_fd2,(struct sockaddr*)&client2,sizeof(client2))==-1){
        printf("error in binding clinet2\n");
        exit(1);
    }

    if(listen(sock_fd2,5)==-1){
        printf("error in listening client2\n");
        exit(1);
    }

    len2=sizeof(client2);
    temp_sock_fd2=accept(sock_fd2,(struct sockaddr*)&client2,&len2);
    if(temp_sock_fd2==-1){
        printf("error in accept client2\n");
        exit(1);
    }
    printf("client 2 connection established\n");
    send(temp_sock_fd2,"READY",sizeof("READY"),0);
    send(temp_sock_fd1,"READY",sizeof("READY"),0);

   do{
        recv(temp_sock_fd1,buf,sizeof(buf),0);
        printf("client1: %s",buf);
        send(temp_sock_fd2,buf,sizeof(buf),0);
        printf("forwared to clinet2\n\n");
        if (strncmp("!EXIT",buf,5)==0)
        {
            printf("client1 exited\n");            
            break;
        }
        recv(temp_sock_fd2,buf,sizeof(buf),0);
        printf("client2: %s",buf);
        send(temp_sock_fd1,buf,sizeof(buf),0);
        printf("forwared to clinet1\n\n");
        if (strncmp("!EXIT",buf,5)==0)
        {
            printf("client2 exited\n");
            break;
        }
        
   }while(1);



    close(sock_fd1);
    close(temp_sock_fd1);
    close(sock_fd2);
    close(temp_sock_fd2);
}

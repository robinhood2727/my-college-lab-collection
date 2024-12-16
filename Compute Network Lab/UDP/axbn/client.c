#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    char buffer[100];
    printf("Enter a message to be sent to the server: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Error sending data");
        close(sockfd); // Close the socket
        return 1;
    }

    printf("Message sent successfully!\n");

    // Close the socket
    close(sockfd);
    return 0;
}

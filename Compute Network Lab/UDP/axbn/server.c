#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in server, client; // Corrected variable name

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Error in bind()");
        close(sockfd); // Close the socket
        return 1;
    }

    char buffer[100];
    socklen_t server_len = sizeof(server); // Corrected variable name
    printf("Server waiting...\n");

    if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &server_len) < 0) {
        perror("Error in recvfrom()");
        close(sockfd); // Close the socket
        return 1;
    }

    printf("Received datagram: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}

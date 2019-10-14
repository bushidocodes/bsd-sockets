#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main() {
    // SOCK_STREAM means TCP.
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Specify where we want to connect
    // The struct uses a strange port representation, so we need to use a function to convert
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        printf("Error creating socket.");
    }

    // Receive data from the socket
    char server_response[256];
    recv(sock, &server_response, sizeof(server_response), 0);

    // Print out the server's response
    printf("The server sent the data: %s\n", server_response);

    // and then close the socket
    close(sock);

    return 0;
}
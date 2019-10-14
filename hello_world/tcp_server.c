#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main() {
    char server_message[256] = "Hello World!";
    int port = 9002;
    int connection_backlog_size = 1000;

    // Initialize socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Configure the connection struct
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == 0) {
        // Seems to block on listen before printing to console. Hmm.
        printf("Socket running on port %d.", port);
    } else {
        printf("Error binding to port %d.", port);
    }

    for (;;){
        // We can pass a struct that gets populated with metadata about the client socket (IP Addr, etc.)
        listen(sock, connection_backlog_size);
        int client_sock = accept(sock, NULL, NULL);
        // Receive data from the socket
        send(client_sock, &server_message, sizeof(server_message), 0);
        // Print out the server's response
        printf("Sending the data: %s\n", server_message);
    }

    // and then close the socket
    close(sock);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int port = 8005;
int connection_backlog_size = 1000;

void build_http_response(char *buffer){
    // Add the Header
    strcat(buffer, "HTTP/1.1 200 OK\r\n\n");

    // Read an HTML file
    FILE *html_data;
    if ((html_data = fopen("index.html", "r")) == NULL) {
        printf("Unable to open index.html");
    };    
    char line_buffer[100];
    fgets(line_buffer, 100, html_data);
    fclose(html_data);
    // Append as Body
    buffer = strcat(buffer, line_buffer);
}

int main() {

    // Build the HTTP Response string
    char http_response[2048];
    build_http_response(http_response);

    // Initialize socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Configure the connection struct
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == 0) {
        printf("Socket running on port %d.\n", port);
    } else {
        printf("Error binding to port %d.\n", port);
    }
    listen(sock, connection_backlog_size);

    for (;;){
        // We can pass a struct that gets populated with metadata about the client socket (IP Addr, etc.)
        int client_sock = accept(sock, NULL, NULL);
        send(client_sock, http_response, strlen(http_response) + 1, 0);
        close(client_sock);
    }
    close(sock);
    return 0;
}
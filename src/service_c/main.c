#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    
    char* server_ip = "127.0.0.1";
    int server_port = 8080;

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error - socket not created");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &(server_address.sin_addr));

    // trying connection
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connection =/!!");
        exit(EXIT_FAILURE);
    }

    // Receiving msg
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error - not receiving msg from server");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Message from Py module: %s\n", buffer);

    close(client_socket);

    return 0;
}

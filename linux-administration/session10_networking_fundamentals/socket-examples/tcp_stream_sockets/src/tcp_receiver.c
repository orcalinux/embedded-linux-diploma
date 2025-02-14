#include "common.h"

int main()
{
    int sockfd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("Socket creation failed");
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Bind failed");
    }

    // Listen for connections
    if (listen(sockfd, 5) < 0)
    {
        error("Listen failed");
    }

    printf("Waiting for incoming connections...\n");

    // Accept connection
    if ((new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0)
    {
        error("Accept failed");
    }

    // Receive data
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message received: %s\n", buffer);

    close(new_socket);
    close(sockfd);
    return 0;
}

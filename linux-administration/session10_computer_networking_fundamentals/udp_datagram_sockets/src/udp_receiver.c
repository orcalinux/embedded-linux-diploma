#include "common.h"

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        error("Socket creation failed");
    }

    // 2. Define server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any interface
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket to the specified address and port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Bind failed");
    }

    printf("UDP Receiver is listening on port %d...\n", PORT);

    // 4. Receive data from a client
    ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                      (struct sockaddr *)&client_addr, &client_len);
    if (bytes_received < 0)
    {
        error("recvfrom failed");
    }

    // Null-terminate the received data for safe printing
    if (bytes_received < BUFFER_SIZE)
        buffer[bytes_received] = '\0';

    printf("Received from client: %s\n", buffer);

    // 5. (Optional) Send a reply back to client
    // For demonstration, let's echo the same message back:
    ssize_t bytes_sent = sendto(sockfd, buffer, bytes_received, 0,
                                (struct sockaddr *)&client_addr, client_len);
    if (bytes_sent < 0)
    {
        error("sendto failed");
    }

    // 6. Close the socket
    close(sockfd);

    return 0;
}

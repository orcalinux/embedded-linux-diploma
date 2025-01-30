#include "common.h"

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = "Hello from UDP sender!";
    char recv_buffer[BUFFER_SIZE] = {0};
    socklen_t server_len = sizeof(server_addr);

    // 1. Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        error("Socket creation failed");
    }

    // 2. Define server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP from text to binary (e.g., 127.0.0.1)
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        error("Invalid address / Address not supported");
    }

    // 3. Send data to the server
    ssize_t bytes_sent = sendto(sockfd, buffer, strlen(buffer), 0,
                                (struct sockaddr *)&server_addr, server_len);
    if (bytes_sent < 0)
    {
        error("sendto failed");
    }
    printf("Message sent: %s\n", buffer);

    // 4. (Optional) Receive a reply from the server
    ssize_t bytes_received = recvfrom(sockfd, recv_buffer, BUFFER_SIZE, 0,
                                      (struct sockaddr *)&server_addr, &server_len);
    if (bytes_received < 0)
    {
        error("recvfrom failed");
    }

    // Null-terminate the received data for safe printing
    if (bytes_received < BUFFER_SIZE)
        recv_buffer[bytes_received] = '\0';

    printf("Received from server: %s\n", recv_buffer);

    // 5. Close the socket
    close(sockfd);

    return 0;
}

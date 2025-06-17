#include "bottom_layer.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define IPC_FIFO "/tmp/packet_pipe"

void bottom_init(void) {
    // Ensure the FIFO exists (create if needed)
    if (mkfifo(IPC_FIFO, 0666) == 0) {
        printf("[TX-Bottom] created FIFO %s\n", IPC_FIFO);
    } else {
        printf("[TX-Bottom] FIFO %s ready (already exists)\n", IPC_FIFO);
    }
}

void bottom_send(const uint8_t *data, size_t len) {
    // Show the raw bytes we’re about to send
    printf("[TX-Bottom] sending %zu bytes:", len);
    for (size_t i = 0; i < len; i++) {
        printf(" %02X", data[i]);
    }
    printf("\n");

    // Open and write into the IPC pipe
    int fd = open(IPC_FIFO, O_WRONLY);
    if (fd < 0) {
        perror("[TX-Bottom] open FIFO failed");
        return;
    }
    ssize_t written = write(fd, data, len);
    if (written < 0) {
        perror("[TX-Bottom] write FIFO failed");
    } else if ((size_t)written != len) {
        fprintf(stderr, "[TX-Bottom] partial write (%zd of %zu bytes)\n", written, len);
    } else {
        printf("[TX-Bottom] successfully wrote %zu bytes into %s\n", len, IPC_FIFO);
    }
    close(fd);
}

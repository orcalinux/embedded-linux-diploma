#include "bottom_layer.h"
#include "middle_layer.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define IPC_FIFO "/tmp/packet_pipe"

void bottom_init(void) {
    // Ensure FIFO exists
    if (mkfifo(IPC_FIFO, 0666) == 0) {
        printf("[RX-Bottom] created FIFO at %s\n", IPC_FIFO);
    } else {
        printf("[RX-Bottom] FIFO %s ready (already exists)\n", IPC_FIFO);
    }
}

void bottom_receive(const uint8_t *data, size_t len) {
    printf("[RX-Bottom] received %zu raw bytes, dispatching to Middle\n", len);
    middle_on_raw(data, len);
}

void bottom_listen(void) {
    int fd = open(IPC_FIFO, O_RDONLY);
    if (fd < 0) {
        perror("[RX-Bottom] open FIFO failed");
        return;
    }
    printf("[RX-Bottom] listening on FIFO %s\n", IPC_FIFO);

    uint8_t buf[256];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        printf("[RX-Bottom] read %zd bytes from FIFO\n", n);
        bottom_receive(buf, (size_t)n);
    }
    if (n == 0) {
        printf("[RX-Bottom] EOF on FIFO, exiting listen loop\n");
    } else if (n < 0) {
        perror("[RX-Bottom] read FIFO error");
    }
    close(fd);
    printf("[RX-Bottom] closed FIFO %s\n", IPC_FIFO);
}

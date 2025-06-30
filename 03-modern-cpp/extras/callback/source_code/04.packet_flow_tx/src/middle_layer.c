#include "middle_layer.h"
#include "bottom_layer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define SLIP_END     0xC0
#define SLIP_ESC     0xDB
#define SLIP_ESC_END 0xDC
#define SLIP_ESC_ESC 0xDD

void middle_init(void) {
    printf("[TX-Middle] initialized SLIP encoder\n");
}

void middle_send(const uint8_t *payload, size_t len) {
    // Show the original payload
    printf("[TX-Middle] original payload %zu bytes:", len);
    for (size_t i = 0; i < len; i++) {
        printf(" %02X", payload[i]);
    }
    printf("\n");

    // Allocate worst-case buffer (2× escapes + framing)
    size_t cap = len * 2 + 2;
    uint8_t *buf = malloc(cap);
    if (!buf) {
        fprintf(stderr, "[TX-Middle] malloc failed for cap=%zu\n", cap);
        return;
    }

    size_t idx = 0;
    buf[idx++] = SLIP_END;

    for (size_t i = 0; i < len; i++) {
        uint8_t b = payload[i];
        if (b == SLIP_END) {
            buf[idx++] = SLIP_ESC;
            buf[idx++] = SLIP_ESC_END;
        } else if (b == SLIP_ESC) {
            buf[idx++] = SLIP_ESC;
            buf[idx++] = SLIP_ESC_ESC;
        } else {
            buf[idx++] = b;
        }
    }

    buf[idx++] = SLIP_END;

    // Show the SLIP-encoded frame
    printf("[TX-Middle] SLIP-encoded %zu bytes:", idx);
    for (size_t i = 0; i < idx; i++) {
        printf(" %02X", buf[i]);
    }
    printf("\n");

    // Forward to Bottom
    printf("[TX-Middle] sending %zu bytes to Bottom\n", idx);
    bottom_send(buf, idx);

    free(buf);
}

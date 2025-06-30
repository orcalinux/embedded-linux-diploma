#include "middle_layer.h"
#include <stdio.h>
#include <stdlib.h>

#define SLIP_END     0xC0
#define SLIP_ESC     0xDB
#define SLIP_ESC_END 0xDC
#define SLIP_ESC_ESC 0xDD

#define MAX_TOP_CBS  10

static PacketCB top_cbs[MAX_TOP_CBS];
static int      top_count = 0;

static uint8_t *rx_buf   = NULL;
static size_t   rx_len   = 0, rx_cap = 0;
static int      esc_flag = 0;

// Helper: package current buffer into a Packet and invoke all Top callbacks
static void deliver_to_top(void) {
    Packet pkt = { rx_buf, rx_len };
    printf("[RX-Middle] delivering %zu decoded bytes to Top\n", rx_len);
    for (int j = 0; j < top_count; j++) {
        top_cbs[j](&pkt);
    }
    rx_len = 0;  // reset for next packet
}

// Initialize SLIP decoder state
void middle_init(void) {
    rx_cap   = 256;
    rx_buf   = malloc(rx_cap);
    if (!rx_buf) {
        fprintf(stderr, "[RX-Middle] middle_init: malloc failed\n");
        exit(1);
    }
    rx_len   = 0;
    esc_flag = 0;
    printf("[RX-Middle] initialized SLIP decoder (cap=%zu)\n", rx_cap);
}

// Register a Top‐layer callback
int middle_register_top(PacketCB cb) {
    if (top_count < MAX_TOP_CBS) {
        top_cbs[top_count] = cb;
        printf("[RX-Middle] registered Top callback #%d\n", top_count + 1);
        top_count++;
        return 0;
    }
    fprintf(stderr, "[RX-Middle] middle_register_top: too many callbacks\n");
    return -1;
}

// SLIP‐decode raw bytes and invoke deliver_to_top() when a full frame ends
void middle_on_raw(const uint8_t *data, size_t len) {
    printf("[RX-Middle] on_raw: processing %zu bytes\n", len);
    for (size_t i = 0; i < len; i++) {
        uint8_t b = data[i];
        printf("[RX-Middle] byte[%zu]=0x%02X\n", i, b);

        if (b == SLIP_END) {
            printf("[RX-Middle] SLIP_END encountered\n");
            if (rx_len > 0) {
                deliver_to_top();
            }
        }
        else if (b == SLIP_ESC) {
            esc_flag = 1;
            printf("[RX-Middle] SLIP_ESC encountered, next byte will be escaped\n");
        }
        else {
            // unescape if needed
            if (esc_flag) {
                if      (b == SLIP_ESC_END) { b = SLIP_END;  printf("[RX-Middle] unescaped to SLIP_END\n"); }
                else if (b == SLIP_ESC_ESC) { b = SLIP_ESC;  printf("[RX-Middle] unescaped to SLIP_ESC\n"); }
                else                        { printf("[RX-Middle] unknown escape 0x%02X\n", b); }
                esc_flag = 0;
            }
            // grow buffer if full
            if (rx_len >= rx_cap) {
                rx_cap *= 2;
                rx_buf = realloc(rx_buf, rx_cap);
                if (!rx_buf) {
                    fprintf(stderr, "[RX-Middle] middle_on_raw: realloc failed\n");
                    exit(1);
                }
                printf("[RX-Middle] expanded buffer to cap=%zu\n", rx_cap);
            }
            rx_buf[rx_len++] = b;
            printf("[RX-Middle] buffered byte 0x%02X (len=%zu)\n", b, rx_len);
        }
    }
}

#include "top_layer.h"
#include <stdio.h>

static void top_on_decoded(Packet *pkt) {
    printf("[RX-Top   ] processing %zu bytes:", pkt->len);
    for (size_t i = 0; i < pkt->len; i++)
        printf(" %02X", pkt->data[i]);
    printf("\n");
}

void top_init(void) {
    middle_register_top(top_on_decoded);
}

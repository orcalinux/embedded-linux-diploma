#include "top_layer.h"
#include "middle_layer.h"
#include <stdio.h>
#include <stdint.h>

void top_send_test(void) {
    uint8_t payload[] = { 0x01, 0xC0, 0x02, 0xDB };
    size_t  len       = sizeof(payload);

    printf("[TX-Top   ] preparing %zu-byte payload\n", len);
    middle_send(payload, len);
}

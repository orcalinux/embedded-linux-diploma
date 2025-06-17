#ifndef MIDDLE_LAYER_H
#define MIDDLE_LAYER_H

#include <stddef.h>
#include <stdint.h>

// Packet descriptor
typedef struct {
    uint8_t *data;
    size_t   len;
} Packet;

// Callback type
typedef void (*PacketCB)(Packet *pkt);

// Initialize data-link (allocates SLIP state)
void middle_init(void);

// Register application callback
int middle_register_top(PacketCB cb);

// Internal: SLIP-decode raw bytes and invoke top callbacks
void middle_on_raw(const uint8_t *data, size_t len);

#endif // MIDDLE_LAYER_H

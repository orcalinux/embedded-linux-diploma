#ifndef BOTTOM_LAYER_H
#define BOTTOM_LAYER_H

#include <stddef.h>
#include <stdint.h>

// Initialize bottom (no-op)
void bottom_init(void);

// Send a raw SLIP-encoded buffer into the IPC FIFO
void bottom_send(const uint8_t *data, size_t len);

#endif // BOTTOM_LAYER_H

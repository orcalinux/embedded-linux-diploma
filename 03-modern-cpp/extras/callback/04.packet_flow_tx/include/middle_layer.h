#ifndef MIDDLE_LAYER_H
#define MIDDLE_LAYER_H

#include <stddef.h>
#include <stdint.h>

// Initialize middle (no-op)
void middle_init(void);

// SLIP-encode payload[0..len) and forward to bottom_send()
void middle_send(const uint8_t *payload, size_t len);

#endif // MIDDLE_LAYER_H

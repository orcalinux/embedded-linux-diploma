#ifndef BOTTOM_LAYER_H
#define BOTTOM_LAYER_H

#include <stddef.h>
#include <stdint.h>

// Initialize bottom (creates FIFO)
void bottom_init(void);

// Blockingly read from FIFO and dispatch bytes upstream
void bottom_listen(void);

// Internal: deliver raw bytes to middle_on_raw()
void bottom_receive(const uint8_t *data, size_t len);

#endif // BOTTOM_LAYER_H

#ifndef SIGNAL_H
#define SIGNAL_H

#define MAX_SLOTS	10

typedef void(*slot_func_t)(void *ctx);

typedef struct {
	slot_func_t slots[MAX_SLOTS];
	void *context[MAX_SLOTS];
	int count;
} singal_t;

void signal_init(singal_t *sig);

int singal_connect(singal_t *sig, slot_func_t slot, void *ctx);

void singal_emit(singal_t *sig);

int singal_disconnect(singal_t *sig, slot_func_t slot);

#endif // SIGNAL_H
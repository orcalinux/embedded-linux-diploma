#include "signal.h"
#include "string.h"

void signal_init(singal_t *sig) {
	memset(sig->slots, 0, sizeof(sig->slots));
	sig->count = 0;
}

int singal_connect(singal_t *sig, slot_func_t slot, void *ctx) {
	if (sig->count >= MAX_SLOTS) {
		return -1;
	}
	
	sig->slots[sig->count] = slot;
	sig->context[sig->count] = ctx;
		
	sig->count++;
	return 0;
}

void singal_emit(singal_t *sig) {
	for (size_t i = 0; i < sig->count; i++) {
		sig->slots[i](sig->context[i]);
	}
}

int singal_disconnect(singal_t *sig, slot_func_t slot) {
	for (size_t i = 0; i < sig->count; i++) {
		if(sig->slots[i] == slot) {
			// shift
			for (size_t j = i; j < sig->count - 1; j++)
			{
				sig->slots[j] = sig->slots[j + 1];
				sig->context[j] = sig->context[j + 1];
			}
			sig->slots[sig->count - 1] = NULL;
			sig->context[sig->count - 1] = NULL;
			sig->count--;
			return 0;
		}
	}
	return -1;
}

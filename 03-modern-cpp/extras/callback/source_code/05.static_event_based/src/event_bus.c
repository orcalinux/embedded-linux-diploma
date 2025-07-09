#include "event_bus.h"

void event_bus_init(event_bus_t *bus) {
	if(!bus) {
		return;
	}
	memset(bus->sub, 0, sizeof(bus->sub));
	bus->count = 0;
}

int event_bus_subscribe(event_bus_t *bus, event_cb_t cb) {
	if(!(bus && cb)) {
		return -1;
	}

	if(bus->count >= MAX_SUBSCRIBERS) {
		return -2;
	}

	bus->sub[bus->count++] = cb;

	return 0;
}

void event_bus_publish(event_bus_t *bus, int code) {
	if(!bus) {
		return;
	}

	for(size_t i = 0; i < bus->count; i++) {
		bus->sub[i](code);
	}
}

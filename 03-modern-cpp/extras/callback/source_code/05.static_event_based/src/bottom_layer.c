#include <stdio.h>
#include "bottom_layer.h"

void bottom_do_work(event_bus_t *bus) {
	printf("[BOTTOM] performing work...\n");
	int code = 42;
	event_bus_publish(bus, code);
}

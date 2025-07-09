#include <stdio.h>
#include "middle_layer.h"

static void middle_on_event1(int code) {
	printf("[MIDDLE] handler1 got id %d\n", code);
}

static void middle_on_event2(int code) {
	printf("[MIDDLE] handler2 got id %d\n", code);
}

void middle_init(event_bus_t *bus) {
	if(!bus) {
		return;
	}

	printf("[MIDDLE] register handler1\n");
	event_bus_subscribe(bus, middle_on_event1);

	printf("[MIDDLE] register handler2\n");
	event_bus_subscribe(bus, middle_on_event2);
}

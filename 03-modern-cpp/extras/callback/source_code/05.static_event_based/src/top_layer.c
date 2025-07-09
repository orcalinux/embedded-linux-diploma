#include <stdio.h>
#include "top_layer.h"
#include "middle_layer.h"
#include "bottom_layer.h"


static void top_on_event(int code) {
	printf("[TOP   ] received event %d \n", code);
}

void top_init(event_bus_t *bus) {
	if(!bus) {
		return;
	}

	event_bus_subscribe(bus, top_on_event);
}

void top_do_work(event_bus_t *bus) {
	printf("[TOP   ] invoke middle && bottom\n");
	middle_init(bus);
	bottom_do_work(bus);
}


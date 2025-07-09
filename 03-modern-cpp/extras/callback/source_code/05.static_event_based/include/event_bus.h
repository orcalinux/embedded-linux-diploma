#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <stddef.h>
#include <string.h>

#define MAX_SUBSCRIBERS	10

typedef void (*event_cb_t)(int code);

typedef struct {
	event_cb_t sub[MAX_SUBSCRIBERS];
	size_t     count;
} event_bus_t;


void event_bus_init(event_bus_t *bus);

int event_bus_subscribe(event_bus_t *bus, event_cb_t cb);

void event_bus_publish(event_bus_t *bus, int code);


#endif // EVENT_BUS_H

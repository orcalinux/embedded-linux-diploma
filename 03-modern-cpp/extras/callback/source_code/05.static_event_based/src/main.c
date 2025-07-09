#include <stdio.h>
#include "top_layer.h"

int main() {
	event_bus_t bus;

	event_bus_init(&bus);

	top_init(&bus);

	printf("===== Begin Flow ====\n");
	top_do_work(&bus);
	printf("===== End Flow ====\n");
}

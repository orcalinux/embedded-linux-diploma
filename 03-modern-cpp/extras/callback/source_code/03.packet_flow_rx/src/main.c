#include "bottom_layer.h"
#include "middle_layer.h"
#include "top_layer.h"

int main(void) {
    bottom_init();
    middle_init();
    top_init();

    bottom_listen();
    return 0;
}

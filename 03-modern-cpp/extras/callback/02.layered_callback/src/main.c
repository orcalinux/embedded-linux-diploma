#include <stdio.h>

typedef void (*middle_callback_t)(int);
typedef void (*top_callback_t)(int);

// Forward Declarations
void middle_do_work(void);
void bottom_do_work(void);
int bottom_register_middle(middle_callback_t cb);
void bottom_notify(int code);
int middle_register_top(top_callback_t cb);
void middle_notify(int code);

// ======================= Top Layer =======================
void top_callback(int code) {
    printf("[TOP   ]   Callback invoked with code %d\n", code);
    if (code == 33) {
        printf("[TOP   ]   Decoded message: \"hello\"\n");
    }
}

void top_init(void) {
    printf("[TOP   ]   Initializing top layer...\n");
    middle_register_top(top_callback);
    printf("[TOP   ]   Directly invoking middle and bottom work routines\n");
    middle_do_work();
    bottom_do_work();
}

// ======================= Middle Layer =======================
static top_callback_t g_top_cb = NULL;

void middle_callback(int code) {
    printf("[MIDDLE]   Callback received from bottom: code %d\n", code);
}

void middle_do_work(void) {
    printf("[MIDDLE]   Performing middle-layer work\n");
}

void middle_init(void) {
    printf("[MIDDLE]   Initializing middle layer...\n");
    bottom_register_middle(middle_callback);
}

int middle_register_top(top_callback_t cb) {
    if (!cb) {
        return -1;
    }
    g_top_cb = cb;
    return 0;
}

void middle_notify(int code) {
    printf("[MIDDLE]   Notifying top layer with code %d\n", code);
    if (g_top_cb) {
        g_top_cb(code);
    }
}

// ======================= Bottom Layer =======================
static middle_callback_t g_mid_cb = NULL;

void bottom_do_work(void) {
    printf("[BOTTOM]   Performing bottom-layer work\n");
}

void bottom_init(void) {
    printf("[BOTTOM]   Initializing bottom layer...\n");
}

int bottom_register_middle(middle_callback_t cb) {
    if (!cb) {
        return -1;
    }
    g_mid_cb = cb;
    return 0;
}

void bottom_notify(int code) {
    printf("[BOTTOM]   Notifying middle layer with code %d\n", code);
    if (g_mid_cb) {
        g_mid_cb(code);
    }
}

// ======================= Main =======================
int main(void) {
	printf("-- Starting the Demo --\n");
    int code = 33;

    bottom_init();
    middle_init();
    top_init();

    printf("\n-- External notifications --\n");
    bottom_notify(code);
    middle_notify(code);

    return 0;
}

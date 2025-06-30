#include <stdio.h>
#include "signal.h"

void say_hello(void *ctx) {
	char *context = (char *)ctx;
	printf("%s\n", context);
}

void say_goodbye(void *ctx) {
	char *context = (char *)ctx;
	printf("%s\n", context);
}

void print_name(void *ctx) {
	char *context = (char *)ctx;
	printf("%s\n", context);
}

int main(void) {
	singal_t sig_1, sig_2;
	
	signal_init(&sig_1);
	signal_init(&sig_2);
	
	singal_connect(&sig_1, say_hello, "say_hello");
	singal_connect(&sig_1, say_goodbye, "say_goodbye");
	
	singal_connect(&sig_2, print_name, "print_name");
	
	printf("---- Before disconnect ----\n");
	singal_emit(&sig_1);
	
	singal_disconnect(&sig_1, say_goodbye);
	
	printf("---- After disconnect ----\n");
	singal_emit(&sig_1);
	
	printf("---- Emit sig_2 ----\n");
	singal_emit(&sig_2);
	
	
	return 0;
}
























/*
void say_hello(void *ctx) {
    const char *name = (const char*)ctx;
    printf("Hello, %s!\n", name);
}

void say_goodbye(void *ctx) {
    const char *name = (const char*)ctx;
    printf("Goodbye, %s!\n", name);
}

int main(void) {
	
    signal_t button_signal;
    signal_init(&button_signal);

    // Connect slots with their contexts
    signal_connect(&button_signal, say_hello,   "Alice");
    signal_connect(&button_signal, say_goodbye, "Bob");

    printf("-- Emitting signal --\n");
    signal_emit(&button_signal);
    
    printf("-- Disconnecting say_hello --\n");
    signal_disconnect(&button_signal, say_hello);
    
    printf("-- Emitting signal again --\n");
    signal_emit(&button_signal);

    return 0;
}*/
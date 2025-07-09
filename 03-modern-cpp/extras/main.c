#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *pthread_cb_demo(void *thread_input) {
	char *input = (char *)thread_input;
	
	while(1) {
		printf("input string: %s", input);
		sleep(1);
	}
}

void thread1_create() {
	pthread_t pthread1;
	
	static char *thread_input = "Hello, my name is Mahmoud Abdelraouf\n";

	pthread_create(&pthread1,
				   NULL,
				   pthread_cb_demo,
				   (void *)thread_input);
}

int main() {
	
	printf("Hello from the main thread\n");
	thread1_create();
	pthread_exit(0);
	printf("After terminate the main thread\n");
	return 0;
}

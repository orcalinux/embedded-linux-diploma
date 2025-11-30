#include <stdio.h>

int main() {
	char test[] = "C++ is fun"; 
	printf("Before any change: %s\n", test);
	test[0] = 'c';
	printf("After change: %s\n", test);

	return 0;
}

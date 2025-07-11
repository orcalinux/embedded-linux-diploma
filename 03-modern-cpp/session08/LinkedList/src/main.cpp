#include <iostream>
#include "LinkedList.hpp"

int main() {
	LinkedList ll;
	ll.pushFront(10);
	ll.pushBack(20);
	ll.pushFront(5);
	// list is now: 5, 10, 20

	std::cout << ll.front() << "\n";  // 5
	std::cout << ll.back()  << "\n";  // 20

	int a = ll.popFront();            // removes 5
	int b = ll.popBack();             // removes 20
	ll.print();                       // prints: 10

	return 0;
}

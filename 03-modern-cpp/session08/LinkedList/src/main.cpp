#include <iostream>
#include "LinkedList.hpp"

int main() {
	LinkedList ll;
	ll.push_front(10);
	ll.push_back(20);
	ll.push_front(5);
	// list is now: 5, 10, 20

	std::cout << ll.front() << "\n";  // 5
	std::cout << ll.back()  << "\n";  // 20

//	int a = ll.pop_front();            // removes 5
//	int b = ll.pop_back();             // removes 20
	ll.print();                       // prints: 10

	return 0;
}

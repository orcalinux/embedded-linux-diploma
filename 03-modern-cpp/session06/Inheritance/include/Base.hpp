#ifndef INCLUDE_BASE_HPP_
#define INCLUDE_BASE_HPP_

#include <iostream>

class Base {
private:
	int x;

protected:
	int shared;

public:
	Base();

	Base(int x, int s);

	void show() const;
};

#endif /* INCLUDE_BASE_HPP_ */


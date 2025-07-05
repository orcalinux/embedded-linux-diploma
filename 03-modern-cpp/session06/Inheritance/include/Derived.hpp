#ifndef INCLUDE_DERIVED_HPP_
#define INCLUDE_DERIVED_HPP_

#include "Base.hpp"

class Derived : public Base {
private:
	int y;

public:
	Derived();

	Derived(int y);

	void display() const;
};


#endif /* INCLUDE_DERIVED_HPP_ */

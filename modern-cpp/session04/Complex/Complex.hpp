/**
 * Complex.hpp
 *
 *  Created on: May 9, 2025
 *      Author: mahmoud
 */
#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <ostream>

class Complex
{
private:
	int real;
	int imag;

public:
	// Default constructor
	Complex() : Complex(0, 0) {}

	// Constructor
	Complex(int real, int imag);

	// Copy constructor
	Complex(const Complex &c);

	// Add function
	void add(Complex &c);

	// Display function
	void display();

	// Friend Method
	friend Complex operator+(Complex &c1, Complex &c2);
	friend std::ostream &operator<<(std::ostream &out, Complex &c);
	friend std::istream &operator>>(std::istream &in, Complex &c);
};

#endif /* COMPLEX_HPP_ */

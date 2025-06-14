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
	static int count; // declare static variable

	// Default constructor
	Complex();

	// Constructor
	Complex(int real, int imag);

	// Copy constructor
	Complex(const Complex &c);

	// Destructor
	~Complex();

	// Add function
	void add(Complex &c);

	// Display function
	void display();

	// Friend Methods
	friend Complex operator+(Complex &c1, Complex &c2);
	friend std::ostream &operator<<(std::ostream &out, Complex &c);
	friend std::istream &operator>>(std::istream &in, Complex &c);
};

#endif /* COMPLEX_HPP_ */

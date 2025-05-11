/**
 * Complex.cpp
 *
 *  Created on: May 9, 2025
 *      Author: mahmoud
 */
#include "Complex.hpp"
#include <iostream>

int Complex::count = 0;

Complex::Complex(int real, int imag) : real(real), imag(imag) {}

Complex::Complex(const Complex &c) : real(c.real), imag(c.imag)
{
	std::cout << "Copy constructor called" << std::endl;
}

void Complex::add(Complex &c)
{
	this->real += c.real;
	this->imag += c.imag;
}

void Complex::display()
{
	std::cout << real << " + " << imag << "i" << std::endl;
}

Complex operator+(Complex &c1, Complex &c2)
{
	Complex temp;
	temp.imag = c1.imag + c2.imag;
	temp.real = c1.real + c2.real;
	return temp;
}

std::istream &operator>>(std::istream &in, Complex &c)
{
	in >> c.real >> c.imag;
	return in;
}

std::ostream &operator<<(std::ostream &out, Complex &c)
{

	out << c.real << " + " << c.imag << "i" << std::endl;
	return out;
}
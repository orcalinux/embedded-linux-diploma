/**
 * main.cpp
 *
 *  Created on: May 9, 2025
 *      Author: mahmoud
 */
#include <iostream>
#include "Complex.hpp"

int main()
{

	Complex c1(5, 10), c2(4, 7), c3;
	c1.count = 10;
	std::cout << c1;

	std::cout << "Enter numbers in form: real, imag: ";
	std::cin >> c1;

	c3 = c1 + c2;

	std::cout << c3;
	std::cout << c1;
}
/**
 * main.cpp
 *
 *  Created on: May 10, 2025
 *      Author: mahmoud
 */
#include <iostream>
#include "Integer.hpp"

Integer add(int a, int b)
{
    Integer temp(a + b);
    return temp;
}

int main()
{
    alignas(Integer) unsigned char buffer[sizeof(Integer)];
    Integer *p = new (buffer) Integer(42);

    std::cout << "Value: " << *p << std::endl;

    p->~Integer();

    return 0;
}

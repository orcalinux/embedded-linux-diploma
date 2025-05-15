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
    Integer a = 3; // Integer a = Integer(3);
    return 0;
}

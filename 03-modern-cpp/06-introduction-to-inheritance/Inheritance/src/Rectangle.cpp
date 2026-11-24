#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle()
  : length(0), breadth(0)
{
    std::cout << "[Rectangle] Default constructor called\n"
              << "             length  = " << length << "\n"
              << "             breadth = " << breadth << "\n";
}

Rectangle::Rectangle(int l, int b)
  : length(l), breadth(b)
{
    std::cout << "[Rectangle] Parameterized constructor called\n"
              << "             length  = " << length << "\n"
              << "             breadth = " << breadth << "\n";
}

int Rectangle::getLength() const
{
    return length;
}

int Rectangle::getBreadth() const
{
    return breadth;
}

void Rectangle::setLength(int l)
{
    if (l > 0) {
        length = l;
    } else {
        std::cerr << "[Rectangle] setLength() ignored invalid value: " << l << "\n";
    }
}

void Rectangle::setBreadth(int b)
{
    if (b > 0) {
        breadth = b;
    } else {
        std::cerr << "[Rectangle] setBreadth() ignored invalid value: " << b << "\n";
    }
}

int Rectangle::area() const
{
    int a = length * breadth;
    return a;
}

int Rectangle::perimeter() const
{
    int p = 2 * (length + breadth);
    return p;
}

#include "Derived.hpp"
#include <iostream>

Derived::Derived()
  : y(0)
{
    std::cout << "[Derived] Default constructor called\n"
              << "          y       = " << y << "\n"
              << "          shared  = " << shared << "\n";
}

Derived::Derived(int yVal)
  : y(yVal)
{
    std::cout << "[Derived] Parameterized constructor called\n"
              << "          y       = " << y << "\n";
}

void Derived::display() const
{
    std::cout << "[Derived] display() -> y = " << y << "\n";
}

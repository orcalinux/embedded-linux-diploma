#include "Base.hpp"
#include <iostream>

Base::Base()
  : x(0), shared(120)
{
    std::cout << "[Base] Default constructor called\n"
              << "        x       = " << x << "\n"
              << "        shared  = " << shared << "\n";
}

Base::Base(int x, int s)
  : x(x), shared(s)
{
    std::cout << "[Base] Parameterized constructor called\n"
              << "        x       = " << this->x << "\n"
              << "        shared  = " << shared << "\n";
}

void Base::show() const
{
    std::cout << "[Base] show() -> x = " << x << "\n";
}

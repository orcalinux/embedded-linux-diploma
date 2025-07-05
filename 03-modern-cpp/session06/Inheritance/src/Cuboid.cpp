#include "Cuboid.hpp"
#include <iostream>

Cuboid::Cuboid()
  : Rectangle(0, 0)
  , height(0)
{
    std::cout << "[Cuboid] Default constructor called\n"
              << "         length    = " << getLength()  << "\n"
              << "         breadth   = " << getBreadth() << "\n"
              << "         height    = " << height       << "\n";
}

Cuboid::Cuboid(int l, int b, int h)
  : Rectangle(l, b)
  , height(h)
{
    std::cout << "[Cuboid] Parameterized constructor called\n"
              << "         length    = " << getLength()  << "\n"
              << "         breadth   = " << getBreadth() << "\n"
              << "         height    = " << height       << "\n";
}

int Cuboid::getHeight() const
{
    return height;
}

void Cuboid::setHeight(int h)
{
	if (h > 0) {
		height = h;
	} else {
		std::cerr << "[Cuboid] setHeight() ignored invalid value: " << h << "\n";
	}
}

int Cuboid::volume() const
{
    int v = getLength() * getBreadth() * height;
    return v;
}

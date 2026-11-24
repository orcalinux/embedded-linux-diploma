#include <iostream>
#include "Base.hpp"
#include "Derived.hpp"
#include "Rectangle.hpp"
#include "Cuboid.hpp"

int main() {
    // --- Test Base ---
    std::cout << "\n-- Testing Base --\n";
    Base b1;                // default
    b1.show();
    Base b2(7, 250);        // param ctor
    b2.show();

    // --- Test Derived ---
    std::cout << "\n-- Testing Derived --\n";
    Derived d1;             // default
    d1.display();
    Derived d2(42);         // param ctor
    d2.display();

    // --- Test Rectangle ---
    std::cout << "\n-- Testing Rectangle --\n";
    Rectangle r1;           // default
    r1.setLength(4);
    r1.setBreadth(3);
    std::cout << "Area: "      << r1.area()      << "\n";
    std::cout << "Perimeter: " << r1.perimeter() << "\n";

    Rectangle r2(6, 2);     // param ctor
    std::cout << "Area: "      << r2.area()      << "\n";
    std::cout << "Perimeter: " << r2.perimeter() << "\n";

    // --- Test Cuboid ---
    std::cout << "\n-- Testing Cuboid --\n";
    Cuboid c1;              // default
    c1.setLength(2);
    c1.setBreadth(3);
    c1.setHeight(5);
    std::cout << "Volume: " << c1.volume() << "\n";

    Cuboid c2(4, 5, 6);      // param ctor
    std::cout << "Volume: " << c2.volume() << "\n";

    return 0;
}

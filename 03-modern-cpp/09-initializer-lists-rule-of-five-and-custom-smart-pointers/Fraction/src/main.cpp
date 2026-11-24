#include "Fraction.hpp"
#include <iostream>

int main() {
    Fraction f1(10, 7), f2(8, 11), f3;

    // Initial values
    std::cout << "Initial values:\n"
              << "  f1 = " << f1 << "\n"
              << "  f2 = " << f2 << "\n\n";

    // Sum before any increments
    f3 = f1 + f2;
    std::cout << "Sum before increments: f1 + f2 = " << f3 << "\n\n";

    // Post-increment f1
    std::cout << "Post-increment: f1++ returns " << f1++
              << "  (now f1 = " << f1 << ")\n";

    // Pre-increment f2
    std::cout << "Pre-increment: ++f2 sets f2 = " << ++f2 << "\n\n";

    // Sum after increments
    f3 = f1 + f2;
    std::cout << "Sum after increments: new f1 + new f2 = " << f3 << "\n";


    return 0;
}

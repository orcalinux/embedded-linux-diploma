#include "UniquePtr.hpp"
#include <cassert>
#include <iostream>

int main() {
    UniquePtr p1;
    assert(!p1);
    std::cout << "p1 is null\n";

    UniquePtr p2(new int(42));
    assert(p2 && *p2 == 42);
    std::cout << "p2 = " << *p2 << "\n";

    UniquePtr p3(std::move(p2));
    assert(!p2 && p3 && *p3 == 42);
    std::cout << "after move, p2 is " << (p2 ? "not-null" : "null")
              << ", p3 = " << *p3 << "\n";

    p3.reset(new int(100));
    assert(p3 && *p3 == 100);
    std::cout << "after reset, p3 = " << *p3 << "\n";

    int* raw = p3.release();
    assert(!p3 && raw && *raw == 100);
    std::cout << "after release, raw = " << *raw << "\n";
    delete raw;

    std::cout << "All tests passed\n";
    return 0;
}

#include <iostream>
#include <cassert>
#include "DynamicArray.hpp"

void test_push_and_access() {
    DynamicArray d(2);
    assert(d.size() == 0);
    assert(d.capacity() == 2);

    // Push beyond initial capacity to force a resize
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);  // should resize from 2 → 4
    assert(d.size() == 3);
    assert(d.capacity() == 4);

    // Verify contents
    assert(d[0] == 1);
    assert(d[1] == 2);
    assert(d[2] == 3);

    // Mutate via operator[]
    d[1] = 42;
    assert(d[1] == 42);
}

void test_copy_constructor() {
    DynamicArray orig(3);
    orig.push_back(5);
    orig.push_back(6);
    orig.push_back(7);

    DynamicArray copy(orig);
    // Copy should have the same size/capacity and contents
    assert(copy.size()     == orig.size());
    assert(copy.capacity() == orig.capacity());
    for (std::size_t i = 0; i < orig.size(); ++i)
        assert(copy[i] == orig[i]);

    // Mutating original must not affect the copy
    orig[0] = 99;
    assert(copy[0] == 5);
}

void test_copy_assignment() {
    DynamicArray a(1);
    a.push_back(9);

    DynamicArray b(5);
    b.push_back(1);
    b.push_back(2);

    b = a;  // copy-assign smaller → larger
    assert(b.size()     == 1);
    assert(b[0]         == 9);

    // Self-assignment should be safe
    b = b;
    assert(b.size() == 1 && b[0] == 9);
}

void test_move_constructor() {
    DynamicArray temp(4);
    temp.push_back(11);
    temp.push_back(22);

    DynamicArray moved(std::move(temp));
    // moved-from temp should be empty
    assert(temp.size()     == 0);
    assert(temp.capacity() == 0);

    // New one has the data
    assert(moved.size()    == 2);
    assert(moved[0]        == 11);
    assert(moved[1]        == 22);
}

void test_move_assignment() {
    DynamicArray x(3);
    x.push_back(7);
    x.push_back(8);

    DynamicArray y(1);
    y = std::move(x);
    // moved-from x is empty
    assert(x.size()     == 0);
    assert(x.capacity() == 0);

    // y now has the contents
    assert(y.size()    == 2);
    assert(y[0]        == 7);
    assert(y[1]        == 8);

    // Self move‑assignment is safe
    y = std::move(y);
    assert(y.size() == 2 && y[0] == 7 && y[1] == 8);
}

int main() {
    test_push_and_access();
    test_copy_constructor();
    test_copy_assignment();
    test_move_constructor();
    test_move_assignment();

    std::cout << "All DynamicArray tests passed successfully!\n";
    return 0;
}

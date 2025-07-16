#include <iostream>
#include <cassert>
#include "SharedPtr.hpp"

void testConstruction() {
    SharedPtr p(new int(5));
    assert(p);                           // operator bool
    assert(p.get_count() == 1);          // single owner
    assert(*p == 5);                     // value check
    std::cout << "[PASS] Construction\n";
}

void testCopy() {
    SharedPtr p1(new int(42));
    SharedPtr p2(p1);                    // copy ctor
    assert(p1.get_count() == 2);
    assert(p2.get_count() == 2);
    assert(*p2 == 42);
    std::cout << "[PASS] Copy semantics\n";
}

void testCopyAssignment() {
    SharedPtr p1(new int(7));
    SharedPtr p2;
    p2 = p1;                             // copy assignment
    assert(p1.get_count() == 2);
    assert(p2.get_count() == 2);
    assert(*p1 == *p2 && *p1 == 7);
    std::cout << "[PASS] Copy-assignment semantics\n";
}

void testMove() {
    SharedPtr p1(new int(99));
    SharedPtr p2(std::move(p1));        // move ctor
    assert(p2.get_count() == 1);
    assert(!p1);                        // p1 should be empty
    assert(p1.get_count() == -1);
    std::cout << "[PASS] Move-construction\n";

    SharedPtr p3(new int(1));
    SharedPtr p4;
    p4 = std::move(p3);                 // move assignment
    assert(p4.get_count() == 1);
    assert(!p3);
    std::cout << "[PASS] Move-assignment\n";
}

void testReset() {
    SharedPtr p(new int(13));
    p.reset(new int(31));
    assert(p.get_count() == 1);
    assert(*p == 31);
    std::cout << "[PASS] Reset\n";
}

void testSelfAssignment() {
    SharedPtr p(new int(123));
    p = p;                               // no-op
    assert(p.get_count() == 1);
    assert(*p == 123);
    std::cout << "[PASS] Self-assignment\n";
}

int main() {
    std::cout << "Running SharedPtr tests...\n\n";
    testConstruction();
    testCopy();
    testCopyAssignment();
    testMove();
    testReset();
    testSelfAssignment();
    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}

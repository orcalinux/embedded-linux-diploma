#ifndef INCLUDE_DYNAMICARRAY_HPP_
#define INCLUDE_DYNAMICARRAY_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>

class DynamicArray {

public:

    DynamicArray(std::size_t cap);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other);
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other);
    ~DynamicArray();

    void push_back(int v);

    int& operator[](std::size_t i);
    int const& operator[](std::size_t i) const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;

private:
    int* data_;
    std::size_t size_;
    std::size_t cap_;

    void reserve(std::size_t new_cap);
};

#endif // INCLUDE_DYNAMICARRAY_HPP_

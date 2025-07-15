#include "DynamicArray.hpp"

DynamicArray::DynamicArray(std::size_t cap)
  : data_(new int[cap])
  , size_(0)
  , cap_(cap)
{}

DynamicArray::DynamicArray(const DynamicArray& other)
  : data_(new int[other.cap_])
  , size_(other.size_)
  , cap_(other.cap_)
{
    std::copy(other.data_, other.data_ + size_, data_);
}

DynamicArray::DynamicArray(DynamicArray&& other)
  : data_(std::exchange(other.data_, nullptr))
  , size_(std::exchange(other.size_, 0))
  , cap_(std::exchange(other.cap_, 0))
{}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
    if (this == &other) return *this;

    int* tmp = new int[other.cap_];
    std::copy(other.data_, other.data_ + other.size_, tmp);

    delete[] data_;
    data_ = tmp;
    size_ = other.size_;
    cap_ = other.cap_;

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other)
{
    if (this == &other) return *this;

    delete[] data_;
    data_ = std::exchange(other.data_, nullptr);
    size_ = std::exchange(other.size_, 0);
    cap_ = std::exchange(other.cap_, 0);

    return *this;
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

void DynamicArray::push_back(int v) {
    if (size_ == cap_) {
        reserve(cap_ == 0 ? 1 : cap_ * 2);
    }
    data_[size_++] = v;
}

int& DynamicArray::operator[](std::size_t i) {
    return data_[i];
}

int const& DynamicArray::operator[](std::size_t i) const {
    return data_[i];
}

std::size_t DynamicArray::size() const noexcept {
    return size_;
}

std::size_t DynamicArray::capacity() const noexcept {
    return cap_;
}

void DynamicArray::reserve(std::size_t new_cap) {
    int* tmp = new int[new_cap];
    std::memcpy(tmp, data_, size_ * sizeof(int));
    delete[] data_;
    data_ = tmp;
    cap_ = new_cap;
}

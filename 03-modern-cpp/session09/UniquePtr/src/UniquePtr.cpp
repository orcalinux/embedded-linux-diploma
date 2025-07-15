#include "UniquePtr.hpp"
#include <utility>

UniquePtr::UniquePtr(int* ptr) noexcept
    : ptr_(ptr)
{}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept
    : ptr_(std::exchange(other.ptr_, nullptr))
{}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = std::exchange(other.ptr_, nullptr);
    }
    return *this;
}

UniquePtr::~UniquePtr() {
    delete ptr_;
    ptr_ = nullptr;
}

UniquePtr::operator bool() const noexcept {
    return ptr_ != nullptr;
}

int& UniquePtr::operator*() const {
    return *ptr_;
}

int* UniquePtr::operator->() const noexcept {
    return ptr_;
}

int* UniquePtr::get() const noexcept {
    return ptr_;
}

int* UniquePtr::release() noexcept {
    int* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

void UniquePtr::reset(int* ptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
}

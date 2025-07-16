#include "SharedPtr.hpp"
#include <utility>

SharedPtr::SharedPtr(int* ptr)
  : res_(ptr),
    counter_(new int(1))
{}

SharedPtr::SharedPtr(const SharedPtr& other)
  : res_(other.res_),
    counter_(other.counter_)
{
    increment_count();
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other)
{
    if (this != &other) {
        decrement_count();
        res_     = other.res_;
        counter_ = other.counter_;
        increment_count();
    }
    return *this;
}

SharedPtr::SharedPtr(SharedPtr&& other)
  : res_(std::exchange(other.res_, nullptr)),
    counter_(std::exchange(other.counter_, nullptr))
{}

SharedPtr& SharedPtr::operator=(SharedPtr&& other)
{
    if (this != &other) {
        decrement_count();
        res_     = std::exchange(other.res_, nullptr);
        counter_ = std::exchange(other.counter_, nullptr);
    }
    return *this;
}

SharedPtr::~SharedPtr()
{
    decrement_count();
}

void SharedPtr::reset(int* ptr)
{
    decrement_count();
    res_     = ptr;
    counter_ = new int(1);
}

int* SharedPtr::get() const
{
    return res_;
}

void SharedPtr::set(int val)
{
    if (res_) *res_ = val;
}

int SharedPtr::get_count() const
{
    return counter_ ? *counter_ : -1;
}

int& SharedPtr::operator*() const
{
    return *res_;
}

int* SharedPtr::operator->() const
{
    return res_;
}

SharedPtr::operator bool() const
{
    return res_ != nullptr;
}

void SharedPtr::increment_count()
{
    if (counter_)
        ++(*counter_);
}

void SharedPtr::decrement_count()
{
    if (counter_) {
        --(*counter_);
        if (*counter_ == 0) {
            delete res_;
            delete counter_;
            res_     = nullptr;
            counter_ = nullptr;
        }
    }
}

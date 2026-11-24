#ifndef UNIQUEPTR_HPP
#define UNIQUEPTR_HPP

#include <utility>

class UniquePtr {
public:
    explicit UniquePtr(int* ptr = nullptr) noexcept;
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) noexcept;

    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    ~UniquePtr();

    explicit operator bool() const noexcept;

    // dereference
    int&  operator*()    const;
    int*  operator->()   const noexcept;

    // raw access
    int*  get()          const noexcept;
    int*  release()      noexcept;
    void  reset(int* ptr = nullptr) noexcept;

private:
    int* ptr_ = nullptr;
};

#endif // UNIQUEPTR_HPP

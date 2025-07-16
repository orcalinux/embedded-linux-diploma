#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <utility>

class SharedPtr {
public:
    /// Constructs a SharedPtr owning ptr (or null if no ptr given)
    explicit SharedPtr(int* ptr = nullptr);

    /// Copy ctor: increments shared count
    SharedPtr(const SharedPtr& other);

    /// Copy‑assignment: release current, then copy + increment
    SharedPtr& operator=(const SharedPtr& other);

    /// Move ctor: steals ownership (source reset to null)
    SharedPtr(SharedPtr&& other);

    /// Move‑assignment: release current, then steal (source reset)
    SharedPtr& operator=(SharedPtr&& other);

    /// Destructor: decrements count, deletes when reaching zero
    ~SharedPtr();

    /// Resets to own ptr (releasing old), count starts at 1
    void reset(int* ptr = nullptr);

    /// Returns the raw pointer
    int* get() const;

    /// Overwrites *get() with val
    void set(int val);

    /// Returns current shared‑owner count (or –1 if none)
    int get_count() const;

    /// Dereference operators
    int& operator*() const;
    int* operator->() const;

    /// Allows "if(ptr)" and static_cast<bool>(ptr)
    explicit operator bool() const;

private:
    int* res_;      // the managed pointer
    int* counter_;  // heap‑allocated reference count

    void increment_count();
    void decrement_count();
};

#endif // SHARED_PTR_HPP

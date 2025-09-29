# Smart and Raw Pointers in Modern C++

A concise guide to choosing and using the right pointer type in C++:  
`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, and raw pointers/references.  
Each section includes **when to use**, **when not to use**, and **code examples** for both.

---

## Table of Contents

- [Smart and Raw Pointers in Modern C++](#smart-and-raw-pointers-in-modern-c)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Unique Ownership: `std::unique_ptr`](#unique-ownership-stdunique_ptr)
    - [When to Use](#when-to-use)
    - [When Not to Use](#when-not-to-use)
  - [Shared Ownership: `std::shared_ptr`](#shared-ownership-stdshared_ptr)
    - [When to Use](#when-to-use-1)
    - [When Not to Use](#when-not-to-use-1)
  - [Non‑Owning Observer: `std::weak_ptr`](#nonowning-observer-stdweak_ptr)
    - [When to Use](#when-to-use-2)
    - [When Not to Use](#when-not-to-use-2)
  - [Raw Pointers \& References](#raw-pointers--references)
    - [When to Use](#when-to-use-3)
    - [When Not to Use](#when-not-to-use-3)
  - [Quick Decision Table](#quick-decision-table)
  - [Additional Tips](#additional-tips)

---

## Introduction

Modern C++ gives you **automatic** and **safe** resource management via smart pointers.  
Choosing the wrong pointer can lead to memory leaks, dangling pointers, or performance issues.  
Use this guide to pick the right tool for your ownership and performance needs.

---

## Unique Ownership: `std::unique_ptr`

A move‑only smart pointer that has **exactly one** owner.  
Zero overhead (no atomic ref‑counting).

### When to Use

- You want **sole ownership** of a resource.
- Resource cleanup must happen when the owner goes out of scope.
- No sharing allowed.

```cpp
#include <memory>
#include <iostream>

struct Widget {
    Widget()  { std::cout << "Widget created\n"; }
    ~Widget() { std::cout << "Widget destroyed\n"; }
    void hello() { std::cout << "Hello\n"; }
};

std::unique_ptr<Widget> make_widget() {
    return std::make_unique<Widget>();
}

void consume(std::unique_ptr<Widget> w) {
    w->hello();
    // w destroyed here, Widget cleaned up
}

int main() {
    auto w = make_widget();       // owns the Widget
    consume(std::move(w));        // transfer ownership
    // w is now nullptr
}
```

### When Not to Use

- You need multiple owners.
- You want observers or non‑owning handles.
- You need to pass the same resource to several places.

```cpp
// WRONG: unique_ptr cannot be copied
std::unique_ptr<int> a = std::make_unique<int>(42);
// std::unique_ptr<int> b = a; // compile error!

// WRONG: object must not outlive the unique_ptr
int* raw = new int(5);
std::unique_ptr<int> u(raw);
// delete raw;                 // double delete when u goes out of scope
```

---

## Shared Ownership: `std::shared_ptr`

A reference‑counted pointer. Destroys the object when the last owner goes away.

### When to Use

- Multiple parts of your code need to **share ownership**.
- You cannot define a single clear owner.
- You accept a small cost for atomic ref‑counting.

```cpp
#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;
    Node(int v): value(v) { std::cout << "Node " << value << " created\n"; }
    ~Node() { std::cout << "Node " << value << " destroyed\n"; }
    int value;
};

int main() {
    auto n1 = std::make_shared<Node>(1);
    auto n2 = std::make_shared<Node>(2);
    n1->next = n2;   // share ownership
    n2->next = nullptr;
    // both n1 and n2 alive
}
```

### When Not to Use

- You don’t need shared ownership—prefer `unique_ptr`.
- In tight loops or hot paths (atomic overhead matters).
- You risk **cycles**, causing leaks.

```cpp
// WRONG: cyclic references → memory leak
struct A {
    std::shared_ptr<A> other;
    ~A() { std::cout << "A destroyed\n"; }
};

int main() {
    auto a1 = std::make_shared<A>();
    auto a2 = std::make_shared<A>();
    a1->other = a2;
    a2->other = a1;
    // neither A is destroyed when main exits!
}
```

---

## Non‑Owning Observer: `std::weak_ptr`

A **non‑owning** reference to a `shared_ptr`‑managed object.
Does **not** increment the ref‑count.

### When to Use

- You want to **observe** without extending lifetime.
- You need to **break cycles** of `shared_ptr`.
- You want to check “is it still alive?” with `lock()`.

```cpp
#include <memory>
#include <iostream>

struct Subject {
    void announce() { std::cout << "Subject says hi\n"; }
};

struct Observer {
    std::weak_ptr<Subject> wp;
    void notify() {
        if (auto sp = wp.lock()) {
            sp->announce();
        } else {
            std::cout << "Subject no longer exists\n";
        }
    }
};

int main() {
    Observer obs;
    {
        auto subj = std::make_shared<Subject>();
        obs.wp = subj;  // observe
        obs.notify();   // prints "Subject says hi"
    }
    obs.notify();       // prints "Subject no longer exists"
}
```

### When Not to Use

- You need to **guarantee** the object stays alive for your operation.
- You’re not dealing with a `shared_ptr`‑managed object.
- You want simple high‑performance access (use raw pointers).

```cpp
// WRONG: using weak_ptr when you actually need ownership
void process(std::weak_ptr<Foo> w) {
    // if you need Foo to live through this call,
    // lock() + new shared_ptr<int> adds overhead
}
```

---

## Raw Pointers & References

Non‑owning, no lifetime management. Use only when lifetime is guaranteed externally.

### When to Use

- Interfacing with legacy C APIs.
- You have a guaranteed-lifetime object (stack, global, or `unique_ptr.get()`).
- You want zero overhead.

```cpp
#include <iostream>

void printValue(int* p) {
    if (p) std::cout << *p << "\n";
}

int main() {
    int x = 10;
    printValue(&x);          // safe: x outlives the call
}
```

### When Not to Use

- You need automatic cleanup.
- You need shared or sole ownership semantics.
- You risk dangling pointers when the pointee is deleted elsewhere.

```cpp
int* foo() {
    int* p = new int(5);
    return p;  // caller must delete → easy to leak
}

int main() {
    int* p = foo();
    // forgot to delete → memory leak!
}
```

---

## Quick Decision Table

| Requirement                                              | Pointer Type     |
| -------------------------------------------------------- | ---------------- |
| Single clear owner                                       | `unique_ptr<T>`  |
| Shared ownership                                         | `shared_ptr<T>`  |
| Non‑owning observer; test for liveness                   | `weak_ptr<T>`    |
| Non‑owning; externally guaranteed lifetime (no overhead) | raw `T*` or `T&` |

---

## Additional Tips

1. **Prefer** `std::make_unique` / `std::make_shared`.
2. **Never** mix raw `new`/`delete` with smart pointers.
3. Use `weak_ptr` to break cycles in shared graphs.
4. Document ownership semantics in your APIs.
5. In performance‑critical code, avoid shared ownership unless necessary.

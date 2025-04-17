# Basic Language Facilities - Part 02

This document covers several intermediate C++ topics:

- **Initialization Forms (including Uniform Initialization)**
- **Pointers**
- **References**
- **Reference vs. Pointer**
- **The `const` Qualifier**
- **`const` in Compound Types**
- **Automatic Type Inference (C++11)**

Each topic includes examples at three difficulty levels (Easy, Medium, Hard). At the end of the **Initialization** section, you’ll find a comprehensive snippet that demonstrates many forms of initialization in one place.

---

## 1. Initialization Forms (with Emphasis on Uniform Init, C++11)

In C++, there are multiple ways to initialize variables. **Uniform Initialization** (C++11) uses braces (`{}`) consistently, but you will also see older forms such as **copy initialization** (`=`) and **direct initialization** (`()`).

### (Easy)

```cpp
#include <iostream>

int main() {
    // Basic types
    int x {10};     // Braced (uniform) initialization
    double d {3.14};

    // Print results
    std::cout << "x = " << x << "\n";
    std::cout << "d = " << d << "\n";
    return 0;
}
```

- **Key Points**
  - Braced (`{}`) initialization may prevent _narrowing_ (e.g., `double` → `int`).
  - Equivalent older forms:
    ```cpp
    int x = 10;   // copy init
    int x(10);    // direct init
    int x{10};    // uniform / list init (C++11+)
    ```

### (Medium)

```cpp
#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
};

int main() {
    // Uniform initialization of a struct
    Person p {"Alice", 30};

    std::cout << p.name << " is " << p.age << " years old.\n";
    return 0;
}
```

- **Key Points**
  - Braced initialization also works for structs/classes, setting each member in order.

### (Hard)

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
    int a;
    double b;
    std::vector<int> vec;

    // Constructor with std::initializer_list
    MyClass(int x, double y, std::initializer_list<int> list)
        : a{x}, b{y}, vec(list) {}
};

int main() {
    // Uses MyClass constructor that accepts braced list for vec
    MyClass obj {10, 2.71828, {1, 2, 3, 4}};

    std::cout << "a = " << obj.a << "\n";
    std::cout << "b = " << obj.b << "\n";
    std::cout << "vec[0] = " << obj.vec[0] << "\n";
    return 0;
}
```

- **Key Points**
  - Braced initialization can seamlessly initialize complex members (like `std::vector`).

### Additional Example: Many Forms of Initialization

Below is a snippet (adapted from your screenshot) demonstrating various styles of initialization side by side. Each line shows a typical usage: uninitialized variables, copy vs. direct init, aggregate init, zero/value init, and dynamic allocations with `{}`.

```cpp
#include <string>
#include <iostream>

int main() {
    // Integers
    int a1;         // Uninitialized (contains garbage)
    int a2 = 8;     // Copy initialization
    int a3(5);      // Direct initialization

    // Strings
    std::string s1;          // Default-constructed, empty
    std::string s2("C++");   // Direct initialization

    // Character arrays
    char d1[8];                        // Uninitialized
    char d2[8] = {'\0'};               // First element '\0', rest zero
    char d3[8] = {'a','b','c','d'};    // Aggregate initialization
    char d4[8] = "abcd";               // C-string init (plus '\0' at the end)

    // Braced initialization for ints
    int b1{};       // Value initialization (sets to 0)
    // int b2();     // Most vexing parse if uncommented (declares a function!)
    int b3{5};      // Uniform direct initialization
    int b4 = 0;     // Copy initialization with 0

    // Braced init for char arrays
    char e1[8]{};           // Zero-initialized (all '\0')
    char e2[8]{"Hello"};    // Partial init to "Hello", rest zero

    // Dynamic allocations with braces
    int *p1 = new int{};                // Zero-initialized int on the heap
    char *p2 = new char[8]{};          // Array of 8 chars, zero-initialized
    char *p3 = new char[8]{"Hello"};   // Array of 8 chars with "Hello"

    // Just to suppress warnings about unused variables
    std::cout << a2 << ", " << a3 << ", " << s2 << ", " << d4 << ", "
              << b1 << ", " << b3 << ", " << b4 << ", " << e2 << "\n";

    // Clean up dynamically allocated memory
    delete p1;
    delete[] p2;
    delete[] p3;
    return 0;
}
```

**Key Takeaways**

1. **Uninitialized** variables and arrays contain _indeterminate_ data—using them before assignment is undefined behavior.
2. **Value Initialization** (e.g., `int b1{};`) zeroes out fundamental types and calls default constructors for class types.
3. **Most Vexing Parse** can happen if you write something like `int b2();` inside a function body, which is interpreted as a function prototype, not a variable declaration.
4. Using braces for dynamic allocations (e.g., `new int{}`) performs **value initialization** rather than leaving the data uninitialized.

---

## 2. Pointers

A pointer holds the address of another variable or object; you can dereference the pointer to read or modify that object.

### (Easy)

```cpp
#include <iostream>

int main() {
    int value = 42;
    int* ptr = &value; // ptr points to value

    std::cout << "Address of value: " << &value << "\n";
    std::cout << "ptr stores:       " << ptr << "\n";
    std::cout << "Dereferenced ptr: " << *ptr << "\n";
    return 0;
}
```

- **Key Points**
  - `int* ptr` = “pointer to int.”
  - `&value` is the address of `value`.

### (Medium)

```cpp
#include <iostream>

int main() {
    int x = 5, y = 10;
    int* px = &x;
    int* py = &y;

    // Swap the values pointed to by px and py
    int temp = *px;
    *px = *py;
    *py = temp;

    std::cout << "x = " << x << ", y = " << y << std::endl;
    return 0;
}
```

- **Key Points**
  - Must dereference (`*px`) to get or set the underlying value.

### (Hard)

```cpp
#include <iostream>
#include <cstdlib>  // for std::malloc, std::free

int main() {
    // Allocate array with malloc (C-style)
    int* arr = (int*) std::malloc(5 * sizeof(int));
    if (!arr) {
        std::cerr << "Allocation failed\n";
        return 1;
    }

    // Initialize
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }

    // Print
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // Free memory
    std::free(arr);
    return 0;
}
```

- **Key Points**
  - Manually managing memory is risky; prefer C++-style `new/delete` or smart pointers (`std::unique_ptr`).

---

## 3. References

A reference is an alias to an existing variable. Once created, it must always refer to the same variable.

### (Easy)

```cpp
#include <iostream>

int main() {
    int n = 10;
    int& ref = n; // reference to n

    std::cout << "n:   " << n << "\n";
    std::cout << "ref: " << ref << "\n";

    ref = 20; // modifies n
    std::cout << "n after ref update: " << n << "\n";
    return 0;
}
```

- **Key Points**
  - `int& ref = n;` must bind immediately to `n`.
  - You cannot “rebind” `ref` to a different variable later.

### (Medium)

```cpp
#include <iostream>

// Use a reference parameter to avoid copying
void increment(int &r) {
    ++r;
}

int main() {
    int value = 5;
    increment(value);
    std::cout << "Value after increment: " << value << "\n";
    return 0;
}
```

- **Key Points**
  - References to function parameters avoid copying big objects and can modify them directly.

### (Hard)

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    Person(const std::string &n, int a) : name(n), age(a) {}
};

void printPerson(const Person &p) {
    // const reference avoids copying, prevents modification
    std::cout << p.name << " is " << p.age << " years old.\n";
}

int main() {
    Person person("Alice", 30);
    printPerson(person);
    return 0;
}
```

- **Key Points**
  - `const Person &` is ideal for read-only function parameters (efficiency + safety).

---

## 4. Reference vs. Pointer

Both let you refer to another variable, but with important differences:

| Aspect           | Reference            | Pointer                      |
| ---------------- | -------------------- | ---------------------------- |
| Declaration      | `int &r = variable;` | `int *p = &variable;`        |
| Rebind Ability   | Cannot be changed    | Can change what it points to |
| Must Initialize  | Yes (immediately)    | No (can be assigned later)   |
| Dereferencing    | Implicit             | Use `*p` to dereference      |
| Null possibility | Cannot be null       | Can be null or invalid       |

### (Easy)

```cpp
#include <iostream>

int main() {
    int x = 10;

    // Reference
    int& r = x;
    // Pointer
    int* p = &x;

    std::cout << "r (reference): " << r << "\n";
    std::cout << "*p (pointer):  " << *p << "\n";
    return 0;
}
```

### (Medium)

```cpp
#include <iostream>

void showPointer(int *ptr) {
    if (!ptr) {
        std::cout << "Pointer is null.\n";
        return;
    }
    std::cout << "Pointer value: " << *ptr << "\n";
}

void showReference(int &ref) {
    // Always valid, no need for a null check
    std::cout << "Reference value: " << ref << "\n";
}

int main() {
    int y = 100;
    int* nullPtr = nullptr;
    int* validPtr = &y;
    int &myRef = y;

    showPointer(nullPtr);   // Must check or it may crash
    showPointer(validPtr);
    showReference(myRef);
    return 0;
}
```

### (Hard)

```cpp
#include <iostream>

int main() {
    int a = 10, b = 20;

    // Swap via pointer
    {
        int *pa = &a, *pb = &b;
        int temp = *pa;
        *pa = *pb;
        *pb = temp;
    }

    // Swap via reference
    auto swapRef = [](int &x, int &y) {
        int tmp = x;
        x = y;
        y = tmp;
    };
    swapRef(a, b);

    std::cout << "a = " << a << ", b = " << b << std::endl;
    return 0;
}
```

- **Key Points**
  - References simplify usage (no `*` in repeated expressions).
  - Pointers offer more flexibility (can be null or reassigned).

---

## 5. The `const` Qualifier

`const` prevents modifications of a variable through that name. Also applies to pointers and references.

### (Easy)

```cpp
#include <iostream>

int main() {
    const int FIXED_VALUE = 100;
    // FIXED_VALUE = 200;  // Error

    std::cout << "Fixed value: " << FIXED_VALUE << "\n";
    return 0;
}
```

### (Medium)

```cpp
#include <iostream>

void printArray(const int arr[], int size) {
    // arr can't be modified here
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int data[5] = {1, 2, 3, 4, 5};
    printArray(data, 5);
    return 0;
}
```

### (Hard)

```cpp
#include <iostream>

int main() {
    int x = 10;

    // Pointer to const int: cannot modify what it points to
    const int* ptrToConst = &x;
    // *ptrToConst = 20; // Error

    // Const pointer to non-const int: cannot change the pointer itself
    int* const constPtr = &x;
    *constPtr = 20;   // OK, x is not const
    // constPtr = nullptr; // Error

    // Const pointer to const int
    const int y = 30;
    const int* const cPtrToC = &y;
    // *cPtrToC = 40;  // Error
    // cPtrToC = nullptr;  // Error

    std::cout << "x = " << x << ", y = " << y << "\n";
    return 0;
}
```

- **Key Points**
  - `const` can apply to data or to the pointer itself:
    - `const int*` → the `int` is const.
    - `int* const` → the pointer is const.
    - `const int* const` → both.

---

## 6. `const` in Compound Types

Combining `const` with references, pointers-to-pointers, or arrays can be tricky. The placement of `const` matters.

### (Easy)

```cpp
#include <iostream>

int main() {
    int val = 10;
    int& r = val;        // normal reference
    const int& cr = val; // const reference

    r = 20;  // OK, modifies val
    // cr = 30; // Error, can't modify via cr

    std::cout << "val = " << val << "\n"; // prints 20
    return 0;
}
```

### (Medium)

```cpp
#include <iostream>

void printElements(const int* arr, int size) {
    // "arr" is pointer-to-const int
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int data[3] = {1, 2, 3};

    printElements(data, 3);
    printElements(&data[1], 2);

    return 0;
}
```

### (Hard)

```cpp
#include <iostream>

int main() {
    int x = 5;
    int *ptr = &x;
    int **pptr = &ptr;   // pointer to pointer to int

    const int * const * ppc;
    // ppc is a pointer to (const int*):
    // i.e., ppc points to a pointer that points to a const int

    const int ci = 100;
    const int *cptr = &ci;
    ppc = &cptr; // now ppc points to cptr, which points to ci

    // *ppc is cptr (a pointer to const int)
    // **ppc = 200;  // Error: cannot modify ci

    std::cout << "ci = " << ci << "\n";
    return 0;
}
```

- **Key Points**
  - Always parse complicated declarations carefully.
  - “Right-to-left rule” can help: read from the variable name outward.

---

## 7. Automatic Type Inference (C++11)

C++11 introduced `auto`, which deduces the type from the initializer. This reduces verbosity, especially with templates or iterators.

### (Easy)

```cpp
#include <iostream>

int main() {
    auto a = 42;       // a is int
    auto d = 3.14;     // d is double
    auto s = "Hello";  // s is const char*

    std::cout << a << " " << d << " " << s << "\n";
    return 0;
}
```

### (Medium)

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values {1, 2, 3, 4, 5};

    // Range-based for loop with auto
    for (auto val : values) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Using auto for iterators
    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}
```

### (Hard)

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> myMap {
        {"alice", 10},
        {"bob",   20},
        {"eve",   30}
    };

    // Using structured bindings (C++17+) with auto
    for (const auto& [key, value] : myMap) {
        std::cout << key << " -> " << value << "\n";
    }

    return 0;
}
```

- **Key Points**
  - In pure C++11, you’d write:
    ```cpp
    for (const auto &pair : myMap) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }
    ```
  - `auto` also helps with lambda expressions, template-heavy code, etc.

---

## Final Notes

1. **Initialization**:

   - Prefer braced initialization (`{}`) to unify style and avoid narrowing.
   - Watch out for the **most vexing parse** with syntax like `int b2();`.

2. **Pointers & References**:

   - Pointers can be null or reassigned; references cannot.
   - Use references for simpler code when you know an object must exist.

3. **`const`**:

   - Mark data as read-only to avoid accidental changes.
   - Distinguish between `const` data vs. a `const` pointer.

4. **Type Inference** (`auto`):
   - Reduces repetition in variable declarations.
   - Always ensure the initializer is unambiguous (e.g., no overloaded function calls).

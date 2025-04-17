# Basic Language Facilities – Part 04

This document extends the exploration of C++'s core features and covers:

- **Inline Functions**
- **Function Pointers**
- **Namespace**

Each topic is broken into examples of increasing difficulty—from basic introductions to more advanced usage scenarios.

---

## Inline Functions

Inline functions signal to the compiler that the function’s code can be expanded at the call site. This may reduce function call overhead, especially for small functions.

### Example 1 (Easy): Basic Inline Function

```cpp
#include <iostream>

inline int multiply(int x, int y) {
    return x * y;
}

int main() {
    std::cout << "Multiply 3 and 4: " << multiply(3, 4) << std::endl;
    return 0;
}
```

**Key Points:**

- The `inline` keyword suggests substitution of the function body at the call site.
- Best suited for small, simple functions.

---

### Example 2 (Medium): Multi-Line Inline Function

```cpp
#include <iostream>

inline double calculateAverage(double a, double b, double c) {
    double sum = a + b + c;
    return sum / 3.0;
}

int main() {
    std::cout << "Average of 3, 4, 5: " << calculateAverage(3, 4, 5) << std::endl;
    return 0;
}
```

**Key Points:**

- Even functions with multiple lines can be declared as inline.
- The function maintains clarity while potentially eliminating call overhead.

---

### Example 3 (Hard): Inline Function Template

```cpp
#include <iostream>

template <typename T>
inline T maxValue(const T &x, const T &y) {
    return (x > y) ? x : y;
}

int main() {
    std::cout << "Max of 10 and 20: " << maxValue(10, 20) << std::endl;
    std::cout << "Max of 3.14 and 2.71: " << maxValue(3.14, 2.71) << std::endl;
    return 0;
}
```

**Key Points:**

- Combines inline with templates for generic programming.
- The function can be inlined for various data types while keeping code concise.

---

## Function Pointers

Function pointers store the address of a function and allow indirect invocation. They are useful in scenarios like callbacks and dynamic function selection.

### Example 1 (Easy): Basic Function Pointer Usage

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    // Declare a function pointer that takes two ints and returns an int.
    int (*funcPtr)(int, int) = add;
    std::cout << "Result of add(5, 3): " << funcPtr(5, 3) << std::endl;
    return 0;
}
```

**Key Points:**

- The function pointer `funcPtr` is assigned the address of `add`.
- It is then used to call the function indirectly.

---

### Example 2 (Medium): Passing Function Pointers as Arguments

```cpp
#include <iostream>

void executeOperation(int a, int b, int (*operation)(int, int)) {
    std::cout << "Result: " << operation(a, b) << std::endl;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    executeOperation(10, 4, subtract);
    return 0;
}
```

**Key Points:**

- Function pointers can be passed as arguments to other functions.
- This facilitates dynamic selection of operations (in this case, subtraction).

---

### Example 3 (Hard): Array of Function Pointers

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Create an array of function pointers with the same signature.
    int (*operations[3])(int, int) = { add, subtract, multiply };
    int a = 15, b = 5;

    std::cout << "Addition: " << operations[0](a, b) << std::endl;
    std::cout << "Subtraction: " << operations[1](a, b) << std::endl;
    std::cout << "Multiplication: " << operations[2](a, b) << std::endl;

    return 0;
}
```

**Key Points:**

- Function pointers can be stored in arrays for dynamic selection.
- This approach allows you to choose an operation at runtime based on array indexing.

---

## Namespace

Namespaces are used to organize code and prevent name collisions, which is especially useful in larger projects or when integrating multiple libraries.

### Example 1 (Easy): Basic Namespace Usage

```cpp
#include <iostream>

namespace Math {
    int add(int a, int b) {
        return a + b;
    }
}

int main() {
    // Use the qualified name to call the function within the Math namespace.
    std::cout << "Sum: " << Math::add(3, 7) << std::endl;
    return 0;
}
```

**Key Points:**

- The `Math` namespace encapsulates the `add` function.
- Prevents naming conflicts with functions in other parts of the program.

---

### Example 2 (Medium): Nested Namespaces and Using Declarations

```cpp
#include <iostream>

namespace Outer {
    namespace Inner {
        void greet() {
            std::cout << "Hello from the Inner Namespace!" << std::endl;
        }
    }
}

int main() {
    // Call using the fully qualified name.
    Outer::Inner::greet();

    // Creating a namespace alias for convenience.
    namespace In = Outer::Inner;
    In::greet();

    return 0;
}
```

**Key Points:**

- Demonstrates nested namespaces (`Outer::Inner`).
- Uses a namespace alias (`In`) to simplify access to deeply nested names.

---

### Example 3 (Hard): Inline Namespaces for Versioning

```cpp
#include <iostream>

namespace Library {
    inline namespace v1 {
        void display() {
            std::cout << "Library version 1" << std::endl;
        }
    }

    namespace v2 {
        void display() {
            std::cout << "Library version 2" << std::endl;
        }
    }
}

int main() {
    // Calls the inline namespace version (v1) by default.
    Library::display();

    // Explicitly call the version 2 function.
    Library::v2::display();

    return 0;
}
```

**Key Points:**

- Inline namespaces allow a versioned interface where one version is the default.
- Consumers of the library can use the inline namespace without specifying the version, while still having access to other versions if needed.

---

## Final Notes

1. **Inline Functions:**

   - Best applied for small, frequently called routines.
   - Can be combined with templates to create highly reusable, efficient code.

2. **Function Pointers:**

   - Enable dynamic function selection and callback mechanisms.
   - Improve modularity and flexibility in your program design.

3. **Namespace:**
   - Essential for organizing code and preventing name collisions.
   - Nested and inline namespaces offer advanced techniques for managing large code bases and library versioning.

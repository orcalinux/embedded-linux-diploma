# Basic Language Facilities - Part 01

This document covers four fundamental topics in C++:

1. **Primitive Types & Variables**
2. **Basic Input/Output**
3. **Functions Basics Part I**
4. **Functions Basics Part II**

Each section includes multiple example programs, starting with simpler code and progressing to more complex usage.

---

## Primitive Types & Variables

C++ provides several **primitive data types**:

- `int`, `long`, `long long`, `unsigned` variations for integral types
- `char`, `wchar_t`, `char16_t`, `char32_t` for character types
- `bool` for Boolean logic
- `float`, `double`, `long double` for floating-point
- plus various type modifiers like `signed`, `unsigned`, and `const`

Variables can be **declared** and **initialized** in a variety of ways (copy init `=`, direct init `()`, or uniform init `{}`).

### Example 1 (Easy): Basic Declarations

```cpp
#include <iostream>

int main() {
    int age = 20;
    double pi = 3.14159;
    char initial = 'A';
    bool isValid = true;

    std::cout << "Age: " << age << std::endl;
    std::cout << "PI: " << pi << std::endl;
    std::cout << "Initial: " << initial << std::endl;
    std::cout << "Is valid: " << isValid << std::endl;

    return 0;
}
```

- **Key Points**
  - Declares basic types (`int`, `double`, `char`, `bool`) and prints them out.
  - `std::endl` flushes the output buffer, whereas `"\n"` just inserts a newline.

---

### Example 2 (Medium): Mixing Types

```cpp
#include <iostream>

int main() {
    int a = 5;
    int b = 2;
    double result = a / b; // Watch out for integer division!

    std::cout << "Integer division (a/b) stored in double: " << result << std::endl;

    // To fix integer division issue, cast one operand:
    double correctResult = static_cast<double>(a) / b;
    std::cout << "Using cast for true division: " << correctResult << std::endl;

    return 0;
}
```

- **Key Points**
  - `a / b` is integer division (5 / 2 → 2).
  - Casting `a` to `double` forces floating-point division (2.5).

---

### Example 3 (Harder): Manipulating `unsigned` and Overflow

```cpp
#include <iostream>
#include <limits>

int main() {
    // Maximum value for a 32-bit unsigned int
    unsigned int maxVal = std::numeric_limits<unsigned int>::max();
    std::cout << "Max unsigned int: " << maxVal << std::endl;

    // Overflow occurs if we add 1
    unsigned int overflowed = maxVal + 1;
    std::cout << "Max unsigned int + 1 = " << overflowed << std::endl;

    // Negative values stored in unsigned can wrap around as well
    overflowed = static_cast<unsigned int>(-1);
    std::cout << "Assigning -1 to unsigned = " << overflowed << std::endl;

    return 0;
}
```

- **Key Points**
  - Demonstrates overflow behavior with `unsigned int`.
  - `<limits>` helps find numeric bounds.

---

### Example 4 (Advanced): Scope and Shadowing

```cpp
#include <iostream>

int main() {
    int x = 10;
    {
        std::cout << "Outer x = " << x << "\n";
        int x = 20; // Shadows outer x in this block
        std::cout << "Inner x = " << x << "\n";
    }
    std::cout << "Back to outer x = " << x << "\n";
    return 0;
}
```

- **Key Points**
  - Variables declared in an inner scope **shadow** (hide) variables of the same name in an outer scope.
  - After the block ends, the shadowed variable is visible again.

---

### Example 5 (Advanced): Using `auto` with Primitives (C++11+)

```cpp
#include <iostream>

int main() {
    auto count = 42;        // deduces 'int'
    auto price = 9.99;      // deduces 'double'
    auto letter = 'Z';      // deduces 'char'
    auto isReady = true;    // deduces 'bool'

    std::cout << count << " " << price << " "
              << letter << " " << isReady << "\n";
    return 0;
}
```

- **Key Points**
  - `auto` can simplify declarations but must have an initializer.
  - For more on `auto`, see “Automatic Type Inference” in advanced references.

---

## Basic Input/Output

C++ uses `<iostream>` for console I/O via:

- `std::cout` (standard output)
- `std::cin` (standard input)
- `std::cerr` (standard error)
- `std::endl` (newline + flush)
- `"\n"` (newline without flush)

### Example 1 (Easy): Reading an Integer and Printing It

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter an integer: ";
    std::cin >> number;
    std::cout << "You entered: " << number << std::endl;
    return 0;
}
```

- **Key Points**
  - `std::cin >> var` reads from user input.
  - Always check for input failures in robust code (e.g., invalid type entered).

---

### Example 2 (Medium): Summing Two Numbers

```cpp
#include <iostream>

int main() {
    int x, y;
    std::cout << "Enter two integers: ";
    std::cin >> x >> y;

    int sum = x + y;
    std::cout << x << " + " << y << " = " << sum << std::endl;

    return 0;
}
```

- **Key Points**
  - Multiple reads: `std::cin >> x >> y;`
  - Basic arithmetic with user-provided values.

---

### Example 3 (Harder): Reading a Whole Line of Text

```cpp
#include <iostream>
#include <string>

int main() {
    std::string line;
    std::cout << "Type a full sentence (including spaces):" << std::endl;

    // std::getline reads an entire line, including spaces, until newline
    std::getline(std::cin, line);

    std::cout << "You wrote: " << line << std::endl;
    return 0;
}
```

- **Key Points**
  - `std::getline` captures all text up to `\n`.
  - If mixing `std::cin >> var` and `std::getline`, watch for leftover newline in the buffer.

---

### Example 4 (Advanced): Reading Until Sentinel

```cpp
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cout << "Enter lines (type 'quit' to stop):\n";

    while (true) {
        std::getline(std::cin, input);
        if (input == "quit") {
            break;
        }
        std::cout << "You entered: " << input << std::endl;
    }
    return 0;
}
```

- **Key Points**
  - Allows indefinite input.
  - Checking for a sentinel value (`"quit"`) to exit the loop.

---

### Example 5 (Advanced): Formatted Output with `<iomanip>`

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double val1 = 3.14159;
    double val2 = 2000.56789;

    // Set precision and formatting
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "val1: " << val1 << "\n";
    std::cout << "val2: " << val2 << "\n";

    // Right alignment, width 10
    std::cout << std::setw(10) << val1 << std::endl;
    std::cout << std::setw(10) << val2 << std::endl;

    return 0;
}
```

- **Key Points**
  - `<iomanip>` provides manipulators such as `std::setprecision`, `std::setw`.
  - Useful for tables, currency formats, etc.

---

## Functions Basics Part I

**Functions** let you break programs into reusable blocks. They can return values (e.g., `int`, `double`, `std::string`) or `void` if no value is returned.

### Example 1 (Easy): Simple Function with Return

```cpp
#include <iostream>

// A function that returns the sum of two integers
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 4);
    std::cout << "3 + 4 = " << result << std::endl;
    return 0;
}
```

- **Key Points**
  - Define the function before or after `main()`, but if after, you need a **forward declaration**.
  - Return type must match what you actually return (here, `int`).

---

### Example 2 (Medium): Pass-by-Reference

```cpp
#include <iostream>

// Swap two integers using references
void swapIntegers(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 10, b = 20;
    std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
    swapIntegers(a, b);
    std::cout << "After swap:  a=" << a << ", b=" << b << std::endl;
    return 0;
}
```

- **Key Points**
  - `int &x` denotes a reference parameter: changes affect the original variable.
  - No need to `return` anything for a swap, since the parameters themselves are modified.

---

### Example 3 (Harder): Recursion

```cpp
#include <iostream>

// Compute factorial recursively
unsigned long long factorial(unsigned long long n) {
    if (n <= 1) {
        return 1ULL;
    }
    return n * factorial(n - 1);
}

int main() {
    std::cout << "Factorial of 5 = " << factorial(5) << std::endl;
    // 5! = 120
    return 0;
}
```

- **Key Points**
  - A function that calls itself until a **base case** is reached.
  - Use a larger type (`unsigned long long`) for bigger factorials.

---

### Example 4 (Advanced): Multiple Return Values via Struct

```cpp
#include <iostream>
#include <string>

struct FullName {
    std::string first;
    std::string last;
};

// Return multiple strings in a struct
FullName parseName(const std::string &full) {
    FullName result;
    // Just a simple example splitting on space
    size_t pos = full.find(' ');
    if (pos != std::string::npos) {
        result.first = full.substr(0, pos);
        result.last  = full.substr(pos + 1);
    } else {
        // If no space, treat entire input as first name
        result.first = full;
    }
    return result;
}

int main() {
    FullName name = parseName("John Doe");
    std::cout << "First: " << name.first << ", Last: " << name.last << std::endl;
    return 0;
}
```

- **Key Points**
  - You can bundle multiple values in a struct/class to “return more than one thing.”
  - Another approach: pass by reference to output parameters.

---

### Example 5 (Advanced): Variadic Functions (C++11+)

```cpp
#include <iostream>
#include <cstdarg> // for C-style variadic or use <initializer_list> in C++

// Simple example with old-style variadic function
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int main() {
    std::cout << "Sum of 3,4,5 = " << sum(3, 3, 4, 5) << std::endl;
    return 0;
}
```

- **Key Points**
  - **C-style** variadic functions can be risky (type safety issues).
  - Prefer modern C++ approaches: e.g., parameter packs in **templates** or `std::initializer_list`.

---

## Functions Basics Part II

We expand on advanced function concepts such as **overloading**, **default parameters**, **inline**, and more.

### Example 1 (Easy): Function Overloading

```cpp
#include <iostream>

// Overloaded function "printData"
void printData(int value) {
    std::cout << "Integer: " << value << std::endl;
}
void printData(double value) {
    std::cout << "Double: " << value << std::endl;
}
void printData(const std::string &value) {
    std::cout << "String: " << value << std::endl;
}

int main() {
    printData(42);
    printData(3.14);
    printData("Hello Overload");
    return 0;
}
```

- **Key Points**
  - Same function name, different parameter types.
  - Compiler picks the right overload based on the argument’s type.

---

### Example 2 (Medium): Default Parameters

```cpp
#include <iostream>

// Default parameter for name
void greet(const std::string &name = "World") {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    greet();           // Uses default: "World"
    greet("Alice");    // Uses explicit value
    return 0;
}
```

- **Key Points**
  - If no argument is provided, "World" is used.
  - Default parameters must be specified in a single place (declaration or definition).

---

### Example 3 (Harder): Inline Functions & Performance Hint

```cpp
#include <iostream>

// 'inline' suggests (not guarantees) that the compiler
// might expand the function body inline to reduce call overhead
inline int multiply(int x, int y) {
    return x * y;
}

int main() {
    int a = 5, b = 6;
    std::cout << "Multiply inline: " << multiply(a, b) << std::endl;
    return 0;
}
```

- **Key Points**
  - Compiler may or may not inline, depending on optimization.
  - Best used for small, frequently called functions.

---

### Example 4 (Advanced): Overloading + Default Params

```cpp
#include <iostream>

void showInfo(int x, int y = 100) {
    std::cout << "Two ints: " << x << " and " << y << "\n";
}
void showInfo(const std::string &s, int repeat = 1) {
    for (int i = 0; i < repeat; ++i) {
        std::cout << "String: " << s << "\n";
    }
}

int main() {
    showInfo(42);           // calls showInfo(int, int=100)
    showInfo(42, 999);      // calls showInfo(int, int)
    showInfo("Hello");      // calls showInfo(string, int=1)
    showInfo("World", 3);   // calls showInfo(string, int)
    return 0;
}
```

- **Key Points**
  - Example of multiple overloads, each with its own default parameter.
  - The compiler chooses based on the argument types.

---

### Example 5 (Advanced): `constexpr` Functions (C++11+)

```cpp
#include <iostream>

// A constexpr function can be evaluated at compile-time if given constant arguments
constexpr int square(int x) {
    return x * x;
}

int main() {
    // This is evaluated at compile time
    constexpr int val = square(5);

    // Can also call at runtime with variables
    int n;
    std::cin >> n;
    std::cout << "Square of " << n << " is " << square(n) << std::endl;

    std::cout << "Square of 5 (compile-time): " << val << std::endl;
    return 0;
}
```

- **Key Points**
  - `constexpr` indicates the function may produce a compile-time constant if inputs are constants.
  - Great for optimizing constant expressions and arrays.

---

## Summary

1. **Primitive Types & Variables**

   - Integral, floating-point, Boolean, character types; declarations and scope.

2. **Basic Input/Output**

   - Reading/writing data via `std::cin`, `std::cout`, and formatting tools (`<iomanip>`).

3. **Functions Basics Part I**

   - Defining/using functions with return values, reference parameters, recursion.

4. **Functions Basics Part II**
   - Overloading, default parameters, `inline`/`constexpr`, and more advanced function techniques.

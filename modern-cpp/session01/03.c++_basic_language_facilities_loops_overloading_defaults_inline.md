# Basic Language Facilities – Part 03

This section covers several more core C++ features with clear, progressively challenging examples. The topics include:

- **Range-Based For Loop I (C++11)**
- **Range-Based For Loop II (C++11)**
- **Function Overloading**
- **Default Function Arguments**
- **Inline Functions**

Each subtopic provides examples from simple to advanced, reinforcing both the syntax and subtle behaviors of the language.

---

## Range-Based For Loop I (C++11)

Range-based for loops, introduced in C++11, simplify iterating over containers by abstracting away the iterator details. Here are three examples:

### Example 1 (Easy): Iterating Over an Array

```cpp
#include <iostream>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};

    // Iterate over array elements
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**Key Points:**

- Iterates directly over each element in the `numbers` array.
- No explicit indexing or iterator declarations are needed.

---

### Example 2 (Medium): Iterating Over a Vector of Strings

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};

    // Loop through each element using range-based for
    for (const std::string &fruit : fruits) {
        std::cout << fruit << "\n";
    }
    return 0;
}
```

**Key Points:**

- Uses a constant reference (`const std::string &`) to avoid copying.
- Works with STL containers like `std::vector`.

---

### Example 3 (Hard): Nested Range-Based For Loops for a 2D Container

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Outer loop for each row and inner loop for each element in the row
    for (const auto &row : matrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
```

**Key Points:**

- Demonstrates the use of nested range-based for loops.
- The outer loop iterates over rows (each row is a vector), and the inner loop iterates over individual elements.
- Using `auto` simplifies the code when the container type is verbose.

---

## Range-Based For Loop II (C++11)

This section digs deeper into range-based for loops to show modifications of elements and control of iteration behavior.

### Example 1 (Easy): Modifying Elements in a Vector

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums = {10, 20, 30, 40};

    // Use non-const reference to modify each element
    for (int &n : nums) {
        n += 5;
    }

    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**Key Points:**

- Iterates by reference (`int &n`) to modify the container’s elements.
- Each element is increased by 5.

---

### Example 2 (Medium): Iterating Over an Initializer List

```cpp
#include <iostream>
#include <initializer_list>

int main() {
    // Directly iterate over an initializer list
    for (auto n : {100, 200, 300, 400}) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    return 0;
}
```

**Key Points:**

- Range-based for loops work directly with initializer lists.
- The `auto` keyword lets the compiler deduce the element type.

---

### Example 3 (Hard): Mixing Constant and Modifiable Iteration

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};

    // First, iterate by const reference to only read values
    std::cout << "Original values:\n";
    for (const auto &v : values) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Then, modify the elements using a non-const reference
    for (auto &v : values) {
        v *= 2;
    }

    // Finally, iterate by value to confirm the change
    std::cout << "Doubled values:\n";
    for (auto v : values) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    return 0;
}
```

**Key Points:**

- Shows the difference between reading (using `const auto&`) and modifying (using `auto&`) elements.
- Verifies that the changes persist by printing the modified elements.

---

## Function Overloading

Function overloading enables using the same function name with different parameter types or counts. Here are examples with increasing complexity:

### Example 1 (Easy): Overloading with Different Parameter Types

```cpp
#include <iostream>

void display(int value) {
    std::cout << "Integer: " << value << "\n";
}

void display(double value) {
    std::cout << "Double: " << value << "\n";
}

int main() {
    display(100);
    display(3.14);
    return 0;
}
```

**Key Points:**

- Two functions named `display` handle different data types (int and double).
- The compiler selects the appropriate function based on argument type.

---

### Example 2 (Medium): Overloading with Pass-by-Reference and Const

```cpp
#include <iostream>
#include <string>

void printInfo(const std::string &info) {
    std::cout << "String Info: " << info << "\n";
}

void printInfo(int value) {
    std::cout << "Integer Info: " << value << "\n";
}

int main() {
    std::string text = "Hello";
    int number = 42;
    printInfo(text);
    printInfo(number);
    return 0;
}
```

**Key Points:**

- One overload accepts a constant reference to avoid copying for strings.
- Another overload is defined for integer values.
- This demonstrates overloading with different parameter types including references.

---

### Example 3 (Hard): Overloading with Ambiguity Resolution

```cpp
#include <iostream>

// Overload for int
void process(int value) {
    std::cout << "Processing int: " << value << "\n";
}

// Overload for long
void process(long value) {
    std::cout << "Processing long: " << value << "\n";
}

// Overload for double
void process(double value) {
    std::cout << "Processing double: " << value << "\n";
}

int main() {
    process(10);        // Calls process(int)
    process(10L);       // Calls process(long)
    process(10.0);      // Calls process(double)

    // To resolve ambiguity when implicit conversions might occur,
    // you can cast or use a literal suffix.
    process(static_cast<long>(20)); // Explicit call to process(long)

    return 0;
}
```

**Key Points:**

- Multiple overloaded functions are provided for different numeric types.
- Using explicit casts or literal suffixes (like `L` for long) avoids ambiguity.
- Demonstrates careful design for disambiguation in overloaded functions.

---

## Default Function Arguments

Default function arguments allow you to define a default value for parameters. If an argument is omitted in a call, the default is used.

### Example 1 (Easy): Simple Default Argument

```cpp
#include <iostream>

void greet(const std::string &name = "World") {
    std::cout << "Hello, " << name << "!\n";
}

int main() {
    greet();          // Uses default: "World"
    greet("Alice");   // Uses provided value: "Alice"
    return 0;
}
```

**Key Points:**

- If no argument is passed, the default value ("World") is used.
- Default arguments simplify function calls when many calls use the same values.

---

### Example 2 (Medium): Default Arguments in Multiple Parameters

```cpp
#include <iostream>

void showMessage(const std::string &msg, int repeat = 1) {
    for (int i = 0; i < repeat; ++i) {
        std::cout << msg << "\n";
    }
}

int main() {
    showMessage("Hello");          // Prints message once
    showMessage("Hello", 3);       // Prints message three times
    return 0;
}
```

**Key Points:**

- The second parameter has a default value.
- Allows calls with one or two arguments while keeping the function flexible.

---

### Example 3 (Hard): Default Arguments with Expressions and Overloads

```cpp
#include <iostream>

void computeSum(int a, int b = 10, int c = a + b) {
    // Note: Default arguments are evaluated at the call site.
    std::cout << "Sum: " << (a + b + c) << "\n";
}

int main() {
    // When calling with only one argument, 'b' defaults to 10 and 'c' defaults to a+b.
    computeSum(5);           // a=5, b=10, c becomes 15 → Total = 5+10+15 = 30

    // Overriding the default for b only
    computeSum(5, 20);       // a=5, b=20, c becomes 25 → Total = 5+20+25 = 50

    // Overriding defaults for both b and c
    computeSum(5, 20, 30);   // Total = 5+20+30 = 55
    return 0;
}
```

**Key Points:**

- Demonstrates default arguments with expression dependencies.
- The default value for parameter `c` depends on `a` and `b`.  
  _(Note: Such dependencies in default arguments require care in C++—the evaluation occurs during the call.)_
- Overriding defaults is possible when necessary.

---

## Inline Functions

Inline functions suggest to the compiler that the function’s code be inserted at each call site. They are typically used for small, frequently called functions.

### Example 1 (Easy): Basic Inline Function

```cpp
#include <iostream>

inline int add(int x, int y) {
    return x + y;
}

int main() {
    std::cout << "Sum: " << add(3, 4) << "\n";
    return 0;
}
```

**Key Points:**

- The `inline` keyword suggests function substitution at compile time.
- Used here for a simple addition function.

---

### Example 2 (Medium): Multi-Line Inline Function

```cpp
#include <iostream>

inline double computeDiscount(double price, double discountRate) {
    // Inline functions may have multiple lines
    double discount = price * discountRate;
    return price - discount;
}

int main() {
    double price = 100.0;
    double rate = 0.15; // 15% discount
    std::cout << "Discounted price: " << computeDiscount(price, rate) << "\n";
    return 0;
}
```

**Key Points:**

- Shows that inline functions can include more logic while remaining candidates for inlining.
- Provides a simple calculation demonstrating inline behavior.

---

### Example 3 (Hard): Inline Function Template

```cpp
#include <iostream>

// Inline function template to return the maximum of two values
template <typename T>
inline T maximum(const T &a, const T &b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << "Max of 10 and 20: " << maximum(10, 20) << "\n";
    std::cout << "Max of 3.14 and 2.71: " << maximum(3.14, 2.71) << "\n";
    return 0;
}
```

**Key Points:**

- Combines inline functions with templates.
- The `maximum` template is defined inline, permitting inlining on a variety of data types.
- Shows how inline functions can be generic.

---

## Final Notes

1. **Range-Based For Loops:**

   - Simplify iteration over any container or initializer list.
   - Use references when you need to modify elements; use const references for read-only access.

2. **Function Overloading and Default Arguments:**

   - Overloading gives different implementations for different parameter types.
   - Default arguments reduce redundancy in function calls and offer flexibility—be cautious with dependencies.

3. **Inline Functions:**
   - Best suited for small and frequently called functions.
   - Modern compilers optimize inlining automatically, but the keyword still provides useful hints.

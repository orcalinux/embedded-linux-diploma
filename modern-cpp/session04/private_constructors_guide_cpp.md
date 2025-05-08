# Private Constructors in C++: Why & How

This README shows why you’d make a constructor `private` and three simple patterns—without any smart pointers, using only raw pointers or value returns for clarity.

---

## Table of Contents

- [Private Constructors in C++: Why \& How](#private-constructors-in-c-why--how)
  - [Table of Contents](#table-of-contents)
  - [Why Private Constructors?](#why-private-constructors)
  - [Use Cases](#use-cases)
    - [Singleton Pattern](#singleton-pattern)
    - [Static Factory Methods](#static-factory-methods)
    - [Utility Class (Non-Instantiable)](#utility-class-non-instantiable)
    - [Friend-Only Creation](#friend-only-creation)

---

## Why Private Constructors?

Making a constructor `private` prevents client code from doing `new MyClass()` or stack-allocating it directly. You force everyone to use your controlled creation API—factories, singletons, or friends—so you can enforce invariants, manage lifetime, or hide implementation details.

---

## Use Cases

### Singleton Pattern

Guarantee exactly one instance:

```cpp
#include <iostream>

class Logger {
private:
    Logger() { std::cout << "Logger created\n"; }
    ~Logger() { std::cout << "Logger destroyed\n"; }

    // no copies
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& instance() {
        static Logger inst;  // created once on first call
        return inst;
    }

    void log(const char* msg) {
        std::cout << "[LOG] " << msg << "\n";
    }
};

int main() {
    // Logger lg;               // ERROR: ctor is private
    Logger::instance().log("Hello");
}
```

- **Private ctor** + **static method** → only one `Logger`.

---

### Static Factory Methods

Hide actual types or enforce validation:

```cpp
#include <iostream>

class Shape {
public:
    void draw() const { std::cout << "Drawing shape\n"; }

    // public factory functions
    static Shape makeCircle(double r) {
        // could validate r > 0 here
        return Shape(r, 0);
    }
    static Shape makeSquare(double side) {
        return Shape(0, side);
    }

private:
    // private constructors
    Shape(double radius, double /*unused*/)
      : radius(radius), width(0), height(0) {}
    Shape(double /*unused*/, double side)
      : radius(0), width(side), height(side) {}

    double radius;
    double width, height;
};

int main() {
    Shape c = Shape::makeCircle(3.0);
    Shape s = Shape::makeSquare(5.0);
    c.draw();
    s.draw();
}
```

- Clients call `Shape::makeCircle` or `makeSquare`; they can’t call `Shape(…)` directly.

---

### Utility Class (Non-Instantiable)

Group related static functions without allowing any instances:

```cpp
struct MathUtils {
    MathUtils() = delete;   // no instances allowed

    static int max(int a, int b) { return (a > b) ? a : b; }
    static int min(int a, int b) { return (a < b) ? a : b; }
};

int main() {
    int m = MathUtils::max(10, 20);  // OK
    // MathUtils mu;                 // ERROR: ctor is deleted
}
```

- Deleting the default ctor stops both stack and heap allocation.

---

### Friend-Only Creation

Only a specific helper can create instances:

```cpp
#include <iostream>

class SecretData {
public:
    int getCode() const { return code; }

private:
    SecretData(int c) : code(c) {}
    int code;

    friend class SecretManager;  // allow only this class to construct
};

class SecretManager {
public:
    static SecretData make(int c) {
        return SecretData(c);
    }
};

int main() {
    // SecretData sd(42);          // ERROR: ctor is private
    SecretData sd = SecretManager::make(42);
    std::cout << "Code: " << sd.getCode() << "\n";
}
```

- `SecretData`’s ctor is private; only `SecretManager` (its friend) can call it.

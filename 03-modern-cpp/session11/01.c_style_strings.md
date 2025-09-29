# C-Style Strings in C++

A comprehensive guide to using C-style (null-terminated) strings in C++, packed with numerous examples to illustrate every concept.

## Table of Contents

- [C-Style Strings in C++](#c-style-strings-in-c)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction](#1-introduction)
  - [2. What Is a C-Style String?](#2-what-is-a-c-style-string)
  - [3. Declaration and Initialization](#3-declaration-and-initialization)
    - [3.1 Fixed-Size Character Arrays](#31-fixed-size-character-arrays)
    - [3.2 String Literals](#32-string-literals)
  - [4. Common C-Style String Functions](#4-common-c-style-string-functions)
    - [1. `strlen`](#1-strlen)
    - [2. `strcpy`](#2-strcpy)
    - [3. `strncpy`](#3-strncpy)
    - [4. `strcat`](#4-strcat)
    - [5. `strncat`](#5-strncat)
    - [6. `strcmp`](#6-strcmp)
    - [7. `strncmp`](#7-strncmp)
    - [8. `strchr`](#8-strchr)
    - [9. `strrchr`](#9-strrchr)
    - [10. `strstr`](#10-strstr)
    - [11. `strspn` \& `strcspn`](#11-strspn--strcspn)
    - [12. `strtok` / `strtok_r`](#12-strtok--strtok_r)
    - [13. Memory \& Miscellaneous Helpers](#13-memory--miscellaneous-helpers)
  - [5. Modification and Concatenation](#5-modification-and-concatenation)
  - [6. Buffer Overflows and Safety](#6-buffer-overflows-and-safety)
  - [7. Converting Between C-Style Strings and std::string](#7-converting-between-c-style-strings-and-stdstring)
  - [8. Real-World Examples](#8-real-world-examples)
    - [8.1 Command-Line Argument Handling](#81-command-line-argument-handling)
    - [8.2 Parsing Simple CSV](#82-parsing-simple-csv)
  - [9. Best Practices and Tips](#9-best-practices-and-tips)
  - [10. References](#10-references)

---

## 1. Introduction

C-style strings are the traditional way of handling text in C and early C++ code. They consist of sequences of characters terminated by a special null character (`'\0'`). Although modern C++ encourages using `std::string`, understanding C-style strings remains essential for low-level programming, interoperability with C libraries, and performance-critical code.

This README explains how to declare, initialize, and manipulate C-style strings, demonstrates common pitfalls, and provides a wealth of examples.

---

## 2. What Is a C-Style String?

A C-style string is simply an array of characters ending in a null terminator:

```cpp
char s[] = "Hello"; // Memory layout: 'H', 'e', 'l', 'l', 'o', '\0'
```

- The null character (`'\0'`) marks the end of the string.
- Functions from `<cstring>` rely on this terminator to determine string length and perform operations.

---

## 3. Declaration and Initialization

### 3.1 Fixed-Size Character Arrays

You can reserve a fixed-size buffer for strings:

```cpp
char buffer[10]; // Can hold up to 9 characters + '\0'
```

**Example: Uninitialized vs. zero-initialized**

```cpp
char msg1[6];       // Contains garbage/indeterminate values
char msg2[6] = {0}; // All bytes zero, equivalent to "\0\0\0\0\0\0"
```

### 3.2 String Literals

You can initialize directly from a literal:

```cpp
char greeting[] = "Hello, world!";    // Size = 14 (13 chars + '\0')
const char* ptr   = "Read-only string"; // Points to static storage
```

**Warning:** Modifying a string literal through a non-const pointer is undefined behavior:

```cpp
char* p = "Mutable?"; // Danger: modifying *p is undefined
```

---

## 4. Common C-Style String Functions

Below is a **comprehensive** list of functions from `<cstring>` (and related memory helpers) for working with C-style strings. Each entry shows the prototype, a brief description, and one or more examples.

---

### 1. `strlen`

```cpp
size_t strlen(const char *s);
```

- **Description**: Returns the number of characters in the null-terminated string `s` (excluding the `'\0'`).
- **Example**:

  ```cpp
  const char *msg = "Hello, world!";
  size_t len      = strlen(msg);  // len == 13
  ```

---

### 2. `strcpy`

```cpp
char *strcpy(char *dest, const char *src);
```

- **Description**: Copies the entire null-terminated `src` (including `'\0'`) into `dest`.
- ** Danger**: `dest` must be large enough to hold `src`.
- **Example**:

  ```cpp
  char buf[20];
  strcpy(buf, "Sample");  // buf == "Sample"
  ```

---

### 3. `strncpy`

```cpp
char *strncpy(char *dest, const char *src, size_t n);
```

- **Description**: Copies up to `n` characters from `src` into `dest`.

  - If `src` is shorter than `n`, the remainder of `dest` is padded with `'\0'`.
  - If `src` length ≥ `n`, **no** trailing `'\0'` is appended (must add manually).

- **Example**:

  ```cpp
  char buf[6];
  strncpy(buf, "Example", 5);
  buf[5] = '\0';  // ensure termination
  // buf == "Examp"
  ```

---

### 4. `strcat`

```cpp
char *strcat(char *dest, const char *src);
```

- **Description**: Appends the null-terminated `src` onto the end of `dest`.
- ** Danger**: `dest` must have enough free space.
- **Example**:

  ```cpp
  char buf[32] = "Hello";
  strcat(buf, ", C++!");  // buf == "Hello, C++!"
  ```

---

### 5. `strncat`

```cpp
char *strncat(char *dest, const char *src, size_t n);
```

- **Description**: Appends up to `n` characters from `src` to `dest`, then adds a `'\0'`.
- **Example**:

  ```cpp
  char buf[20] = "Data: ";
  strncat(buf, "1234567890", 4);
  // buf == "Data: 1234"
  ```

---

### 6. `strcmp`

```cpp
int strcmp(const char *s1, const char *s2);
```

- **Description**: Lexicographically compares `s1` vs `s2`.

  - Returns `<0` if `s1 < s2`, `0` if equal, `>0` if `s1 > s2`.

- **Example**:

  ```cpp
  strcmp("abc",  "abd");   // < 0
  strcmp("hello","hello"); //  0
  strcmp("world","word");  // > 0
  ```

---

### 7. `strncmp`

```cpp
int strncmp(const char *s1, const char *s2, size_t n);
```

- **Description**: Compares up to `n` characters of `s1` and `s2`.
- **Example**:

  ```cpp
  strncmp("apple", "apricot", 2); // 0 (only 'a','p' compared)
  ```

---

### 8. `strchr`

```cpp
char *strchr(const char *s, int c);
```

- **Description**: Finds the first occurrence of character `c` in `s`.

  - Returns a pointer to it, or `nullptr` if not found.

- **Example**:

  ```cpp
  const char *fruit = "banana";
  char *p = strchr(fruit, 'n'); // p points at fruit[2]
  ```

---

### 9. `strrchr`

```cpp
char *strrchr(const char *s, int c);
```

- **Description**: Finds the **last** occurrence of `c` in `s`.

  - Returns a pointer or `nullptr`.

- **Example**:

  ```cpp
  const char *fruit = "banana";
  char *p = strrchr(fruit, 'a'); // p points at fruit[5]
  ```

---

### 10. `strstr`

```cpp
char *strstr(const char *haystack, const char *needle);
```

- **Description**: Finds the first occurrence of substring `needle` in `haystack`.

  - Returns a pointer or `nullptr`.

- **Example**:

  ```cpp
  const char *text = "embedded systems";
  char *sub = strstr(text, "sys"); // sub points at text[9]
  ```

---

### 11. `strspn` & `strcspn`

```cpp
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
```

- **`strspn`**: Length of initial segment of `s` consisting only of chars in `accept`.
- **`strcspn`**: Length of initial segment of `s` containing no chars from `reject`.
- **Examples**:

  ```cpp
  strspn("123abc", "0123456789"); // 3
  strcspn("hello world", " ");   // 5 (space at index 5)
  ```

---

### 12. `strtok` / `strtok_r`

```cpp
char *strtok(char *s, const char *delim);
char *strtok_r(char *s, const char *delim, char **saveptr);
```

- **Description**: Splits `s` into tokens separated by any char in `delim`.

  - `strtok` is **not** thread-safe; `strtok_r` is reentrant.

- **Example**:

  ```cpp
  char data[] = "one,two,three";
  char *save;
  char *token = strtok_r(data, ",", &save);
  while (token) {
      std::cout << token << '\n';
      token = strtok_r(nullptr, ",", &save);
  }
  ```

---

### 13. Memory & Miscellaneous Helpers

```cpp
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int   memcmp(const void *s1, const void *s2, size_t n);
char *strerror(int errnum);
```

- **Examples**:

  ```cpp
  char a[] = "123456";
  // memmove handles overlap safely:
  memmove(a + 2, a, 4);  // a == "121234"

  char buf[10];
  memset(buf, '.', 9);
  buf[9] = '\0';         // "........."

  int cmp = memcmp("abc", "abd", 2); // 0 (only first 2 bytes)

  std::cout << strerror(ENOENT); // "No such file or directory"
  ```

---

## 5. Modification and Concatenation

Since C-style strings are arrays, you can modify them element by element:

```cpp
char data[6] = "Hello";
data[0] = 'h';    // "hello"
data[5] = '\0';   // safe termination
```

**Example: Building a message**

```cpp
char msg[50] = "User: ";
strcat(msg, "Alice");          // msg == "User: Alice"
strcat(msg, ", Score: ");
char scoreStr[10];
sprintf(scoreStr, "%d", 95);   // convert number to string
strcat(msg, scoreStr);         // msg == "User: Alice, Score: 95"
```

---

## 6. Buffer Overflows and Safety

Overwriting the null terminator or writing beyond the array leads to buffer overflows:

```cpp
char buf[5];
strcpy(buf, "TooLong"); // undefined behavior: writes past buf[4]
```

**Safer alternatives:**

- Always ensure enough space: compute required size with `strlen(src) + 1`.
- Use the “n”-variants (`strncpy`, `strncat`, etc.) and manually null-terminate.
- In modern C++, prefer `std::string` or `std::array<char, N>` when possible.

---

## 7. Converting Between C-Style Strings and std::string

```cpp
#include <string>

std::string cppStr = "Hello";
const char* cstr   = cppStr.c_str(); // read-only access

std::string copy  = cstr;            // constructs from C-style string
```

**Example: Mixing with C APIs**

```cpp
void cFunction(const char* msg);

std::string s = "Greetings";
cFunction(s.c_str()); // pass C-style string to a C function
```

---

## 8. Real-World Examples

### 8.1 Command-Line Argument Handling

```cpp
#include <iostream>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        std::cout << "Arg " << i << ": " << argv[i] << '\n';
    }
    return 0;
}
```

### 8.2 Parsing Simple CSV

```cpp
#include <iostream>
#include <cstring>

int main() {
    char row[] = "John,Doe,30";
    char* token = std::strtok(row, ",");
    while (token) {
        std::cout << token << '\n';
        token = std::strtok(nullptr, ",");
    }
    return 0;
}
```

---

## 9. Best Practices and Tips

- **Always terminate:** ensure `array[size-1] = '\0'`.
- **Bounds checking:** never assume unbounded inputs.
- **Prefer `std::string`:** for safety and convenience when overhead is acceptable.
- **Know your functions:** understand each `<cstring>` function’s nuances to avoid UB.

---

## 10. References

- Nicolai M. Josuttis, _The C++ Standard Library_
- [cppreference.com – `<cstring>`](https://en.cppreference.com/w/cpp/header/cstring)
- [C FAQ – C-Style Strings](https://c-faq.com/aryptr/ary2.html)

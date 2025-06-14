# Programming with Python 3: Variables and Functions

This README covers the fundamental concepts of Python variables and functions. You'll learn how to write your first Python program in Thonny, understand variables and data types, define functions, and work with variable scope. Each section includes four examples ranging from easy to hard. At the end, you'll complete a mini project that ties everything together.

---

## Table of Contents

1. [First Python Program: Introduction to Thonny IDE](#1-first-python-program-introduction-to-thonny-ide)
2. [Understanding Variables](#2-understanding-variables)
3. [Data Types](#3-data-types)
4. [Defining Functions](#4-defining-functions)
5. [Variable Scope](#5-variable-scope)
6. [Activity: Concatenate Two Uppercase Strings](#6-activity-concatenate-two-uppercase-strings)
7. [Mini Project: Uppercase Concatenator and Analyzer](#7-mini-project-uppercase-concatenator-and-analyzer)

---

## 1. First Python Program: Introduction to Thonny IDE

Thonny is a beginner-friendly Python IDE that comes pre-installed with Raspberry Pi OS. Use it to write and test your Python programs.

### Example 1: Hello, World!

```python
print("Hello, World!")
```

### Example 2: Simple Arithmetic

```python
print("2 + 3 =", 2 + 3)
```

### Example 3: User Input and Greeting

```python
name = input("Enter your name: ")
print("Hello, " + name + "!")
```

### Example 4: Function Demonstration

```python
def greet(name):
    return "Hello, " + name + "!"

print(greet("Alice"))
```

Run these examples in Thonny to get familiar with the IDE’s interface and basic Python execution.

---

## 2. Understanding Variables

Variables store data that your program can use and modify.

### Example 1: Basic Variable Assignment

```python
x = 5
print("x =", x)
```

### Example 2: Arithmetic with Variables

```python
a = 10
b = 20
result = a + b
print("Result of a + b =", result)
```

### Example 3: String Variables and Concatenation

```python
first_name = "John"
last_name = "Doe"
full_name = first_name + " " + last_name
print("Full name:", full_name)
```

### Example 4: Reassigning Variables and Type Change

```python
var = 100
print("Initial value (int):", var)
var = "One Hundred"
print("Reassigned value (str):", var)
```

---

## 3. Data Types

Python supports several data types. Here are examples that explore integers, floats, strings, booleans, and lists.

### Example 1: Integers and Floats

```python
integer_num = 42
float_num = 3.14159
print("Integer:", integer_num)
print("Float:", float_num)
```

### Example 2: Strings and String Methods

```python
text = "Hello, Python!"
print("Original text:", text)
print("Uppercase text:", text.upper())
```

### Example 3: Booleans

```python
is_valid = True
is_empty = False
print("is_valid =", is_valid)
print("is_empty =", is_empty)
```

### Example 4: Lists and Basic Operations

```python
numbers = [1, 2, 3, 4, 5]
print("List:", numbers)
numbers.append(6)
print("After appending 6:", numbers)
```

---

## 4. Defining Functions

Functions allow you to reuse code and build modular programs.

### Example 1: Simple Function Without Parameters

```python
def say_hello():
    return "Hello!"

print(say_hello())
```

### Example 2: Function with Parameters

```python
def add(a, b):
    return a + b

print("5 + 7 =", add(5, 7))
```

### Example 3: Function for String Manipulation

```python
def greet_person(name):
    return "Welcome, " + name + "!"

print(greet_person("Alice"))
```

### Example 4: Function with Conditional Logic

```python
def check_number(num):
    if num > 0:
        return "Positive"
    elif num == 0:
        return "Zero"
    else:
        return "Negative"

print("check_number(10):", check_number(10))
print("check_number(0):", check_number(0))
print("check_number(-5):", check_number(-5))
```

---

## 5. Variable Scope

Variable scope determines where variables can be accessed within your program.

### Example 1: Local Scope

```python
def local_example():
    local_var = "I'm local"
    print("Inside function:", local_var)

local_example()
# Uncommenting the next line would cause an error:
# print(local_var)
```

### Example 2: Global Variables

```python
global_var = "I'm global"

def print_global():
    print("Inside function:", global_var)

print_global()
print("Outside function:", global_var)
```

### Example 3: Modifying Global Variables

```python
counter = 0

def increment():
    global counter
    counter += 1
    print("Inside function, counter =", counter)

increment()
print("Outside function, counter =", counter)
```

### Example 4: Variable Shadowing

```python
x = "global value"

def shadow():
    x = "local value"
    print("Inside function:", x)

shadow()
print("Outside function:", x)
```

---

## 6. Activity: Concatenate Two Uppercase Strings

Develop a function that takes two strings, converts them to uppercase, and concatenates them.

### Example 1: Basic Concatenation Function

```python
def concat_uppercase(str1, str2):
    return str1.upper() + str2.upper()

print(concat_uppercase("hello", "world"))
```

### Example 2: Trimming Whitespace Before Concatenation

```python
def concat_uppercase(str1, str2):
    return str1.strip().upper() + str2.strip().upper()

print(concat_uppercase("  hello  ", "  world  "))
```

### Example 3: Using Variables and User Input

```python
def concat_uppercase(str1, str2):
    return str1.strip().upper() + str2.strip().upper()

first_input = input("Enter first string: ")
second_input = input("Enter second string: ")
print("Concatenated:", concat_uppercase(first_input, second_input))
```

### Example 4: Incorporating Error Handling

```python
def concat_uppercase(str1, str2):
    try:
        result = str1.strip().upper() + str2.strip().upper()
        return result
    except AttributeError:
        return "Error: Both inputs must be strings."

print(concat_uppercase("hello", "world"))
print(concat_uppercase("hello", None))
```

---

## 7. Mini Project: Uppercase Concatenator and Analyzer

### Project Description

Create a program that:

- Prompts the user for two strings.
- Converts both strings to uppercase.
- Concatenates the strings.
- Analyzes the concatenated string by counting the number of characters.
- Displays the concatenated string along with its length.

### Implementation

```python
def concat_uppercase(str1, str2):
    """Converts two strings to uppercase and concatenates them."""
    try:
        result = str1.strip().upper() + str2.strip().upper()
        return result
    except AttributeError:
        return None

def analyze_string(s):
    """Analyzes the string to count the number of characters."""
    if s is None:
        return "Invalid input provided."
    length = len(s)
    return f"The concatenated string is '{s}' and its length is {length} characters."

def main():
    print("Welcome to the Uppercase Concatenator and Analyzer!")
    first_input = input("Enter the first string: ")
    second_input = input("Enter the second string: ")

    concatenated = concat_uppercase(first_input, second_input)
    analysis = analyze_string(concatenated)

    print(analysis)

if __name__ == "__main__":
    main()
```

### Project Explanation

- **concat_uppercase:** Converts input strings to uppercase and concatenates them, with basic error handling.
- **analyze_string:** Determines and returns the length of the concatenated string.
- **main:** Manages user input, processes the concatenation and analysis, and displays the results.

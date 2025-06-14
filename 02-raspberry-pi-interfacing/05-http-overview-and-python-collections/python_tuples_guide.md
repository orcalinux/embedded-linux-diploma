# Python Tuples – A Comprehensive Guide

This **README** provides an overview of **Python tuples**, complete with code examples and exercises. Tuples are one of the fundamental data structures in Python, used for grouping related data into an **immutable** sequence.

## Table of Contents

- [Python Tuples – A Comprehensive Guide](#python-tuples--a-comprehensive-guide)
  - [Table of Contents](#table-of-contents)
  - [1. What is a Tuple?](#1-what-is-a-tuple)
  - [2. Creating Tuples](#2-creating-tuples)
    - [2.1 Using Parentheses](#21-using-parentheses)
    - [2.2 Parentheses Omission](#22-parentheses-omission)
    - [2.3 Single-Element Tuples](#23-single-element-tuples)
  - [3. Accessing and Slicing](#3-accessing-and-slicing)
  - [4. Immutability](#4-immutability)
  - [5. Tuple Packing and Unpacking](#5-tuple-packing-and-unpacking)
    - [5.1 Packing](#51-packing)
    - [5.2 Unpacking](#52-unpacking)
  - [6. Common Operations](#6-common-operations)
  - [7. Named Tuples](#7-named-tuples)
  - [8. Code Examples](#8-code-examples)
  - [9. Exercises](#9-exercises)
  - [10. Additional Resources](#10-additional-resources)
    - [**Happy Coding with Tuples!**](#happy-coding-with-tuples)

---

## 1. What is a Tuple?

A **tuple** in Python is an **ordered** and **immutable** sequence of elements.  
- **Ordered** means the items are stored in a defined sequence, and each item’s position is fixed.  
- **Immutable** means once created, the elements inside the tuple **cannot** be changed.

```python
# Example of a tuple
my_tuple = (1, 2, 3)
```

---

## 2. Creating Tuples

### 2.1 Using Parentheses

Most commonly, tuples are created by placing items within **parentheses** `()`:

```python
# Simple tuple
numbers = (1, 2, 3)

# Mixed data types
mixed = (1, "apple", 3.14, True)
```

### 2.2 Parentheses Omission

You can also create a tuple **without** parentheses. Python automatically treats comma-separated values as a tuple:

```python
colors = "red", "green", "blue"
print(colors)  # ('red', 'green', 'blue')
```

### 2.3 Single-Element Tuples

A single-element tuple **must** include a trailing comma to differentiate it from a simple expression:

```python
single_element = (42,)
print(type(single_element))  # <class 'tuple'>

not_a_tuple = (42)
print(type(not_a_tuple))  # <class 'int'>
```

---

## 3. Accessing and Slicing

You can access tuple elements by **index** (starting at 0) or use **slicing** to get a subrange of elements:

```python
fruits = ("apple", "banana", "cherry", "date")

# Access by index
print(fruits[0])   # "apple"
print(fruits[-1])  # "date"

# Slice (start at index 1 up to but not including index 3)
print(fruits[1:3]) # ("banana", "cherry")
```

---

## 4. Immutability

Once a tuple is created, its elements **cannot be altered**. Attempting to change an element results in an error:

```python
numbers = (1, 2, 3)
# numbers[0] = 99  # Uncommenting this line will raise a TypeError
```

If you need a **modifiable** sequence, consider using a **list** instead.

---

## 5. Tuple Packing and Unpacking

### 5.1 Packing

“Tuple Packing” refers to assigning multiple values into a tuple in one statement:

```python
person = "Alice", 25, "Engineer"
```

### 5.2 Unpacking

“Tuple Unpacking” allows you to extract the tuple’s contents into separate variables:

```python
name, age, profession = person
print(name)       # "Alice"
print(age)        # 25
print(profession) # "Engineer"
```

> **Tip:** The number of variables **must match** the number of items in the tuple.

---

## 6. Common Operations

| Operation               | Syntax or Function               | Description                                    |
|-------------------------|----------------------------------|------------------------------------------------|
| **Length**              | `len(my_tuple)`                  | Returns number of elements in the tuple        |
| **Concatenation**       | `tuple1 + tuple2`                | Creates a new tuple by joining two tuples      |
| **Repetition**          | `my_tuple * 3`                   | Repeats the tuple 3 times                      |
| **Membership**          | `value in my_tuple`              | Checks if `value` is in the tuple              |
| **Index**               | `my_tuple.index(value)`          | Returns the index of the first match           |
| **Count**               | `my_tuple.count(value)`          | Counts how many times `value` appears          |

---

## 7. Named Tuples

Python provides **`namedtuple`** in the `collections` module, which creates a tuple-like object with **named fields**. This allows you to access tuple elements by name instead of index:

```python
from collections import namedtuple

Person = namedtuple("Person", ["name", "age", "city"])
bob = Person(name="Bob", age=30, city="New York")

print(bob.name)  # "Bob"
print(bob.age)   # 30
```

---

## 8. Code Examples

Below are a few **Python code snippets** demonstrating tuple usage.

```python
# 1. Creating and accessing tuples
numbers = (10, 20, 30)
print(numbers[1])  # 20

# 2. Tuple packing and unpacking
person = ("Alice", 25, "Engineer")
name, age, job = person
print(name, age, job)  # Alice 25 Engineer

# 3. Checking membership
if "Alice" in person:
    print("Found Alice!")

# 4. Tuple concatenation
tuple_a = (1, 2)
tuple_b = (3, 4)
tuple_c = tuple_a + tuple_b
print(tuple_c)  # (1, 2, 3, 4)

# 5. Named tuples
from collections import namedtuple
Point = namedtuple("Point", ["x", "y"])
p1 = Point(3, 5)
print(p1.x, p1.y)  # 3 5
```

---

## 9. Exercises

Try these exercises to get comfortable working with tuples.

1. **Create a Tuple**  
   - Create a tuple called `dimensions` with three integers: 10, 20, and 30.
   - Print the length of this tuple using `len()`.

2. **Unpack a Tuple**  
   - Create a tuple called `employee` with values: `("Bob", 30, "Sales")`.
   - Unpack it into three variables: `emp_name`, `emp_age`, `emp_dept`.
   - Print each variable to confirm the values.

3. **Concatenate and Slice**  
   - Create two tuples:  
     `tuple1 = (1, 2, 3)`  
     `tuple2 = (4, 5, 6)`  
   - Concatenate them into `tuple3`.
   - Print a slice of `tuple3` containing only the elements `(2, 3, 4)`.

4. **Check Immutability**  
   - Create a tuple `my_tuple = ("x", "y", "z")`.
   - Try modifying the first element: `my_tuple[0] = "new"`.  
   - Observe and note the error.

5. **Named Tuple**  
   - Import `namedtuple` from `collections`.
   - Create a named tuple type called `Car` with fields `brand`, `model`, `year`.
   - Instantiate a car named `my_car` with values (`"Toyota"`, `"Corolla"`, `2020`).
   - Print each field (`my_car.brand`, `my_car.model`, `my_car.year`) individually.

> **Bonus**: Write a function that **returns multiple values** (in a tuple) and unpack them in your main code.

---

## 10. Additional Resources

- [Official Python Documentation – Tuples](https://docs.python.org/3/tutorial/datastructures.html#tuples-and-sequences)
- [Real Python – Tuples in Python](https://realpython.com/python-lists-tuples/)
- [Namedtuple in Python](https://docs.python.org/3/library/collections.html#collections.namedtuple)
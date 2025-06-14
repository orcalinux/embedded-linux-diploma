# Python Conditions, Loops, and Lists: Comprehensive Guide

This guide covers Python's conditional statements, loops, lists, and an introduction to modules. Each section provides four examples ranging from simple to more advanced cases. At the end, you'll complete a mini project that integrates all these topics.

---

## Table of Contents

- [Python Conditions, Loops, and Lists: Comprehensive Guide](#python-conditions-loops-and-lists-comprehensive-guide)
  - [Table of Contents](#table-of-contents)
  - [Conditional Statements](#conditional-statements)
    - [Example 1: Basic if Statement](#example-1-basic-if-statement)
    - [Example 2: if-else Statement](#example-2-if-else-statement)
    - [Example 3: if-elif-else Statement](#example-3-if-elif-else-statement)
    - [Example 4: Complex Conditions with Logical Operators](#example-4-complex-conditions-with-logical-operators)
  - [User Input Validation Activity](#user-input-validation-activity)
  - [Loop Constructs](#loop-constructs)
    - [Example 1: Simple for Loop](#example-1-simple-for-loop)
    - [Example 2: Iterating Over a List with a for Loop](#example-2-iterating-over-a-list-with-a-for-loop)
    - [Example 3: Basic while Loop](#example-3-basic-while-loop)
    - [Example 4: Advanced while Loop with Break and Continue](#example-4-advanced-while-loop-with-break-and-continue)
  - [Working with Lists](#working-with-lists)
    - [Example 1: Creating and Printing a List](#example-1-creating-and-printing-a-list)
    - [Example 2: List Manipulation (Append, Remove)](#example-2-list-manipulation-append-remove)
    - [Example 3: Iterating Over a List](#example-3-iterating-over-a-list)
    - [Example 4: List Comprehensions](#example-4-list-comprehensions)
  - [Activity: Compute Maximum Value in a List](#activity-compute-maximum-value-in-a-list)
  - [Introduction to Python Modules](#introduction-to-python-modules)
    - [Example 1: Importing a Standard Module](#example-1-importing-a-standard-module)
    - [Example 2: Using a Function from a Module](#example-2-using-a-function-from-a-module)
    - [Example 3: Importing with an Alias](#example-3-importing-with-an-alias)
    - [Example 4: Creating and Importing a Custom Module](#example-4-creating-and-importing-a-custom-module)
  - [Mini Project: Student Grades Analyzer](#mini-project-student-grades-analyzer)
    - [Project Description](#project-description)
    - [Implementation](#implementation)
    - [Project Explanation](#project-explanation)

---

## Conditional Statements

### Example 1: Basic if Statement

```python
number = 10
if number > 5:
    print("The number is greater than 5.")
```

### Example 2: if-else Statement

```python
number = 3
if number > 5:
    print("The number is greater than 5.")
else:
    print("The number is not greater than 5.")
```

### Example 3: if-elif-else Statement

```python
number = 5
if number > 5:
    print("The number is greater than 5.")
elif number == 5:
    print("The number is equal to 5.")
else:
    print("The number is less than 5.")
```

### Example 4: Complex Conditions with Logical Operators

```python
age = 20
citizenship = True

if age >= 18 and citizenship:
    print("You are eligible to vote.")
else:
    print("You are not eligible to vote.")
```

---

## User Input Validation Activity

Create a program that validates user input by checking if the entered value is a positive integer.

```python
user_input = input("Enter a positive integer: ")

if user_input.isdigit():
    number = int(user_input)
    if number > 0:
        print("Valid input!")
    else:
        print("The number is not positive.")
else:
    print("Invalid input! Please enter a positive integer.")
```

---

## Loop Constructs

### Example 1: Simple for Loop

```python
for i in range(5):
    print("Iteration:", i)
```

### Example 2: Iterating Over a List with a for Loop

```python
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
    print("Fruit:", fruit)
```

### Example 3: Basic while Loop

```python
count = 0
while count < 5:
    print("Count is", count)
    count += 1
```

### Example 4: Advanced while Loop with Break and Continue

```python
number = 0
while number < 10:
    number += 1
    if number == 5:
        continue  # Skip when number is 5
    if number > 8:
        break  # Exit loop when number is greater than 8
    print("Number:", number)
```

---

## Working with Lists

### Example 1: Creating and Printing a List

```python
colors = ["red", "green", "blue"]
print("Colors:", colors)
```

### Example 2: List Manipulation (Append, Remove)

```python
numbers = [1, 2, 3]
numbers.append(4)
print("After appending 4:", numbers)
numbers.remove(2)
print("After removing 2:", numbers)
```

### Example 3: Iterating Over a List

```python
animals = ["cat", "dog", "rabbit"]
for animal in animals:
    print("Animal:", animal)
```

### Example 4: List Comprehensions

```python
squares = [x**2 for x in range(1, 6)]
print("Squares:", squares)
```

---

## Activity: Compute Maximum Value in a List

Write a script that computes the maximum value from a list of numbers without using the built-in `max()` function.

```python
numbers = [15, 22, 8, 19, 31, 7]
max_value = numbers[0]

for num in numbers:
    if num > max_value:
        max_value = num

print("The maximum value in the list is:", max_value)
```

---

## Introduction to Python Modules

Modules allow you to organize and reuse code across different programs.

### Example 1: Importing a Standard Module

```python
import math
print("Square root of 16 is:", math.sqrt(16))
```

### Example 2: Using a Function from a Module

```python
import random
print("A random integer between 1 and 10:", random.randint(1, 10))
```

### Example 3: Importing with an Alias

```python
import datetime as dt
print("Current date and time:", dt.datetime.now())
```

### Example 4: Creating and Importing a Custom Module

_Create a file named `my_module.py` with the following content:_

```python
# my_module.py
def greet(name):
    return f"Hello, {name}!"
```

_Then, in your main script:_

```python
import my_module
print(my_module.greet("Alice"))
```

---

## Mini Project: Student Grades Analyzer

### Project Description

In this project, you'll create a program that:

- Prompts the user for the number of students.
- Validates each student's grade (ensuring it is a number between 0 and 100).
- Stores the grades in a list.
- Computes the maximum grade, average grade, and counts how many students passed (grade ≥ 50) and failed (grade < 50).
- Utilizes conditional statements, loops, lists, and modules.

### Implementation

```python
def get_valid_grade(student_number):
    """Prompt for a valid grade between 0 and 100 for a student."""
    while True:
        grade_input = input(f"Enter grade for student {student_number} (0-100): ")
        if grade_input.isdigit():
            grade = int(grade_input)
            if 0 <= grade <= 100:
                return grade
        print("Invalid input. Please enter a number between 0 and 100.")

def analyze_grades(grades):
    """Analyze grades to compute maximum, average, and pass/fail counts."""
    max_grade = grades[0]
    total = 0
    pass_count = 0
    for grade in grades:
        if grade > max_grade:
            max_grade = grade
        total += grade
        if grade >= 50:
            pass_count += 1
    average_grade = total / len(grades)
    fail_count = len(grades) - pass_count
    return max_grade, average_grade, pass_count, fail_count

def main():
    print("Welcome to the Student Grades Analyzer!")

    num_students_input = input("Enter the number of students: ")
    while not num_students_input.isdigit() or int(num_students_input) <= 0:
        num_students_input = input("Please enter a valid positive number for the number of students: ")
    num_students = int(num_students_input)

    grades = []
    for i in range(1, num_students + 1):
        grade = get_valid_grade(i)
        grades.append(grade)

    max_grade, avg_grade, pass_count, fail_count = analyze_grades(grades)

    print("\n--- Grades Analysis ---")
    print("Grades entered:", grades)
    print("Maximum Grade:", max_grade)
    print("Average Grade:", avg_grade)
    print("Passed:", pass_count)
    print("Failed:", fail_count)

if __name__ == "__main__":
    main()
```

### Project Explanation

- **Input Validation:** The function `get_valid_grade()` ensures that each grade is between 0 and 100.
- **Loop and Conditional Usage:** Loops and conditionals are used to gather grades and analyze them.
- **List Usage:** Grades are stored in a list for processing.
- **Modularity:** Functions are used to separate different parts of the logic, making the code reusable and organized.

# Python Dictionary: A Comprehensive Guide

## Introduction

A **Python dictionary** is a built-in data structure that stores data in **key-value pairs**. It is **fast, flexible, and efficient** for data retrieval, storage, and manipulation. This guide will walk you through the basics and advanced operations of dictionaries, practical code examples, and mini projects you can expand upon.

**Why Use Dictionaries?**

- **Fast lookups:** Utilizes hash tables.
- **Flexible:** Supports various data types.
- **Ordered:** Maintains insertion order (Python 3.7+).
- **Nested:** Can contain dictionaries within dictionaries.

---

## Quick Start: Copyable Dictionary Example

Below is a complete Python script you can save as `dict_example.py` and run immediately:

```python
# dict_example.py

def main():
    # Creating a dictionary
    person = {
        "name": "Alice",
        "age": 28,
        "city": "New York"
    }
    print("Initial dictionary:", person)

    # Accessing and modifying values
    print("Name:", person["name"])
    person["age"] = 29
    person["email"] = "alice@example.com"
    print("Updated dictionary:", person)

    # Deleting an item
    del person["city"]
    print("After deletion:", person)

    # Iterating over key-value pairs
    for key, value in person.items():
        print(f"{key}: {value}")

if __name__ == "__main__":
    main()
```

---

## Table of Contents

- [Python Dictionary: A Comprehensive Guide](#python-dictionary-a-comprehensive-guide)
  - [Introduction](#introduction)
  - [Quick Start: Copyable Dictionary Example](#quick-start-copyable-dictionary-example)
  - [Table of Contents](#table-of-contents)
  - [What is a Python Dictionary?](#what-is-a-python-dictionary)
    - [**Example:**](#example)
  - [Basic Dictionary Operations](#basic-dictionary-operations)
    - [1. Creating a Dictionary](#1-creating-a-dictionary)
    - [2. Accessing Values](#2-accessing-values)
    - [3. Modifying a Dictionary](#3-modifying-a-dictionary)
    - [4. Deleting Items](#4-deleting-items)
  - [Advanced Dictionary Methods](#advanced-dictionary-methods)
    - [1. Iterating Through a Dictionary](#1-iterating-through-a-dictionary)
    - [2. Dictionary Comprehension](#2-dictionary-comprehension)
    - [3. Merging Dictionaries](#3-merging-dictionaries)
  - [Dictionary Methods Reference Table](#dictionary-methods-reference-table)
  - [Practical Code Examples](#practical-code-examples)
    - [Example 1: Counting Character Frequency](#example-1-counting-character-frequency)
    - [Example 2: Reversing a Dictionary](#example-2-reversing-a-dictionary)
  - [Mini Projects](#mini-projects)
    - [Mini Project 1: Contact Book](#mini-project-1-contact-book)
    - [Mini Project 2: Word Frequency Counter](#mini-project-2-word-frequency-counter)
    - [Mini Project 3: Student Grade Manager](#mini-project-3-student-grade-manager)
  - [Conclusion](#conclusion)

---

## What is a Python Dictionary?

A **dictionary** is an **unordered** (prior to Python 3.7) and **mutable** collection that stores data in **key-value pairs**. In a dictionary:

- **Keys** must be unique and immutable (e.g., strings, numbers, tuples).
- **Values** can be any Python object.
- **Dynamic:** Dictionaries can be modified (items added, removed, or changed) at runtime.

### **Example:**

```python
# Creating a dictionary with Arabic names
person = {
    "name": "Mahmoud",
    "age": 30,
    "city": "Cairo"
}
print(person["name"])  # Output: Mahmoud
```

---

## Basic Dictionary Operations

### 1. Creating a Dictionary

```python
# Empty dictionary
empty_dict = {}

# Dictionary with values
person = {"name": "Mohamed", "age": 25, "city": "Alexandria"}

# Using dict() constructor
person2 = dict(name="Ali", age=35, city="Giza")
```

### 2. Accessing Values

```python
# Using the key
print(person["name"])  # Output: Mohamed

# Using get() to avoid errors if key doesn't exist
print(person.get("email", "Not provided"))  # Output: Not provided
```

### 3. Modifying a Dictionary

```python
person["age"] = 26  # Update an existing key
person["email"] = "mohamed@example.com"  # Add a new key-value pair
```

### 4. Deleting Items

```python
del person["city"]  # Removes "city" key
age = person.pop("age")  # Removes "age" and returns its value
```

---

## Advanced Dictionary Methods

### 1. Iterating Through a Dictionary

```python
# Iterating over keys
for key in person.keys():
    print(key)

# Iterating over values
for value in person.values():
    print(value)

# Iterating over key-value pairs
for key, value in person.items():
    print(f"{key}: {value}")
```

### 2. Dictionary Comprehension

```python
squared_numbers = {x: x**2 for x in range(5)}
print(squared_numbers)  # Output: {0: 0, 1: 1, 2: 4, 3: 9, 4: 16}
```

### 3. Merging Dictionaries

```python
dict1 = {"a": 1, "b": 2}
dict2 = {"b": 3, "c": 4}

# Using update()
dict1.update(dict2)
print(dict1)  # Output: {'a': 1, 'b': 3, 'c': 4}

# Using dictionary unpacking (Python 3.5+)
merged_dict = {**dict1, **dict2}
print(merged_dict)
```

---

## Dictionary Methods Reference Table

Below is a table summarizing the most common dictionary methods:

| **Method**          | **Description**                                                                                                      | **Example**                                           |
| ------------------- | -------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------- |
| `dict.clear()`      | Removes all items from the dictionary.                                                                               | `person.clear()`                                      |
| `dict.copy()`       | Returns a shallow copy of the dictionary.                                                                            | `new_person = person.copy()`                          |
| `dict.get(key)`     | Returns the value for the given key; returns `None` (or a default) if key is not found.                              | `email = person.get("email", "Not provided")`         |
| `dict.items()`      | Returns a view object of the dictionary’s key-value pairs.                                                           | `for key, value in person.items(): print(key, value)` |
| `dict.keys()`       | Returns a view object of the dictionary’s keys.                                                                      | `print(list(person.keys()))`                          |
| `dict.pop(key)`     | Removes the specified key and returns its value; raises a KeyError if key is not found unless a default is provided. | `age = person.pop("age", "Not found")`                |
| `dict.popitem()`    | Removes and returns the last inserted key-value pair.                                                                | `item = person.popitem()`                             |
| `dict.setdefault()` | Returns the value of a key if it exists; if not, inserts the key with the specified default value.                   | `value = person.setdefault("country", "Egypt")`       |
| `dict.update()`     | Updates the dictionary with the key/value pairs from another dictionary or iterable.                                 | `person.update({"city": "Alexandria", "age": 27})`    |
| `dict.values()`     | Returns a view object of the dictionary’s values.                                                                    | `print(list(person.values()))`                        |

---

## Practical Code Examples

### Example 1: Counting Character Frequency

```python
text = "hello world"
char_count = {}

for char in text:
    char_count[char] = char_count.get(char, 0) + 1

print(char_count)
# Output: {'h': 1, 'e': 1, 'l': 3, 'o': 2, ' ': 1, 'w': 1, 'r': 1, 'd': 1}
```

### Example 2: Reversing a Dictionary

```python
original = {"apple": "red", "banana": "yellow", "grape": "purple"}
reversed_dict = {v: k for k, v in original.items()}
print(reversed_dict)
# Output: {'red': 'apple', 'yellow': 'banana', 'purple': 'grape'}
```

---

## Mini Projects

### Mini Project 1: Contact Book

**Description:**  
The Contact Book project allows you to store, search, and delete contact information. Each contact is stored as a key (the contact's name) with a corresponding value—a dictionary that contains the contact's phone number and email.

**Input:**

- **Adding a Contact:**
  - Name (string), e.g., `"Mahmoud"`
  - Phone (string), e.g., `"123-456-7890"`
  - Email (string), e.g., `"mahmoud@example.com"`
- **Searching for a Contact:**
  - Enter the contact's name.
- **Deleting a Contact:**
  - Enter the contact's name to remove it.

**Output:**

- When searching, the contact's details (phone and email) are displayed, or a "Contact not found" message if the name doesn’t exist.
- When deleting, the removed contact details are shown or a "Contact not found" message if the name isn’t in the contacts.

**Code:**

```python
contacts = {}

def add_contact(name, phone, email):
    """Adds a new contact to the contact book."""
    contacts[name] = {"phone": phone, "email": email}

def search_contact(name):
    """Searches for a contact by name and returns the contact details."""
    return contacts.get(name, "Contact not found.")

def delete_contact(name):
    """Deletes a contact by name and returns the removed contact details or an error message."""
    return contacts.pop(name, "Contact not found.")

# Usage Example:
add_contact("Mahmoud", "123-456-7890", "mahmoud@example.com")
print("Search result for 'Mahmoud':", search_contact("Mahmoud"))
print("Deleting 'Mahmoud':", delete_contact("Mahmoud"))
print("Search result after deletion:", search_contact("Mahmoud"))
```

_Sample Run:_

```
Search result for 'Mahmoud': {'phone': '123-456-7890', 'email': 'mahmoud@example.com'}
Deleting 'Mahmoud': {'phone': '123-456-7890', 'email': 'mahmoud@example.com'}
Search result after deletion: Contact not found.
```

---

### Mini Project 2: Word Frequency Counter

**Description:**  
The Word Frequency Counter reads a text file and counts how many times each word appears in the file. This project is useful for text analysis and can help identify the most common words.

**Input:**

- A text file (e.g., `sample.txt`) containing text.  
  _Example file content for `sample.txt`:_
  ```
  hello world hello
  ```

**Output:**

- A dictionary where each key is a word and its value is the number of times that word appears.  
  _Expected output for the example:_
  ```
  {'hello': 2, 'world': 1}
  ```

**Code:**

```python
def word_count(filename):
    """Counts the frequency of each word in a text file."""
    with open(filename, 'r') as file:
        words = file.read().lower().split()
        word_freq = {word: words.count(word) for word in set(words)}
    return word_freq

# Example Usage:
print("Word Frequency Count:", word_count("sample.txt"))
```

_Sample Run (given the example file content):_

```
Word Frequency Count: {'hello': 2, 'world': 1}
```

---

### Mini Project 3: Student Grade Manager

**Description:**  
The Student Grade Manager helps you manage student grades. You can add students along with a list of their scores, compute each student's average grade, and display all student details. This project is ideal for basic record-keeping and grade analysis.

**Input:**

- **Adding a Student:**
  - Student name (string), e.g., `"Ali"`
  - A list of scores (list of numbers), e.g., `[85, 90, 78]`
- **Displaying Students:**
  - No user input is required; the function prints each student’s name, scores, and computed average.

**Output:**

- For each student, display their name, list of scores, and average grade formatted to two decimal places.  
  _Expected output for the example:_
  ```
  Ali: [85, 90, 78], Average: 84.33
  Ahmed: [70, 88, 95], Average: 84.33
  ```

**Code:**

```python
grades = {}

def add_student(name, scores):
    """Adds a student and their scores to the grade manager."""
    grades[name] = scores

def average_grade(name):
    """Calculates the average grade for a given student."""
    return sum(grades[name]) / len(grades[name]) if name in grades else "Student not found."

def display_students():
    """Displays all students with their scores and average grade."""
    for student, scores in grades.items():
        avg = average_grade(student)
        print(f"{student}: {scores}, Average: {avg:.2f}")

# Example Usage:
add_student("Ali", [85, 90, 78])
add_student("Ahmed", [70, 88, 95])
display_students()
```

_Sample Run:_

```
Ali: [85, 90, 78], Average: 84.33
Ahmed: [70, 88, 95], Average: 84.33
```

---

## Conclusion

Python dictionaries offer a powerful, efficient way to handle key-value pairs with:

- **Fast Lookups**
- **Dynamic Data Storage**
- **Numerous Built-in Methods**

They are used in real-world applications like contact management, text processing, and data storage. Experiment with the provided code examples, expand the projects (integrating file storage, GUIs with Tkinter, or databases with SQLite), and keep exploring the versatility of Python dictionaries.

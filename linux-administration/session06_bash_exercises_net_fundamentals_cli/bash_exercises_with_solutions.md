## Bash Scripting Exercises

This document contains solutions to common bash scripting exercises, covering topics such as user input, file handling, and conditional statements.

---

### **Table of Contents**

1. [Exercise 1: Login Script](#exercise-1-login-script)
2. [Exercise 2: Simple Calculator](#exercise-2-simple-calculator)
3. [Exercise 3: File Existence Check](#exercise-3-file-existence-check)
4. [Exercise 4: Line Count in a File](#exercise-4-line-count-in-a-file)
5. [Exercise 5: Even or Odd Number](#exercise-5-even-or-odd-number)

---

### **Exercise 1: Login Script**

#### **Description**

- Prompts the user for a username and password.
- Validates the input against predefined credentials.
- Displays whether the login attempt was successful or not.

#### **Solution**

```bash
#!/bin/bash

# Recorded username and password
recorded_user="admin"
recorded_pass="password123"

# Prompt the user for input
read -p "Enter username: " username
read -sp "Enter password: " password
echo

# Check the username and password
if [[ "$username" == "$recorded_user" && "$password" == "$recorded_pass" ]]; then
    echo "Login successful!"
else
    echo "Login failed!"
fi
```

---

### **Exercise 2: Simple Calculator**

#### **Description**

- Asks the user for two numbers and an operator.
- Performs the calculation and displays the result.
- Supports basic operators: `+`, `-`, `*`, `/`.

#### **Solution**

```bash
#!/bin/bash

# Prompt the user for two numbers and an operator
read -p "Enter the first number: " num1
read -p "Enter the second number: " num2
read -p "Enter the operator (+, -, *, /): " operator

# Perform the calculation
case $operator in
    +) result=$((num1 + num2)) ;;
    -) result=$((num1 - num2)) ;;
    *) result=$((num1 * num2)) ;;
    /) result=$((num1 / num2)) ;;
    *) echo "Invalid operator!" && exit 1 ;;
esac

# Display the result
echo "Result: $result"
```

---

### **Exercise 3: File Existence Check**

#### **Description**

- Prompts the user for a file name.
- Checks if the file exists and notifies the user.

#### **Solution**

```bash
#!/bin/bash

# Ask the user for a file name
read -p "Enter the file name: " filename

# Check if the file exists
if [[ -e "$filename" ]]; then
    echo "File exists."
else
    echo "File does not exist."
fi
```

---

### **Exercise 4: Line Count in a File**

#### **Description**

- Prompts the user for a file name.
- Checks if the file exists and counts the number of lines in it.
- If the file does not exist, notifies the user.

#### **Solution**

```bash
#!/bin/bash

# Ask the user for a file name
read -p "Enter the file name: " filename

# Check if the file exists
if [[ -e "$filename" ]]; then
    line_count=$(wc -l < "$filename")
    echo "The file has $line_count lines."
else
    echo "File does not exist."
fi
```

---

### **Exercise 5: Even or Odd Number**

#### **Description**

- Prompts the user to input a number.
- Determines whether the number is even or odd.
- Displays the result.

#### **Solution**

```bash
#!/bin/bash

# Ask the user for a number
read -p "Enter a number: " number

# Check if the number is even or odd
if (( number % 2 == 0 )); then
    echo "The number is even."
else
    echo "The number is odd."
fi
```

---

### **How to Run These Scripts**

1. Save each script to a file, e.g., `exercise1.sh`.
2. Make the script executable:
   ```bash
   chmod +x exercise1.sh
   ```
3. Run the script:
   ```bash
   ./exercise1.sh
   ```

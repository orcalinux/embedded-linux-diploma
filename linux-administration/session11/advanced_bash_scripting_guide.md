# Advanced Bash Scripting Guide

## Table of Contents

- [Advanced Bash Scripting Guide](#advanced-bash-scripting-guide)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction](#1-introduction)
  - [2. Advanced Functions in Bash](#2-advanced-functions-in-bash)
    - [2.1 Defining Functions with Arguments](#21-defining-functions-with-arguments)
    - [2.2 Using Local Variables](#22-using-local-variables)
    - [2.3 Returning Values from Functions](#23-returning-values-from-functions)
    - [2.4 Function Documentation](#24-function-documentation)
    - [2.5 Error Handling in Functions](#25-error-handling-in-functions)
  - [3. Pattern Matching and Substitution in Bash](#3-pattern-matching-and-substitution-in-bash)
    - [3.1 Using Globbing Patterns](#31-using-globbing-patterns)
    - [3.2 Parameter Expansion with Patterns](#32-parameter-expansion-with-patterns)
    - [3.3 Using `[[` with Patterns](#33-using--with-patterns)
  - [4. The `read` Command in Bash](#4-the-read-command-in-bash)
    - [4.1 Syntax](#41-syntax)
    - [4.2 Options and Examples](#42-options-and-examples)
      - [4.2.1 `-a array`](#421--a-array)
      - [4.2.2 `-d delim`](#422--d-delim)
      - [4.2.3 `-e`](#423--e)
      - [4.2.4 `-i text`](#424--i-text)
      - [4.2.5 `-n nchars`](#425--n-nchars)
      - [4.2.6 `-N nchars`](#426--n-nchars)
      - [4.2.7 `-p prompt`](#427--p-prompt)
      - [4.2.8 `-r`](#428--r)
      - [4.2.9 `-s`](#429--s)
      - [4.2.10 `-t timeout`](#4210--t-timeout)
      - [4.2.11 `-u fd`](#4211--u-fd)
    - [4.3 Exit Status](#43-exit-status)
  - [5. Demos and Examples](#5-demos-and-examples)
    - [5.1 Advanced Functions Example](#51-advanced-functions-example)
    - [5.2 Pattern Matching and Substitution Example](#52-pattern-matching-and-substitution-example)
    - [5.3 Using `read` with Various Options Example](#53-using-read-with-various-options-example)
  - [6. Demos and Examples](#6-demos-and-examples)
    - [6.1 Advanced Functions Example](#61-advanced-functions-example)
    - [6.2 Pattern Matching and Substitution Example](#62-pattern-matching-and-substitution-example)
    - [5.3 Using `read` with Various Options Example](#53-using-read-with-various-options-example-1)
  - [6. Conclusion](#6-conclusion)
  - [7. References](#7-references)

---

## 1. Introduction

Bash scripting is an indispensable tool for automating tasks, managing system operations, and enhancing productivity in Unix-like environments. While basic Bash commands and scripts are widely used, mastering advanced scripting techniques can significantly elevate your scripts' efficiency, flexibility, and maintainability. This guide delves into advanced Bash scripting concepts, including sophisticated function usage, pattern matching and substitution, and comprehensive utilization of the `read` command with its extensive options. Through detailed explanations and practical examples, you'll gain the skills needed to write powerful and robust Bash scripts.

---

## 2. Advanced Functions in Bash

Functions in Bash allow you to encapsulate reusable blocks of code, making scripts more organized and maintainable. Advanced usage of functions includes handling arguments, using local variables, returning values, documenting functions, and implementing robust error handling.

### 2.1 Defining Functions with Arguments

Functions can accept arguments, enabling dynamic and flexible code execution.

**Example:**

```bash
#!/bin/bash

# Function to greet a user
greet() {
    local name="$1"
    local time_of_day="$2"
    echo "Good $time_of_day, $name!"
}

# Usage
greet "Alice" "morning"
# Output: Good morning, Alice!
```

**Explanation:**

-   `greet` is a function that takes two arguments: `name` and `time_of_day`.
-   Arguments are accessed within the function using `$1`, `$2`, etc.

### 2.2 Using Local Variables

Using local variables within functions prevents variable name conflicts and ensures that variables are scoped appropriately.

**Example:**

```bash
#!/bin/bash

# Function to calculate the sum of two numbers
calculate_sum() {
    local num1="$1"
    local num2="$2"
    local sum=$((num1 + num2))
    echo "$sum"
}

# Usage
result=$(calculate_sum 5 10)
echo "Sum is: $result"
# Output: Sum is: 15
```

**Explanation:**

-   The `local` keyword confines `num1`, `num2`, and `sum` within the function scope.
-   This prevents these variables from affecting or being affected by variables outside the function.

### 2.3 Returning Values from Functions

Bash functions cannot return complex data structures, but you can use `echo` or set global variables to return values.

**Example Using `echo`:**

```bash
#!/bin/bash

# Function to multiply two numbers
multiply() {
    local a="$1"
    local b="$2"
    echo $((a * b))
}

# Usage
product=$(multiply 4 5)
echo "Product is: $product"
# Output: Product is: 20
```

**Example Using Global Variables:**

```bash
#!/bin/bash

# Function to multiply two numbers and set a global variable
multiply() {
    local a="$1"
    local b="$2"
    result=$((a * b))
}

# Usage
multiply 4 5
echo "Product is: $result"
# Output: Product is: 20
```

**Note:** Using `echo` is generally safer to avoid unintended side effects from global variables.

### 2.4 Function Documentation

Documenting functions enhances readability and maintainability, especially in larger scripts.

**Example:**

```bash
#!/bin/bash

# Function: backup_files
# Description: Creates a backup of specified files.
# Arguments:
#   $1 - Source directory
#   $2 - Backup directory
backup_files() {
    local src_dir="$1"
    local backup_dir="$2"

    if [[ ! -d "$src_dir" ]]; then
        echo "Source directory does not exist."
        return 1
    fi

    mkdir -p "$backup_dir"
    cp -r "$src_dir"/* "$backup_dir"/
    echo "Backup completed successfully."
}

# Usage
backup_files "/home/user/documents" "/home/user/backup/documents_backup"
```

**Explanation:**

-   Comments before the function provide a clear description of its purpose, arguments, and behavior.
-   This practice is crucial for maintaining clarity in complex scripts.

### 2.5 Error Handling in Functions

Implementing error handling ensures that functions behave predictably and provide meaningful feedback in case of failures.

**Example:**

```bash
#!/bin/bash

# Function: create_directory
# Description: Creates a directory if it doesn't exist.
# Arguments:
#   $1 - Directory path
create_directory() {
    local dir_path="$1"

    if [[ -d "$dir_path" ]]; then
        echo "Directory '$dir_path' already exists."
        return 0
    fi

    mkdir -p "$dir_path"
    if [[ $? -ne 0 ]]; then
        echo "Failed to create directory '$dir_path'."
        return 1
    fi

    echo "Directory '$dir_path' created successfully."
    return 0
}

# Usage
create_directory "/home/user/new_folder"
```

**Explanation:**

-   Checks if the directory exists before attempting to create it.
-   Uses `$?` to check the exit status of the `mkdir` command.
-   Returns appropriate status codes and messages based on success or failure.

---

## 3. Pattern Matching and Substitution in Bash

Pattern matching and substitution are powerful features in Bash that allow for flexible and efficient text processing. They are essential for tasks like file manipulation, string parsing, and conditional operations.

### 3.1 Using Globbing Patterns

Globbing patterns allow you to match filenames and strings based on wildcard characters.

**Common Globbing Wildcards:**

-   `*`: Matches any number of characters (including zero).
-   `?`: Matches exactly one character.
-   `[abc]`: Matches any one character inside the brackets.
-   `[a-z]`: Matches any one character in the specified range.
-   `{a,b}`: Matches either `a` or `b`.

**Example:**

```bash
#!/bin/bash

# List all .md files
echo "Markdown files:"
for file in *.md; do
    echo "$file"
done
```

**Explanation:**

-   `*.md` matches all files ending with `.md`.
-   This is useful for operations like listing, moving, or deleting specific types of files.

### 3.2 Parameter Expansion with Patterns

Bash's parameter expansion allows for advanced string manipulation using patterns.

**Syntax:**

```bash
${variable/pattern/replacement}
```

**Example:**

```bash
#!/bin/bash

filename="document_backup_2023.md"

# Remove the suffix '_backup_2023.md'
base=${filename/_backup_2023.md/}
echo "Base filename: $base"
# Output: Base filename: document
```

**Using `%` and `%%` for Suffix Removal:**

-   `${variable%pattern}`: Removes the shortest match of `pattern` from the end.
-   `${variable%%pattern}`: Removes the longest match of `pattern` from the end.

**Example:**

```bash
#!/bin/bash

filename="report_final_draft.docx"

# Remove the shortest match '_draft.docx' from the end
short=${filename%_draft.docx}
echo "$short"
# Output: report_final

# Remove the longest match '_final_draft.docx' from the end
long=${filename%%_final_draft.docx}
echo "$long"
# Output: report
```

**Explanation:**

-   `%` and `%%` are used to remove suffixes based on patterns.
-   Useful for extracting base filenames or modifying strings dynamically.

### 3.3 Using `[[` with Patterns

The `[[` conditional expression allows for pattern matching using `=~` and other operators.

**Example:**

```bash
#!/bin/bash

read -p "Enter your email: " email

if [[ "$email" =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-z]{2,}$ ]]; then
    echo "Valid email."
else
    echo "Invalid email."
fi
```

**Explanation:**

-   `=~` is used for regex matching.
-   Allows complex pattern matching within conditional statements.

**Using `==` with Wildcards:**

```bash
#!/bin/bash

read -p "Enter a filename: " filename

if [[ "$filename" == *.sh ]]; then
    echo "This is a shell script."
else
    echo "This is not a shell script."
fi
```

**Explanation:**

-   Checks if the `filename` ends with `.sh`.
-   Uses globbing patterns within the `[[` expression.

---

## 4. The `read` Command in Bash

The `read` command is a built-in Bash utility for reading input from users or other sources. It is highly versatile, with numerous options to control its behavior. Mastery of `read` enhances your ability to interact with users, process data, and control script flow.

### 4.1 Syntax

```bash
read [options] [name ...]
```

-   **Options**: Modify the behavior of the `read` command.
-   **name...**: Variables to store the input.

### 4.2 Options and Examples

Below is a comprehensive breakdown of each `read` option, accompanied by examples and explanations.

#### 4.2.1 `-a array`

**Description:**

Assigns the words read to sequential indices of the array variable `ARRAY`, starting at zero.

**Example:**

```bash
#!/bin/bash

echo "Enter some fruits separated by space:"
read -a fruits
echo "Fruits array: ${fruits[@]}"
echo "First fruit: ${fruits[0]}"
echo "Second fruit: ${fruits[1]}"
```

**Usage:**

```
Enter some fruits separated by space:
apple banana cherry
Fruits array: apple banana cherry
First fruit: apple
Second fruit: banana
```

**Explanation:**

-   `-a fruits` assigns each word to an element in the `fruits` array.
-   Access array elements using `${fruits[index]}`.

#### 4.2.2 `-d delim`

**Description:**

Continues reading until the first character of `delim` is read, instead of waiting for a newline.

**Example:**

```bash
#!/bin/bash

echo "Enter input terminated by comma:"
read -d ',' input
echo "You entered: $input"
```

**Usage:**

```
Enter input terminated by comma:
hello,world
You entered: hello
```

**Explanation:**

-   The `read` command stops reading after encountering the delimiter `,`.
-   Useful for parsing input with custom delimiters.

#### 4.2.3 `-e`

**Description:**

Uses Readline to obtain the line, enabling features like line editing and history.

**Example:**

```bash
#!/bin/bash

read -e -p "Enter your name: " name
echo "Hello, $name!"
```

**Usage:**

```
Enter your name: [User can use arrow keys to edit]
Hello, Alice!
```

**Explanation:**

-   `-e` allows the user to navigate and edit the input using arrow keys.
-   Enhances user experience by providing interactive input capabilities.

#### 4.2.4 `-i text`

**Description:**

Uses `text` as the initial text for Readline. Only works when `-e` is also used.

**Example:**

```bash
#!/bin/bash

read -e -i "John Doe" -p "Enter your name: " name
echo "Hello, $name!"
```

**Usage:**

```
Enter your name: John Doe
Hello, John Doe!
```

**Explanation:**

-   The input field is pre-filled with "John Doe".
-   Users can accept the default or modify it as needed.

#### 4.2.5 `-n nchars`

**Description:**

Returns after reading `nchars` characters rather than waiting for a newline, but honors a delimiter if fewer than `nchars` characters are read before the delimiter.

**Example:**

```bash
#!/bin/bash

echo "Press any 3 keys:"
read -n 3 keys
echo
echo "You pressed: $keys"
```

**Usage:**

```
Press any 3 keys:
abc
You pressed: abc
```

**Explanation:**

-   `-n 3` reads exactly three characters without waiting for the Enter key.
-   Useful for capturing short inputs or single-character responses.

#### 4.2.6 `-N nchars`

**Description:**

Returns only after reading exactly `nchars` characters, unless EOF is encountered or read times out, ignoring any delimiter.

**Example:**

```bash
#!/bin/bash

echo "Enter exactly 4 characters:"
read -N 4 code
echo
echo "Your code is: $code"
```

**Usage:**

```
Enter exactly 4 characters:
abcd
Your code is: abcd
```

**Explanation:**

-   Forces the user to input exactly four characters.
-   The script proceeds once the specified number of characters is read.

#### 4.2.7 `-p prompt`

**Description:**

Outputs the string `prompt` without a trailing newline before attempting to read.

**Example:**

```bash
#!/bin/bash

read -p "Enter your favorite color: " color
echo "Your favorite color is: $color"
```

**Usage:**

```
Enter your favorite color: Blue
Your favorite color is: Blue
```

**Explanation:**

-   Displays "Enter your favorite color: " and waits for user input on the same line.
-   Enhances readability by combining prompt and input seamlessly.

#### 4.2.8 `-r`

**Description:**

Does not allow backslashes to escape any characters.

**Example:**

```bash
#!/bin/bash

echo "Enter a path with backslashes:"
read -r path
echo "You entered: $path"
```

**Usage:**

```
Enter a path with backslashes:
C:\Program Files\Test
You entered: C:\Program Files\Test
```

**Explanation:**

-   Backslashes are treated as literal characters, not escape characters.
-   Prevents unexpected behavior when reading paths or strings containing backslashes.

#### 4.2.9 `-s`

**Description:**

Does not echo input coming from a terminal (useful for passwords).

**Example:**

```bash
#!/bin/bash

read -s -p "Enter your password: " password
echo
echo "Password has been set."
```

**Usage:**

```
Enter your password:
Password has been set.
```

**Explanation:**

-   The password input is hidden from the terminal display.
-   Enhances security by preventing shoulder surfing or accidental disclosure.

#### 4.2.10 `-t timeout`

**Description:**

Times out and returns failure if a complete line of input is not read within `timeout` seconds. The exit status is greater than 128 if the timeout is exceeded.

**Example:**

```bash
#!/bin/bash

read -t 5 -p "Enter your name within 5 seconds: " name
if [[ $? -eq 0 ]]; then
    echo "Hello, $name!"
else
    echo "Timed out waiting for input."
fi
```

**Usage:**

```
Enter your name within 5 seconds: Alice
Hello, Alice!
```

Or, if the user does not enter within 5 seconds:

```
Enter your name within 5 seconds:
Timed out waiting for input.
```

**Explanation:**

-   `-t 5` sets a 5-second timeout for the input.
-   Useful for scenarios where timely responses are critical.

#### 4.2.11 `-u fd`

**Description:**

Reads from file descriptor `fd` instead of the standard input.

**Example:**

```bash
#!/bin/bash

exec 3< input.txt
read -u 3 first_line
echo "First line from file descriptor 3: $first_line"
exec 3<&-
```

**Usage:**

Assuming `input.txt` contains:

```
Hello, World!
This is a test.
```

Running the script will output:

```
First line from file descriptor 3: Hello, World!
```

**Explanation:**

-   `exec 3< input.txt` opens `input.txt` for reading on file descriptor 3.
-   `read -u 3 first_line` reads from file descriptor 3 instead of standard input.
-   Useful for reading from files or other input streams within scripts.

### 4.3 Exit Status

The `read` command returns an exit status based on the outcome of the read operation:

-   **`0`**: Success. The input was successfully read.
-   **`>128`**: Timeout exceeded (`-t` option). The specified timeout was reached without completing the read.
-   **Non-zero**: Various errors, such as invalid file descriptors with `-u`.

**Example:**

```bash
#!/bin/bash

read -t 2 -p "Enter your username within 2 seconds: " username
if [[ $? -eq 0 ]]; then
    echo "Username: $username"
elif [[ $? -gt 128 ]]; then
    echo "Timed out waiting for username."
else
    echo "An error occurred."
fi
```

**Usage:**

-   If the user inputs within 2 seconds, it echoes the input.
-   If not, it notifies about the timeout.

**Sample Output:**

```
Enter your username within 2 seconds: alice
Username: alice
```

Or, if the user does not enter within 2 seconds:

```
Enter your username within 2 seconds:
Timed out waiting for username.
```

---

## 5. Demos and Examples

This section provides practical demonstrations of advanced Bash scripting features, including functions, pattern matching and substitution, and the `read` command with various options.

### 5.1 Advanced Functions Example

**Script: `advanced_functions_demo.sh`**

```bash
#!/bin/bash

# Function: calculate_statistics
# Description: Calculates the sum and average of an array of numbers.
# Arguments:
#   $@ - List of numbers
# Returns:
#   Sum and average

calculate_statistics() {
    local numbers=("$@")
    local sum=0
    local count=${#numbers[@]}

    for num in "${numbers[@]}"; do
        sum=$((sum + num))
    done

    if [[ $count -gt 0 ]]; then
        local average=$(echo "scale=2; $sum / $count" | bc)
        echo "Sum: $sum"
        echo "Average: $average"
    else
        echo "No numbers provided."
    fi
}

# Function: find_max_min
# Description: Finds the maximum and minimum in an array of numbers.
# Arguments:
#   $@ - List of numbers
# Returns:
#   Maximum and minimum

find_max_min() {
    local numbers=("$@")
    local max min

    if [[ ${#numbers[@]} -eq 0 ]]; then
        echo "No numbers provided."
        return 1
    fi

    max=${numbers[0]}
    min=${numbers[0]}

    for num in "${numbers[@]}"; do
        if (( num > max )); then
            max=$num
        fi
        if (( num < min )); then
            min=$num
        fi
    done

    echo "Maximum: $max"
    echo "Minimum: $min"
}

# Usage
echo "Enter numbers separated by space:"
read -a nums

calculate_statistics "${nums[@]}"
find_max_min "${nums[@]}"
```

**Explanation:**

-   **`calculate_statistics`**: Computes the sum and average of provided numbers.
-   **`find_max_min`**: Identifies the maximum and minimum values in the provided numbers.
-   **Usage**: The script prompts the user to enter numbers, reads them into an array, and then calls the functions to process the data.

**Running the Script:**

```bash
$ chmod +x advanced_functions_demo.sh
$ ./advanced_functions_demo.sh
Enter numbers separated by space:
10 20 30 40 50
Sum: 150
Average: 30.00
Maximum: 50
Minimum: 10
```

### 5.2 Pattern Matching and Substitution Example

**Script: `pattern_matching_demo.sh`**

```bash
#!/bin/bash

# Function: rename_files
# Description: Renames all .txt files in a directory by adding a prefix.
# Arguments:
#   $1 - Directory path
#   $2 - Prefix to add
rename_files() {
    local dir="$1"
    local prefix="$2"

    if [[ ! -d "$dir" ]]; then
        echo "Directory '$dir' does not exist."
        return 1
    fi

    for file in "$dir"/*.txt; do
        if [[ -f "$file" ]]; then
            local base=$(basename "$file" .txt)
            local new_file="$dir/${prefix}${base}.txt"
            mv "$file" "$new_file"
            echo "Renamed '$file' to '$new_file'"
        fi
    done
}

# Function: extract_extension
# Description: Extracts the file extension from a filename.
# Arguments:
#   $1 - Filename
extract_extension() {
    local filename="$1"
    echo "${filename##*.}"
}

# Function: replace_extension
# Description: Replaces the extension of a filename.
# Arguments:
#   $1 - Filename
#   $2 - New extension
replace_extension() {
    local filename="$1"
    local new_ext="$2"
    echo "${filename%.*}.$new_ext"
}

# Usage
echo "---- Renaming Files Example ----"
mkdir -p sample_dir
touch sample_dir/file1.txt sample_dir/file2.txt sample_dir/file3.md
rename_files "sample_dir" "new_"

echo "---- Extract Extension Example ----"
filename="archive.tar.gz"
extension=$(extract_extension "$filename")
echo "The extension of '$filename' is: $extension"
# Output: The extension of 'archive.tar.gz' is: gz

echo "---- Replace Extension Example ----"
new_filename=$(replace_extension "document.txt" "md")
echo "Replaced filename: $new_filename"
# Output: Replaced filename: document.md

# Cleanup
rm -rf sample_dir
```

**Explanation:**

-   **`rename_files`**: Uses pattern matching to select `.txt` files and renames them by adding a prefix.
-   **`extract_extension`**: Demonstrates parameter expansion to extract the file extension.
-   **`replace_extension`**: Shows how to replace a file's extension using parameter expansion.
-   **Usage**: The script creates a sample directory with files, renames them, extracts extensions, and replaces extensions.

**Running the Script:**

```bash
$ chmod +x pattern_matching_demo.sh
$ ./pattern_matching_demo.sh
---- Renaming Files Example ----
Renamed 'sample_dir/file1.txt' to 'sample_dir/new_file1.txt'
Renamed 'sample_dir/file2.txt' to 'sample_dir/new_file2.txt'
---- Extract Extension Example ----
The extension of 'archive.tar.gz' is: gz
---- Replace Extension Example ----
Replaced filename: document.md
```

### 5.3 Using `read` with Various Options Example

**Script: `read_options_demo.sh`**

```bash
#!/bin/bash

# Demonstrating various read options

# 4.2.1 -a array
echo "---- Example: -a array ----"
echo "Enter some colors separated by space:"
read -a colors
echo "Colors array: ${colors[@]}"
echo "First color: ${colors[0]}"
echo "Second color: ${colors[1]}"
echo

# 4.2.2 -d delim
echo "---- Example: -d delim ----"
echo "Enter a sentence terminated by a semicolon (';'):"
read -d ';' sentence
echo "You entered: $sentence"
echo

# 4.2.3 -e and -i text
echo "---- Example: -e and -i text ----"
read -e -i "DefaultUser" -p "Enter your username: " username
echo "Username set to: $username"
echo

# 4.2.4 -n nchars
echo "---- Example: -n nchars ----"
echo "Press any 2 keys:"
read -n 2 keys
echo
echo "You pressed: $keys"
echo

# 4.2.5 -N nchars
echo "---- Example: -N nchars ----"
echo "Enter exactly 3 characters:"
read -N 3 code
echo
echo "Your code is: $code"
echo

# 4.2.6 -p prompt
echo "---- Example: -p prompt ----"
read -p "Enter your favorite programming language: " language
echo "Your favorite programming language is: $language"
echo

# 4.2.7 -r
echo "---- Example: -r ----"
echo "Enter a file path with backslashes:"
read -r filepath
echo "You entered: $filepath"
echo

# 4.2.8 -s
echo "---- Example: -s ----"
read -s -p "Enter your API key: " api_key
echo
echo "API key has been set."
echo

# 4.2.9 -t timeout
echo "---- Example: -t timeout ----"
read -t 3 -p "Enter your email within 3 seconds: " email
if [[ $? -eq 0 ]]; then
    echo "Email: $email"
else
    echo "Timed out waiting for email."
fi
echo

# 4.2.10 -u fd
echo "---- Example: -u fd ----"
echo "Creating a temporary file with content:"
echo -e "First Line\nSecond Line\nThird Line" > temp_input.txt

exec 4< temp_input.txt
read -u 4 first_line
echo "First line from file descriptor 4: $first_line"
exec 4<&-
rm temp_input.txt
```

**Explanation:**

This script demonstrates how to use various `read` command options with different scenarios.

**Running the Script:**

```bash
$ chmod +x read_options_demo.sh
$ ./read_options_demo.sh
```

**Sample Output:**

```
---- Example: -a array ----
Enter some colors separated by space:
red green blue
Colors array: red green blue
First color: red
Second color: green

---- Example: -d delim ----
Enter a sentence terminated by a semicolon (';'):
This is a test sentence; How are you?
You entered: This is a test sentence

---- Example: -e and -i text ----
Enter your username: DefaultUser
Username set to: DefaultUser

---- Example: -n nchars ----
Press any 2 keys:
ab
You pressed: ab

---- Example: -N nchars ----
Enter exactly 3 characters:
xyz
Your code is: xyz

---- Example: -p prompt ----
Enter your favorite programming language: Python
Your favorite programming language is: Python

---- Example: -r ----
Enter a file path with backslashes:
C:\Program Files\Test
You entered: C:\Program Files\Test

---- Example: -s ----
Enter your API key:
API key has been set.

---- Example: -t timeout ----
Enter your email within 3 seconds:
Timed out waiting for email.

---- Example: -u fd ----
Creating a temporary file with content:
First line from file descriptor 4: First Line
```

**Explanation:**

-   **`-a array`**: Captures multiple inputs into an array.
-   **`-d delim`**: Reads input until a specified delimiter.
-   **`-e and -i text`**: Provides editable input with a default value.
-   **`-n nchars`**: Reads a fixed number of characters without waiting for Enter.
-   **`-N nchars`**: Forces reading exactly a specified number of characters.
-   **`-p prompt`**: Displays a prompt before reading input.
-   **`-r`**: Reads input literally, preserving backslashes.
-   **`-s`**: Hides input (useful for sensitive data).
-   **`-t timeout`**: Times out after a specified duration if no input is received.
-   **`-u fd`**: Reads input from a specified file descriptor.

---

## 6. Demos and Examples

This section provides detailed demonstrations of advanced Bash scripting features, including functions, pattern matching and substitution, and the `read` command with various options.

### 6.1 Advanced Functions Example

**Script: `advanced_functions_demo.sh`**

```bash
#!/bin/bash

# Function: calculate_area
# Description: Calculates the area of a circle given its radius.
# Arguments:
#   $1 - Radius of the circle
# Returns:
#   Area of the circle

calculate_area() {
    local radius="$1"
    local pi=3.14159
    local area=$(echo "$pi * $radius * $radius" | bc)
    echo "$area"
}

# Function: greet_user
# Description: Greets the user with their name and the current time of day.
# Arguments:
#   $1 - User's name
greet_user() {
    local name="$1"
    local hour=$(date +"%H")
    local time_of_day

    if (( hour < 12 )); then
        time_of_day="morning"
    elif (( hour < 18 )); then
        time_of_day="afternoon"
    else
        time_of_day="evening"
    fi

    echo "Good $time_of_day, $name!"
}

# Usage
echo "Enter the radius of the circle:"
read -r radius
area=$(calculate_area "$radius")
echo "The area of the circle is: $area"

echo "Enter your name:"
read -r name
greet_user "$name"
```

**Explanation:**

-   **`calculate_area`**: Computes the area using the radius provided.
-   **`greet_user`**: Greets the user based on the current time of day.
-   **Usage**: The script prompts the user to enter the radius and their name, then uses the functions to process and display the results.

**Running the Script:**

```bash
$ chmod +x advanced_functions_demo.sh
$ ./advanced_functions_demo.sh
Enter the radius of the circle:
5
The area of the circle is: 78.53975
Enter your name:
Alice
Good afternoon, Alice!
```

### 6.2 Pattern Matching and Substitution Example

**Script: `pattern_matching_demo.sh`**

```bash
#!/bin/bash

# Function: rename_files
# Description: Renames all .txt files in a directory by adding a prefix.
# Arguments:
#   $1 - Directory path
#   $2 - Prefix to add
rename_files() {
    local dir="$1"
    local prefix="$2"

    if [[ ! -d "$dir" ]]; then
        echo "Directory '$dir' does not exist."
        return 1
    fi

    for file in "$dir"/*.txt; do
        if [[ -f "$file" ]]; then
            local base=$(basename "$file" .txt)
            local new_file="$dir/${prefix}${base}.txt"
            mv "$file" "$new_file"
            echo "Renamed '$file' to '$new_file'"
        fi
    done
}

# Function: extract_extension
# Description: Extracts the file extension from a filename.
# Arguments:
#   $1 - Filename
extract_extension() {
    local filename="$1"
    echo "${filename##*.}"
}

# Function: replace_extension
# Description: Replaces the extension of a filename.
# Arguments:
#   $1 - Filename
#   $2 - New extension
replace_extension() {
    local filename="$1"
    local new_ext="$2"
    echo "${filename%.*}.$new_ext"
}

# Usage
echo "---- Renaming Files Example ----"
mkdir -p sample_dir
touch sample_dir/file1.txt sample_dir/file2.txt sample_dir/file3.md
rename_files "sample_dir" "new_"

echo "---- Extract Extension Example ----"
filename="archive.tar.gz"
extension=$(extract_extension "$filename")
echo "The extension of '$filename' is: $extension"
# Output: The extension of 'archive.tar.gz' is: gz

echo "---- Replace Extension Example ----"
new_filename=$(replace_extension "document.txt" "md")
echo "Replaced filename: $new_filename"
# Output: Replaced filename: document.md

# Cleanup
rm -rf sample_dir
```

**Explanation:**

-   **`rename_files`**: Uses pattern matching to select `.txt` files and renames them by adding a prefix.
-   **`extract_extension`**: Demonstrates parameter expansion to extract the file extension.
-   **`replace_extension`**: Shows how to replace a file's extension using parameter expansion.
-   **Usage**: The script creates a sample directory with files, renames them, extracts extensions, and replaces extensions.

**Running the Script:**

```bash
$ chmod +x pattern_matching_demo.sh
$ ./pattern_matching_demo.sh
---- Renaming Files Example ----
Renamed 'sample_dir/file1.txt' to 'sample_dir/new_file1.txt'
Renamed 'sample_dir/file2.txt' to 'sample_dir/new_file2.txt'
---- Extract Extension Example ----
The extension of 'archive.tar.gz' is: gz
---- Replace Extension Example ----
Replaced filename: document.md
```

### 5.3 Using `read` with Various Options Example

**Script: `read_options_demo.sh`**

```bash
#!/bin/bash

# Demonstrating various read options

# 4.2.1 -a array
echo "---- Example: -a array ----"
echo "Enter some colors separated by space:"
read -a colors
echo "Colors array: ${colors[@]}"
echo "First color: ${colors[0]}"
echo "Second color: ${colors[1]}"
echo

# 4.2.2 -d delim
echo "---- Example: -d delim ----"
echo "Enter a sentence terminated by a semicolon (';'):"
read -d ';' sentence
echo "You entered: $sentence"
echo

# 4.2.3 -e and -i text
echo "---- Example: -e and -i text ----"
read -e -i "DefaultUser" -p "Enter your username: " username
echo "Username set to: $username"
echo

# 4.2.4 -n nchars
echo "---- Example: -n nchars ----"
echo "Press any 2 keys:"
read -n 2 keys
echo
echo "You pressed: $keys"
echo

# 4.2.5 -N nchars
echo "---- Example: -N nchars ----"
echo "Enter exactly 3 characters:"
read -N 3 code
echo
echo "Your code is: $code"
echo

# 4.2.6 -p prompt
echo "---- Example: -p prompt ----"
read -p "Enter your favorite programming language: " language
echo "Your favorite programming language is: $language"
echo

# 4.2.7 -r
echo "---- Example: -r ----"
echo "Enter a file path with backslashes:"
read -r filepath
echo "You entered: $filepath"
echo

# 4.2.8 -s
echo "---- Example: -s ----"
read -s -p "Enter your API key: " api_key
echo
echo "API key has been set."
echo

# 4.2.9 -t timeout
echo "---- Example: -t timeout ----"
read -t 3 -p "Enter your email within 3 seconds: " email
if [[ $? -eq 0 ]]; then
    echo "Email: $email"
else
    echo "Timed out waiting for email."
fi
echo

# 4.2.10 -u fd
echo "---- Example: -u fd ----"
echo "Creating a temporary file with content:"
echo -e "First Line\nSecond Line\nThird Line" > temp_input.txt

exec 4< temp_input.txt
read -u 4 first_line
echo "First line from file descriptor 4: $first_line"
exec 4<&-
rm temp_input.txt
```

**Explanation:**

This script demonstrates how to use various `read` command options with different scenarios.

**Running the Script:**

```bash
$ chmod +x read_options_demo.sh
$ ./read_options_demo.sh
```

**Sample Output:**

```
---- Example: -a array ----
Enter some colors separated by space:
red green blue
Colors array: red green blue
First color: red
Second color: green

---- Example: -d delim ----
Enter a sentence terminated by a semicolon (';'):
This is a test sentence; How are you?
You entered: This is a test sentence

---- Example: -e and -i text ----
Enter your username: DefaultUser
Username set to: DefaultUser

---- Example: -n nchars ----
Press any 2 keys:
ab
You pressed: ab

---- Example: -N nchars ----
Enter exactly 3 characters:
xyz
Your code is: xyz

---- Example: -p prompt ----
Enter your favorite programming language: Python
Your favorite programming language is: Python

---- Example: -r ----
Enter a file path with backslashes:
C:\Program Files\Test
You entered: C:\Program Files\Test

---- Example: -s ----
Enter your API key:
API key has been set.

---- Example: -t timeout ----
Enter your email within 3 seconds:
Timed out waiting for email.

---- Example: -u fd ----
Creating a temporary file with content:
First line from file descriptor 4: First Line
```

**Explanation:**

-   **`-a array`**: Captures multiple inputs into an array.
-   **`-d delim`**: Reads input until a specified delimiter.
-   **`-e and -i text`**: Provides editable input with a default value.
-   **`-n nchars`**: Reads a fixed number of characters without waiting for Enter.
-   **`-N nchars`**: Forces reading exactly a specified number of characters.
-   **`-p prompt`**: Displays a prompt before reading input.
-   **`-r`**: Reads input literally, preserving backslashes.
-   **`-s`**: Hides input (useful for sensitive data).
-   **`-t timeout`**: Times out after a specified duration if no input is received.
-   **`-u fd`**: Reads input from a specified file descriptor.

---

## 6. Conclusion

Advanced Bash scripting empowers you to create more efficient, flexible, and maintainable scripts by leveraging sophisticated functions, pattern matching techniques, and comprehensive input handling. Understanding and utilizing these advanced features can significantly enhance your automation workflows, data processing tasks, and overall productivity in Unix-like environments.

This guide has provided detailed insights into advanced functions, pattern matching and substitution, and the versatile `read` command. By applying these concepts through practical examples and demos, you can elevate your Bash scripting skills to tackle complex tasks with ease.

---

## 7. References

1. **GNU Bash Manual**: [https://www.gnu.org/software/bash/manual/bash.html](https://www.gnu.org/software/bash/manual/bash.html)
2. **Advanced Bash-Scripting Guide** by Mendel Cooper: [https://tldp.org/LDP/abs/html/](https://tldp.org/LDP/abs/html/)
3. **Bash Pitfalls** by Various Authors: [https://mywiki.wooledge.org/BashPitfalls](https://mywiki.wooledge.org/BashPitfalls)
4. **The Art of Computer Programming** by Donald E. Knuth
5. **Effective Bash Scripting** by Peteris Krumins

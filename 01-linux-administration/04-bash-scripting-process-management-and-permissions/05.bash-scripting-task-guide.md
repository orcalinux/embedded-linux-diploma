# Introduction to Bash Scripting - Task Guide

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Tasks](#tasks)
   - [Task 1: Hello World Script](#task-1-hello-world-script)
   - [Task 2: Simple File Backup](#task-2-simple-file-backup)
   - [Task 3: User Input-Based Calculator](#task-3-user-input-based-calculator)
4. [Resources](#resources)
5. [Conclusion](#conclusion)

---

## Introduction

Welcome to the **Introduction to Bash Scripting Task Guide**! This guide is designed to help you practice and reinforce your Bash scripting skills through three hands-on tasks. Whether you're a beginner looking to get started or someone with some experience aiming to solidify your knowledge, these tasks will provide practical experience with essential Bash concepts.

---

## Prerequisites

Before diving into the tasks, ensure you have the following:

- **Basic Understanding of the Command Line**: Familiarity with navigating directories, listing files, and executing basic commands.
- **Bash Installed**: Bash is typically pre-installed on most Unix-like systems (Linux, macOS). To verify, run:

  ```bash
  bash --version
  ```

- **Text Editor**: Use any text editor of your choice (e.g., `nano`, `vim`, `gedit`, VS Code).

---

## Tasks

### Task 1: Hello World Script

**Objective:** Create a simple Bash script that prints "Hello, World!" to the terminal.

**Steps:**

1. **Create the Script File:**

   Open your terminal and create a new file named `hello.sh` using your preferred text editor. For example, using `nano`:

   ```bash
   nano hello.sh
   ```

2. **Add the Following Content:**

   ```bash
   #!/bin/bash
   # This script prints "Hello, World!" to the terminal

   echo "Hello, World!"
   ```

3. **Save and Exit:**

   - If using `nano`, press `Ctrl + X`, then `Y`, and `Enter` to save.
   - For other editors, follow the respective save and exit commands.

4. **Make the Script Executable:**

   ```bash
   chmod +x hello.sh
   ```

5. **Run the Script:**

   ```bash
   ./hello.sh
   ```

**Expected Output:**

```
Hello, World!
```

**What You Learn:**

- Creating and editing Bash scripts.
- Using the `echo` command to output text.
- Making scripts executable.
- Running scripts from the terminal.

---

### Task 2: Simple File Backup

**Objective:** Develop a Bash script that backs up a specified directory by compressing it into a `.tar.gz` file with a timestamp.

**Steps:**

1. **Create the Script File:**

   ```bash
   nano backup.sh
   ```

2. **Add the Following Content:**

   ```bash
   #!/bin/bash
   # This script backs up a specified directory

   # Configuration
   SOURCE_DIR="$HOME/Documents"         # Directory to back up
   BACKUP_DIR="$HOME/Backups"           # Directory where backups are stored
   TIMESTAMP=$(date +"%Y%m%d%H%M%S")    # Current timestamp
   BACKUP_FILE="$BACKUP_DIR/backup_$TIMESTAMP.tar.gz"  # Backup file name

   # Create backup directory if it doesn't exist
   mkdir -p "$BACKUP_DIR"

   # Create the backup
   tar -czf "$BACKUP_FILE" "$SOURCE_DIR"

   # Verify backup creation
   if [ $? -eq 0 ]; then
       echo "Backup successful: $BACKUP_FILE"
   else
       echo "Backup failed."
       exit 1
   fi
   ```

3. **Customize the Script:**

   - **`SOURCE_DIR`**: Change this to the directory you want to back up.
   - **`BACKUP_DIR`**: Change this to where you want the backups to be stored.

4. **Save and Exit:**

   - For `nano`, press `Ctrl + X`, then `Y`, and `Enter`.

5. **Make the Script Executable:**

   ```bash
   chmod +x backup.sh
   ```

6. **Run the Script:**

   ```bash
   ./backup.sh
   ```

**Expected Output:**

```
Backup successful: /home/yourusername/Backups/backup_20240427123045.tar.gz
```

**What You Learn:**

- Using variables to store paths and dynamic data.
- Creating directories with `mkdir -p`.
- Compressing directories using `tar`.
- Conditional statements to verify command success.
- Generating timestamps for unique backup filenames.

---

### Task 3: User Input-Based Calculator

**Objective:** Create a Bash script that performs basic arithmetic operations (addition, subtraction, multiplication, division) based on user input.

**Steps:**

1. **Create the Script File:**

   ```bash
   nano calculator.sh
   ```

2. **Add the Following Content:**

   ```bash
   #!/bin/bash
   # This script performs basic arithmetic operations

   echo "Simple Calculator"
   echo "-----------------"

   # Prompt for the first number
   read -p "Enter the first number: " num1

   # Prompt for the second number
   read -p "Enter the second number: " num2

   # Prompt for the operation
   echo "Select an operation:"
   echo "1) Addition (+)"
   echo "2) Subtraction (-)"
   echo "3) Multiplication (*)"
   echo "4) Division (/)"
   read -p "Enter your choice (1-4): " choice

   # Perform the selected operation
   case $choice in
       1)
           result=$((num1 + num2))
           operation="+"
           ;;
       2)
           result=$((num1 - num2))
           operation="-"
           ;;
       3)
           result=$((num1 * num2))
           operation="*"
           ;;
       4)
           if [ "$num2" -ne 0 ]; then
               result=$((num1 / num2))
               operation="/"
           else
               echo "Error: Division by zero is not allowed."
               exit 1
           fi
           ;;
       *)
           echo "Invalid choice."
           exit 1
           ;;
   esac

   # Display the result
   echo "$num1 $operation $num2 = $result"
   ```

3. **Save and Exit:**

   - For `nano`, press `Ctrl + X`, then `Y`, and `Enter`.

4. **Make the Script Executable:**

   ```bash
   chmod +x calculator.sh
   ```

5. **Run the Script:**

   ```bash
   ./calculator.sh
   ```

**Sample Interaction:**

```
Simple Calculator
-----------------
Enter the first number: 15
Enter the second number: 5
Select an operation:
1) Addition (+)
2) Subtraction (-)
3) Multiplication (*)
4) Division (/)
Enter your choice (1-4): 4
15 / 5 = 3
```

**What You Learn:**

- Reading user input with `read`.
- Implementing menus and user choices.
- Using `case` statements for control flow.
- Performing arithmetic operations.
- Handling errors, such as division by zero.

---

## Resources

- **Books:**

  - _Learning the bash Shell_ by Cameron Newham
  - _Classic Shell Scripting_ by Arnold Robbins and Nelson H.F. Beebe

- **Online Documentation:**

  - [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)
  - [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)

- **Tutorials:**

  - [Bash Scripting Tutorial by Ryan Chadwick](https://ryanstutorials.net/bash-scripting-tutorial/)
  - [Shell Scripting Tutorial by TutorialsPoint](https://www.tutorialspoint.com/unix/shell_scripting.htm)

- **Tools:**
  - [ShellCheck](https://www.shellcheck.net/) - A static analysis tool for shell scripts.

---

## Conclusion

Congratulations on completing the **Introduction to Bash Scripting Task Guide**! Through these tasks, you've gained hands-on experience with fundamental Bash scripting concepts, including creating executable scripts, performing file operations, handling user input, and implementing control structures. Continue practicing by exploring more advanced topics and creating your own scripts to automate tasks and enhance your productivity.

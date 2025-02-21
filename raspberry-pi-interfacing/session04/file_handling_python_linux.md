# File Handling in Python on Linux

## Table of Contents

- [File Handling in Python on Linux](#file-handling-in-python-on-linux)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction](#1-introduction)
  - [2. Linux File Path Basics](#2-linux-file-path-basics)
  - [3. Opening and Closing Files in Python](#3-opening-and-closing-files-in-python)
  - [4. Common Python File Object Methods](#4-common-python-file-object-methods)
  - [5. Reading from Files](#5-reading-from-files)
  - [6. Writing to Files](#6-writing-to-files)
  - [7. Appending to Files](#7-appending-to-files)
  - [8. Using `with` Statement (Context Manager)](#8-using-with-statement-context-manager)
  - [9. Dummy Files with Example Content](#9-dummy-files-with-example-content)
  - [10. Example Code Snippets](#10-example-code-snippets)
    - [10.1 Reading Entire File](#101-reading-entire-file)
    - [10.2 Writing (Overwriting) a File](#102-writing-overwriting-a-file)
    - [10.3 Appending to a File](#103-appending-to-a-file)
    - [10.4 Reading Line by Line](#104-reading-line-by-line)
  - [11. Additional Tips](#11-additional-tips)
  - [12. References](#12-references)

---

## 1. Introduction

File handling is one of the most common tasks in programming. In Python, file operations (reading, writing, appending, etc.) are straightforward and consistent across different operating systems, including Linux. This README will guide you through fundamental file operations in Python, focusing on a Linux environment.

---

## 2. Linux File Path Basics

- **Path Separators**:  
  On Linux, directories are separated by a **forward slash** (`/`).

  - Example (absolute paths): `/home/user/documents/notes.txt`
  - Example (relative path): `./notes.txt` (relative to the current directory)

- **Absolute vs. Relative Paths**:
  - **Absolute path**: starts at the root (`/`), e.g., `/home/myuser/projects/script.py`.
  - **Relative path**: starts from the current working directory, e.g., if you’re in `/home/myuser/projects`, referencing `data/input.txt` would look for `input.txt` inside `projects/data`.

---

## 3. Opening and Closing Files in Python

The built-in function `open()` is used to open files:

```python
file_object = open("file_path", mode)
```

where:

- `file_path` is the path to your file (absolute or relative).
- `mode` is a string specifying how you want to open the file, such as:
  - `"r"`: Read (default)
  - `"w"`: Write (overwrites existing file or creates a new one)
  - `"a"`: Append (adds data to end of file or creates a new one)
  - `"r+"`: Read and write
  - Use `"b"` for binary mode (e.g., `"rb"`, `"wb"`).

After you finish working with the file, it’s good practice to close it:

```python
file_object.close()
```

This frees up system resources.

---

## 4. Common Python File Object Methods

Once a file is opened (e.g., `f = open("some_file.txt", "r")`), you get back a file object `f` that has several useful methods. Below is a **table** of commonly used methods:

| **Method**                  | **Description**                                                                                                                        | **Example**                            |
| --------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------- |
| `f.read(size=-1)`           | Reads up to `size` bytes (or characters in text mode). If `size` is `-1` or omitted, it reads the entire file.                         | `content = f.read()`                   |
| `f.readline(size=-1)`       | Reads a single line from the file. If `size` is provided, reads up to `size` characters.                                               | `line = f.readline()`                  |
| `f.readlines()`             | Reads the entire file into a list of lines.                                                                                            | `lines = f.readlines()`                |
| `f.write(string)`           | Writes `string` to the file. Only valid in write (`"w"`), append (`"a"`), or read-write (`"r+"`, `"w+"`, etc.) modes.                  | `f.write("Hello World!")`              |
| `f.writelines(list_of_str)` | Writes a list of strings to the file.                                                                                                  | `f.writelines(["Line1\n", "Line2\n"])` |
| `f.close()`                 | Closes the file.                                                                                                                       | `f.close()`                            |
| `f.flush()`                 | Forces the write buffer to be written to disk immediately.                                                                             | `f.flush()`                            |
| `f.tell()`                  | Returns the file object’s current position (in bytes from the start).                                                                  | `pos = f.tell()`                       |
| `f.seek(offset, whence=0)`  | Moves the file pointer to a given `offset`. `whence`=0 means from file start; 1 means from current position; 2 means from end of file. | `f.seek(0)  # Move to start of file`   |
| `f.truncate(size=None)`     | Resizes the file to `size` bytes. If `size` not specified, it truncates at the current file position.                                  | `f.truncate(100)`                      |

> **Notes**:
>
> - `read()`, `readline()`, and `readlines()` are only valid if the file is opened in a mode that supports reading (e.g., `"r"`, `"r+"`, `"w+"`, etc.).
> - `write()`, `writelines()`, and `truncate()` are only valid if the file is opened in a mode that supports writing (`"w"`, `"a"`, `"r+"`, etc.).

---

## 5. Reading from Files

Here are the common ways to read data:

1. **`read()`**: Reads the entire file (or up to `size` bytes).
2. **`readline()`**: Reads one line (including the newline) at a time.
3. **`readlines()`**: Reads the entire file into a list of lines.

Example:

```python
with open("example_file1.txt", "r") as f:
    content = f.read()       # Reads entire file
    # OR
    # line = f.readline()    # Reads a single line
    # lines = f.readlines()  # Reads entire file into a list
```

---

## 6. Writing to Files

When using `"w"` mode:

- If the file **exists**, it’s **overwritten**.
- If the file does **not** exist, it’s created.

```python
with open("example_file2.txt", "w") as f:
    f.write("This text will overwrite any existing content.\n")
```

> **Be careful** with `"w"` mode, as you may lose existing data in the file.

---

## 7. Appending to Files

When using `"a"` mode:

- Data is added to the end of the existing file.
- If the file doesn’t exist, it’s created.

```python
with open("example_file2.txt", "a") as f:
    f.write("New line appended at the end.\n")
```

---

## 8. Using `with` Statement (Context Manager)

The recommended way to handle files in Python is using the `with` statement, because it:

- Automatically closes the file after the block finishes (even if errors occur).
- Makes for cleaner, more readable code.

```python
with open("example_file1.txt", "r") as f:
    for line in f:
        print(line.strip())
```

Within this `with` block, the file object is available as `f`. After exiting the block, `f` is automatically closed.

---

## 9. Dummy Files with Example Content

We’ll use two dummy files for demonstration:

1. **`example_file1.txt`**
   ```
   This is line 1 in example_file1.
   This is line 2 in example_file1.
   ```
2. **`example_file2.txt`**
   ```
   example_file2 initial content.
   More lines can go here.
   ```

**Creating these files on Linux** (using `echo` commands):

```bash
echo "This is line 1 in example_file1." > example_file1.txt
echo "This is line 2 in example_file1." >> example_file1.txt

echo "example_file2 initial content." > example_file2.txt
echo "More lines can go here." >> example_file2.txt
```

---

## 10. Example Code Snippets

### 10.1 Reading Entire File

```python
#!/usr/bin/env python3

def read_entire_file(filepath):
    with open(filepath, "r") as file:
        content = file.read()
        return content

if __name__ == "__main__":
    file_content = read_entire_file("example_file1.txt")
    print("=== Content of example_file1.txt ===")
    print(file_content)
```

### 10.2 Writing (Overwriting) a File

```python
#!/usr/bin/env python3

def overwrite_file(filepath, text):
    with open(filepath, "w") as file:
        file.write(text)

if __name__ == "__main__":
    overwrite_file("example_file2.txt", "This content overwrote everything.\n")
    print("File overwritten successfully.")
```

### 10.3 Appending to a File

```python
#!/usr/bin/env python3

def append_to_file(filepath, text):
    with open(filepath, "a") as file:
        file.write(text)

if __name__ == "__main__":
    append_to_file("example_file2.txt", "Appending some more lines...\n")
    print("Content appended successfully.")
```

### 10.4 Reading Line by Line

```python
#!/usr/bin/env python3

def print_file_lines(filepath):
    with open(filepath, "r") as file:
        for line in file:
            print(line.strip())

if __name__ == "__main__":
    print_file_lines("example_file1.txt")
```

---

## 11. Additional Tips

1. **File Permissions**:  
   On Linux, you may need to adjust file permissions if you get a “permission denied” error.

   - For example, `chmod 644 filename.txt` gives read/write for the owner and read-only for others.

2. **Binary Mode**:  
   If you’re working with non-text files (images, PDFs, etc.), open in binary mode:

   ```python
   with open("image.jpg", "rb") as img_file:
       data = img_file.read()
   ```

3. **Exceptions**:  
   If the file doesn’t exist or if there’s a permission issue, Python raises an exception (e.g., `FileNotFoundError`, `PermissionError`). You can handle these with `try-except` blocks for more robust code.

4. **Encoding**:  
   When reading or writing text files, you can specify an encoding:
   ```python
   with open("example_utf8.txt", "r", encoding="utf-8") as f:
       data = f.read()
   ```
   This is often important for non-ASCII text.

---

## 12. References

- [Python Docs: `open()` Function](https://docs.python.org/3/library/functions.html#open)
- [Python Docs: File Objects](https://docs.python.org/3/tutorial/inputoutput.html#reading-and-writing-files)
- [Linux File Permissions](https://www.gnu.org/software/coreutils/manual/html_node/Mode-Structure.html)

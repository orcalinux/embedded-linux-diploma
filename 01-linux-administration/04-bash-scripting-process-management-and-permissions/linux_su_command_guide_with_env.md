# **`su` Command in Linux: A Comprehensive Guide**

The `su` (substitute user or switch user) command is used to **switch to another user account** in a Linux system. It allows you to execute commands as another user or start a new shell session.

Understanding **environment variables** is key to seeing the difference between `su` and `su -`.

---

## **Table of Contents**

1. [What are Environment Variables?](#what-are-environment-variables)
2. [Demo: Viewing and Understanding Environment Variables](#demo-viewing-and-understanding-environment-variables)
3. [What is the `su` Command?](#what-is-the-su-command)
4. [Options of the `su` Command](#options-of-the-su-command)
5. [Difference Between `su` and `su -`](#difference-between-su-and-su-)
6. [Demo: How `su` Affects Environment Variables](#demo-how-su-affects-environment-variables)
7. [Common Usage Examples](#common-usage-examples)
8. [Using `su` Securely](#using-su-securely)
9. [Summary](#summary)

---

## **What are Environment Variables?**

Environment variables are **key-value pairs** in Linux that define the behavior of processes and shells. These variables affect how programs and the operating system behave.

### **Common Environment Variables**

| Variable | Description                                | Example Value                  |
| -------- | ------------------------------------------ | ------------------------------ |
| `PATH`   | Directories to search for executable files | `/usr/bin:/bin:/usr/local/bin` |
| `HOME`   | Home directory of the current user         | `/home/ahmed`                  |
| `USER`   | Current user name                          | `ahmed`                        |
| `SHELL`  | Default shell of the user                  | `/bin/bash`                    |
| `PWD`    | Current working directory                  | `/home/ahmed/projects`         |

---

## **Demo: Viewing and Understanding Environment Variables**

### **Check Current Environment Variables**

To display environment variables for the current session, run:

```bash
printenv
```

Or to display specific variables, use:

```bash
echo $USER     # Current user
echo $HOME     # Home directory
echo $SHELL    # Default shell
echo $PATH     # Executable search path
```

---

### **Environment Variables in a Demo**

#### **Step 1: Check the Environment as Your Current User**

Run the following:

```bash
echo "Current User: $USER"
echo "Home Directory: $HOME"
echo "Current PATH: $PATH"
```

**Example Output:**

```
Current User: ahmed
Home Directory: /home/ahmed
Current PATH: /usr/bin:/bin:/usr/local/bin
```

---

## **What is the `su` Command?**

The `su` command allows you to switch users in a Linux system. By default, `su` switches to the **root user**. It can also be used to switch to other users with their passwords.

The behavior of **environment variables** changes depending on whether you use `su` or `su -`.

---

## **Options of the `su` Command**

| Option            | Description                                                                |
| ----------------- | -------------------------------------------------------------------------- |
| `-` (dash)        | Start a **login shell** for the user, resetting the environment variables. |
| `-l` or `--login` | Same as `-`. Equivalent to logging in as the user.                         |
| `-c`              | Run a single command as the target user.                                   |
| `-m` or `-p`      | Preserve the current environment (do not load target user environment).    |
| `-s SHELL`        | Specify a shell to use (e.g., `/bin/bash`, `/bin/zsh`).                    |
| `--help`          | Display help information about the `su` command.                           |
| `--version`       | Display the version information.                                           |

---

## **Difference Between `su` and `su -`**

### **`su` (Without Dash)**

- Switches to the target user **without changing the environment**.
- The environment variables (`USER`, `PATH`, `HOME`) of the previous user **are retained**.
- You remain in the **current directory**.

---

### **`su -` (With Dash)**

- Switches to the target user **and starts a full login shell**.
- The environment variables (`USER`, `HOME`, `PATH`) are fully loaded as if the user logged in directly.
- The working directory changes to the user's **home directory**.

---

## **Demo: How `su` Affects Environment Variables**

Here we demonstrate the difference in environment variables between `su` and `su -`.

---

### **Step 1: Check the Environment Before Using `su`**

As your current user (`ahmed`), run:

```bash
echo "Current User: $USER"
echo "Home Directory: $HOME"
echo "Current PATH: $PATH"
```

**Output Example:**

```
Current User: ahmed
Home Directory: /home/ahmed
Current PATH: /usr/bin:/bin:/usr/local/bin
```

---

### **Step 2: Use `su` (Without Dash)**

Switch to another user (e.g., `ali`):

```bash
su ali
```

Now check the environment variables:

```bash
echo "Current User: $USER"
echo "Home Directory: $HOME"
echo "Current PATH: $PATH"
```

**Output Example:**

```
Current User: ahmed
Home Directory: /home/ahmed
Current PATH: /usr/bin:/bin:/usr/local/bin
```

- **Observation:** The environment variables remain **unchanged**. The shell is running as `ali`, but the environment still reflects `ahmed`.

Exit back to the original user:

```bash
exit
```

---

### **Step 3: Use `su -` (With Dash)**

Now use the `-` option:

```bash
su - ali
```

Check the environment variables:

```bash
echo "Current User: $USER"
echo "Home Directory: $HOME"
echo "Current PATH: $PATH"
```

**Output Example:**

```
Current User: ali
Home Directory: /home/ali
Current PATH: /usr/local/bin:/usr/bin:/bin
```

- **Observation:** The environment variables are fully updated to reflect `ali`'s environment.

Exit back to the original user:

```bash
exit
```

---

## **Common Usage Examples**

1. **Switch to Root User**:

   ```bash
   su
   ```

2. **Switch to Another User**:

   ```bash
   su fatima
   ```

3. **Switch to Another User with Login Shell**:

   ```bash
   su - fatima
   ```

4. **Run a Single Command as Another User**:

   ```bash
   su - khaled -c "echo Hello from Khaled"
   ```

5. **Preserve the Current Environment**:
   ```bash
   su -m khaled
   ```

---

## **Summary**

The `su` command allows you to switch users and execute commands as another user. The **behavior of environment variables** changes depending on whether you use `su` or `su -`.

- **`su`**: Retains the current environment.
- **`su -`**: Resets the environment and behaves like a fresh login.

### **Key Takeaways**:

- Use `su` when you only need to switch the user temporarily.
- Use `su -` when you need to load the full environment of the target user.

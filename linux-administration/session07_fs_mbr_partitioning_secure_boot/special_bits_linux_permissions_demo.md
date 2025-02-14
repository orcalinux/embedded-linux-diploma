# Special Bits in Linux File Permissions – Setuid, Setgid, and Sticky Bit

This guide explains the **special bits** in Linux file permissions—**Setuid**, **Setgid**, and **Sticky Bit**. We'll explore their importance, practical use cases, and demonstrations with real commands. The demo at the end involves creating users to fully demonstrate how these permissions affect file and directory access.

---

## Table of Contents

1. [Introduction](#introduction)
2. [User and Group Setup for Demo](#user-and-group-setup-for-demo)
3. [Special Bits and Octal Values](#special-bits-and-octal-values)
4. [Setuid Bit](#setuid-bit)
   - [Explanation](#setuid-explanation)
   - [Demo: Setuid Bit](#demo-setuid-bit)
5. [Setgid Bit](#setgid-bit)
   - [Explanation](#setgid-explanation)
   - [Demo: Setgid Bit](#demo-setgid-bit)
6. [Sticky Bit](#sticky-bit)
   - [Explanation](#sticky-bit-explanation)
   - [Demo: Sticky Bit](#demo-sticky-bit)
7. [Full Demo: Combining Setuid, Setgid, and Sticky Bit](#full-demo-combining-setuid-setgid-and-sticky-bit)
8. [Conclusion](#conclusion)

---

## Introduction

Linux file permissions are essential for security and managing access to files and directories. Special permission bits—**Setuid**, **Setgid**, and **Sticky Bit**—extend beyond basic `read`, `write`, and `execute` permissions to enable specific functionality:

- **Setuid**: Execute a program with the privileges of the file owner.
- **Setgid**: Newly created files and directories inherit the group ownership of their parent directory.
- **Sticky Bit**: Prevents users from deleting files they do not own in shared directories.

---

## User and Group Setup for Demo

Before testing **Setuid**, **Setgid**, and **Sticky Bit**, let's create the necessary users and groups.

### **Create Users and Groups**

```bash
sudo groupadd developers
sudo useradd -m -G developers developer1
sudo useradd -m -G developers developer2
sudo useradd -m testuser
```

- **developers** – Group for shared directories.
- **developer1 & developer2** – Users in the `developers` group for Setgid tests.
- **testuser** – A regular user to test Setuid programs.

### **Set User Passwords**

```bash
sudo passwd developer1
sudo passwd developer2
sudo passwd testuser
```

---

## Special Bits and Octal Values

In Linux, the **special bits** – **Setuid, Setgid, and Sticky Bit** – have specific octal values when applied to files or directories. These bits are represented as the **first digit** in a four-digit octal permission.

---

### **Special Bit Values (Octal Representation)**

| Special Bit    | Symbol | Octal Value | Description                                    |
| -------------- | ------ | ----------- | ---------------------------------------------- |
| **Setuid**     | `s`    | `4`         | Set User ID (execute as file owner)            |
| **Setgid**     | `s`    | `2`         | Set Group ID (inherit group ownership)         |
| **Sticky Bit** | `t`    | `1`         | Restrict file deletion (only owner can delete) |

---

### **Combining Special Bits**

Special bits can be combined by adding their octal values:

| Special Bits Combination | Octal Value     | Meaning                       |
| ------------------------ | --------------- | ----------------------------- |
| Setuid + Setgid          | `4 + 2 = 6`     | Setuid and Setgid enabled     |
| Setuid + Sticky Bit      | `4 + 1 = 5`     | Setuid and Sticky Bit enabled |
| Setgid + Sticky Bit      | `2 + 1 = 3`     | Setgid and Sticky Bit enabled |
| Setuid + Setgid + Sticky | `4 + 2 + 1 = 7` | All special bits enabled      |

---

### **How to Apply Special Bits (Examples)**

1. **Setuid (Octal `4755`)** – User executes the file with the owner's permissions:

```bash
sudo chmod 4755 /path/to/file
```

2. **Setgid (Octal `2755`)** – Files in the directory inherit the group:

```bash
sudo chmod 2755 /path/to/directory
```

3. **Sticky Bit (Octal `1777`)** – Users can only delete their own files in shared directories:

```bash
sudo chmod 1777 /tmp
```

4. **Setuid + Setgid (Octal `6755`)**:

```bash
sudo chmod 6755 /path/to/file
```

---

## Viewing Special Bits on Files/Directories

```bash
ls -l /path/to/file
```

**Output Example**:

```
-rwsr-xr-x  1 root root  12345 Dec 25 10:00 /usr/bin/passwd
drwxrwsr-x  2 root developers  4096 Dec 25 10:00 /shared
drwxrwxrwt  2 root root  4096 Dec 25 10:00 /tmp
```

- **`s`** in **user** (`rws`) – Setuid
- **`s`** in **group** (`rws`) – Setgid
- **`t`** in **others** (`rwt`) – Sticky Bit

---

## Setuid Bit

### Setuid Explanation

- The **Setuid (Set User ID)** bit allows a program to execute with the permissions of the **file owner** (typically root).
- **Why it's Important**: This allows non-privileged users to run essential system utilities that require elevated privileges (e.g., `/usr/bin/passwd`).
- **Security Note**: Setuid can introduce security vulnerabilities if misconfigured or applied to insecure programs.

**Symbol**: `s` in place of the executable bit for the user (`rws` instead of `rwx`).

---

### Demo: Setuid Bit

1. **Create a Test Program with Setuid**:

```bash
echo '#include <unistd.h> \n#include <stdlib.h> \nint main() { setuid(0); system("/bin/bash"); return 0; }' > test.c
gcc -o test test.c
```

**Explanation**:

- The warnings occur because `setuid` and `system` require explicit header file declarations.
- **Fix**: Add `#include <unistd.h>` for `setuid()` and `#include <stdlib.h>` for `system()`.

2. **Assign Root Ownership and Setuid**:

```bash
sudo chown root:root test
sudo chmod u+s test
ls -l test
```

**Expected Output**:

```
-rwsr-xr-x 1 root root 12345 Dec 25 10:00 test
```

3. **Test with `testuser`**:

```bash
su - testuser
./test
```

- The program runs with **root privileges**.

---

## Setgid Bit

### Setgid Explanation

- The **Setgid (Set Group ID)** bit causes files and directories to inherit the **group ownership** of the parent directory.
- **Why it's Important**: Useful for collaborative environments where files must share group ownership.

**Symbol**: `s` in place of the executable bit for the group (`rws` instead of `rwx` for directories).

---

### Demo: Setgid Bit

1. **Create a Shared Directory**:

```bash
sudo mkdir /shared
sudo chown root:developers /shared
sudo chmod 2770 /shared
ls -ld /shared
```

**Expected Output**:

```
drwxrws--- 2 root developers 4096 Dec 25 10:00 /shared
```

2. **Create Files in the Shared Directory**:

```bash
su - developer1
cd /shared
touch file1
ls -l
```

**Expected Output**:

```
-rw-r--r-- 1 developer1 developers 0 Dec 25 10:05 file1
```

- **Files inherit the `developers` group** instead of the user’s primary group.

---

## Sticky Bit

### Sticky Bit Explanation

- The **Sticky Bit** prevents users from deleting files they don't own, even if they have write access to the directory.
- **Why it's Important**: Commonly applied to `/tmp` to ensure only the file owner or root can delete files.

**Symbol**: `t` in place of the executable bit for others (`rwt`).

---

### Demo: Sticky Bit

1. **Create a Shared Directory with Sticky Bit**:

```bash
sudo mkdir /sticky
sudo chmod 1777 /sticky
ls -ld /sticky
```

**Expected Output**:

```
drwxrwxrwt 2 root root 4096 Dec 25 10:00 /sticky
```

2. **Create Files as Different Users**:

```bash
su - developer1
touch /sticky/file1
su - developer2
touch /sticky/file2
```

3. **Attempt to Delete Files**:

```bash
su - developer1
rm /sticky/file2
```

**Expected Output**:

```
rm: cannot remove '/sticky/file2': Operation not permitted
```

- Only the **owner** of the file (or root) can delete it.

---

## Full Demo: Combining Setuid, Setgid, and Sticky Bit

### Scenario

1. Create a **shared directory** for developers, with:
   - **Setgid** – Ensures all files belong to the `developers` group.
   - **Sticky Bit** – Prevents unauthorized file deletions.

---

### **Setup**

```bash
sudo mkdir /project
sudo chown root:developers /project
sudo chmod 2777 /project
ls -ld /project
```

**Expected Output**:

```
drwxrwsrwt 2 root developers 4096 Dec 25 10:00 /project
```

### **User Actions**

```bash
su - developer1
cd /project
touch file1
su - developer2
touch file2
```

### **File Deletion Attempt**

```bash
su - developer1
rm file2
```

**Expected Output**:

```
rm: cannot remove 'file2': Operation not permitted
```

- The sticky bit prevents unauthorized deletion.

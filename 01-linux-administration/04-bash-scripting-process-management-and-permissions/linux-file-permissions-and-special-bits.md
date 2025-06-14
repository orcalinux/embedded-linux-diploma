# **Linux File Permissions and Special Bits**

File permissions in Linux control the level of access users have to files and directories. Understanding these permissions and special bits is critical for maintaining a secure and well-organized system.

---

## **Table of Contents**

1. [Introduction to File Permissions](#introduction-to-file-permissions)
2. [Ownership Model](#ownership-model)
3. [Permission Types](#permission-types)
   - [Read (r)](#read-r)
   - [Write (w)](#write-w)
   - [Execute (x)](#execute-x)
4. [Permission Groups](#permission-groups)
   - [User (Owner)](#user-owner)
   - [Group](#group)
   - [Others (World)](#others-world)
5. [Symbolic and Numeric Representations](#symbolic-and-numeric-representations)
   - [Symbolic Mode](#symbolic-mode)
   - [Numeric Mode (Octal)](#numeric-mode-octal)
6. [Special Permission Bits](#special-permission-bits)
   - [Setuid (Set User ID)](#setuid-set-user-id)
   - [Setgid (Set Group ID)](#setgid-set-group-id)
   - [Sticky Bit](#sticky-bit)
7. [How Special Bits Appear in `ls -l`](#how-special-bits-appear-in-ls--l)
8. [Other Attributes Not Shown by `ls -al`](#other-attributes-not-shown-by-ls--al)
   - [Extended Attributes and ACLs](#extended-attributes-and-acls)
   - [File Attributes with `chattr` and `lsattr`](#file-attributes-with-chattr-and-lsattr)
9. [Examples and Common Commands](#examples-and-common-commands)
   - [Changing Permissions with `chmod`](#changing-permissions-with-chmod)
   - [Changing Ownership with `chown` and `chgrp`](#changing-ownership-with-chown-and-chgrp)
   - [Viewing Extended Attributes and ACLs](#viewing-extended-attributes-and-acls)
10. [Summary](#summary)

---

## **Introduction to File Permissions**

Linux enforces access control on files and directories using a permissions system. Each file or directory has associated permissions that determine whether a user can read, write, or execute it.

---

## **Ownership Model**

Each file and directory has three key attributes related to identity:

1. **User (Owner)**: The username of the person who owns the file.
2. **Group**: The group that owns the file.
3. **Others**: Everyone else who is not the user or in the group.

---

## **Permission Types**

There are three standard permission types:

### **Read (r)**

- For files: Allows viewing the file’s contents.
- For directories: Allows listing the directory’s contents.

### **Write (w)**

- For files: Allows modifying or deleting the file’s contents.
- For directories: Allows creating, deleting, and renaming files within the directory.

### **Execute (x)**

- For files: Allows executing the file as a program or script.
- For directories: Allows entering (cd into) the directory.

---

## **Permission Groups**

Permissions apply to three categories:

### **User (Owner)**

Permissions that apply only to the file’s owner.

### **Group**

Permissions that apply to members of the file’s group.

### **Others (World)**

Permissions that apply to everyone else on the system.

---

## **Symbolic and Numeric Representations**

Permissions can be represented symbolically or numerically.

### **Symbolic Mode**

A typical `ls -l` output:

```
-rw-r--r-- 1 user group  1024 Mar  2 12:34 file.txt
```

Breaking down the first field (`-rw-r--r--`):

- The first character `-` indicates a regular file (d for directory, l for symlink, etc.).
- Next three characters (`rw-`): User permissions (read, write, no execute).
- Next three characters (`r--`): Group permissions (read only).
- Final three characters (`r--`): Others permissions (read only).

### **Numeric Mode (Octal)**

Permissions can also be represented using a three-digit octal number, where each digit represents the sum of read (4), write (2), and execute (1):

- **4** = read
- **2** = write
- **1** = execute

For example:

- `rwx` = 4 + 2 + 1 = 7
- `rw-` = 4 + 2 + 0 = 6
- `r--` = 4 + 0 + 0 = 4

So `-rw-r--r--` translates to `644`:

- User: `rw-` = 6
- Group: `r--` = 4
- Others: `r--` = 4

---

## **Special Permission Bits**

Beyond the standard rwx bits, there are three special permissions:

### **Setuid (Set User ID)**

- **Applies to files**: When set on an executable file, it causes the program to run with the file owner’s privileges rather than the user who runs it.
- Represented symbolically: `s` replaces the `x` in the user’s permission field.
- Octal: Setuid bit = 4 in the four-digit octal notation (e.g., `4755`).

### **Setgid (Set Group ID)**

- **Applies to files and directories**:
  - On executable files: Similar to setuid, but applies group privileges.
  - On directories: Files created inside the directory inherit the directory’s group.
- Represented symbolically: `s` replaces the `x` in the group’s permission field.
- Octal: Setgid bit = 2 in the four-digit octal notation (e.g., `2755`).

### **Sticky Bit**

- **Primarily applies to directories**: When set on a directory (e.g. `/tmp`), only the owner of a file (or directory) inside it, the directory’s owner, or the root user can delete or rename that file.
- Represented symbolically: `t` replaces the `x` in the others’ permission field.
- Octal: Sticky bit = 1 in the four-digit octal notation (e.g., `1755`).

---

## **How Special Bits Appear in `ls -l`**

- **Setuid**: Appears as `s` in the user’s execute position. For example: `-rwsr-xr-x`.
- **Setgid**: Appears as `s` in the group’s execute position. For example: `-rwxr-sr-x`.
- **Sticky Bit**: Appears as `t` in the others’ execute position on a directory. For example: `drwxrwxrwt`.

---

## **Other Attributes Not Shown by `ls -al`**

`ls -al` shows basic permissions, but there are other attributes and permissions that do not appear in the standard listing:

### **Extended Attributes and ACLs**

- **Extended Attributes (xattrs)**: Additional metadata can be associated with files. Use `ls -l` with `-Z` for SELinux contexts or `getfattr -d file` to see extended attributes.
- **Access Control Lists (ACLs)**: Provide more fine-grained permissions than the standard rwx model. If a file has ACLs, `ls -l` may show a `+` sign at the end of the permission string. Use `getfacl` and `setfacl` commands to view and modify these.

For example:

```
-rw-r--r--+ 1 user group 1024 Mar  2 12:34 file.txt
```

The `+` indicates ACLs or extended attributes are present.

### **File Attributes with `chattr` and `lsattr`**

There are file attributes that are not reflected in standard Unix permissions, managed by `chattr` and viewed with `lsattr`. These attributes can:

- Make a file immutable (`i` attribute),
- Append-only (`a` attribute),
- Or have other special behaviors.

For example, to view attributes:

```bash
lsattr file.txt
```

To set an attribute (like immutable):

```bash
sudo chattr +i file.txt
```

These attributes do not appear in the standard `ls -al` output.

---

## **Examples and Common Commands**

### Changing Permissions with `chmod`

- Symbolic:
  ```bash
  chmod u=rwx,g=rx,o=r file.txt
  chmod g+w file.txt
  ```
- Numeric:
  ```bash
  chmod 755 file.txt
  chmod 640 file.txt
  ```

Setting special bits using numeric notation:

```bash
chmod 4755 program     # Setuid
chmod 2755 directory   # Setgid
chmod 1755 directory   # Sticky bit
```

### Changing Ownership with `chown` and `chgrp`

```bash
sudo chown newuser file.txt
sudo chown newuser:newgroup file.txt
sudo chgrp newgroup file.txt
```

### Viewing Extended Attributes and ACLs

- Viewing ACLs:
  ```bash
  getfacl file.txt
  ```
- Setting ACLs:
  ```bash
  setfacl -m u:username:rwx file.txt
  ```
- Viewing extended attributes:
  ```bash
  getfattr -d file.txt
  ```

---

## **Summary**

Linux file permissions control access at a granular level using owner, group, and others classifications combined with read, write, and execute permissions. Special permission bits (setuid, setgid, and sticky) add further functionality for executing files and managing directories. Beyond standard permissions, extended attributes, ACLs, and file attributes offer even finer control and additional metadata.

A solid understanding of these concepts enables administrators and users to maintain a secure, organized, and predictable system environment.

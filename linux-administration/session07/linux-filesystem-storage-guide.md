# Linux Filesystem and Storage: Comprehensive Guide

Welcome to the **Linux Filesystem and Storage** guide. This document provides a detailed exploration of storage technologies in Linux, their evolution, the concepts of inodes, dentries, the Master Boot Record (MBR), the superblock, and the Linux filesystem. Practical examples and demonstrations, including C programming and system calls, are included to deepen your understanding and provide hands-on experience.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Storage in Linux: A Historical Overview](#storage-in-linux-a-historical-overview)
3. [Types of Storage in Linux](#types-of-storage-in-linux)
   - [Direct-Attached Storage (DAS)](#direct-attached-storage-das)
   - [Network-Attached Storage (NAS)](#network-attached-storage-nas)
   - [Storage Area Networks (SAN)](#storage-area-networks-san)
4. [Understanding the Inode Table](#understanding-the-inode-table)
   - [What is an Inode?](#what-is-an-inode)
   - [Key Concepts](#key-concepts)
   - [Inode Table Structure and Example](#inode-table-structure-and-example)
   - [Linux Inode Structure and Metadata](#linux-inode-structure-and-metadata)
5. [Understanding the Dentry Table](#understanding-the-dentry-table)
   - [What is a Dentry?](#what-is-a-dentry)
   - [Key Concepts](#key-concepts-1)
   - [Dentry Table Structure and Example](#dentry-table-structure-and-example)
6. [Understanding the Superblock](#understanding-the-superblock)
   - [What is a Superblock?](#what-is-a-superblock)
   - [Key Concepts](#key-concepts-2)
   - [Superblock Structure and Example](#superblock-structure-and-example)
   - [Superblock and Its Relationship with Inodes and Dentries](#superblock-and-its-relationship-with-inodes-and-dentries)
7. [Boot Process and Master Boot Record (MBR)](#boot-process-and-master-boot-record-mbr)
   - [What is the MBR?](#what-is-the-mbr)
   - [MBR Structure](#mbr-structure)
   - [Boot Process Overview](#boot-process-overview)
   - [MBR and Partition Tables](#mbr-and-partition-tables)
   - [Second Stage Bootloader](#second-stage-bootloader)
   - [GPT vs. MBR](#gpt-vs-mbr)
8. [Linux Filesystem Overview](#linux-filesystem-overview)
   - [Filesystem Types](#filesystem-types)
   - [Filesystem Hierarchy Standard (FHS)](#filesystem-hierarchy-standard-fhs)
9. [Practical Examples and Demos](#practical-examples-and-demos)
   - [Demo 1: Checking Storage Devices](#demo-1-checking-storage-devices)
   - [Demo 2: Creating and Mounting a Filesystem](#demo-2-creating-and-mounting-a-filesystem)
   - [Demo 3: Viewing and Managing Inodes](#demo-3-viewing-and-managing-inodes)
   - [Demo 4: Exploring Filesystem Hierarchy](#demo-4-exploring-filesystem-hierarchy)
   - [Demo 5: Interacting with the Filesystem Using C and Syscalls](#demo-5-interacting-with-the-filesystem-using-c-and-syscalls)
   - [Demo 6: Creating a Custom Inode Manipulation Program](#demo-6-creating-a-custom-inode-manipulation-program)
   - [Demo 7: Inspecting the Master Boot Record](#demo-7-inspecting-the-master-boot-record)
   - [Demo 8: Exploring Partition Tables with GPT and MBR](#demo-8-exploring-partition-tables-with-gpt-and-mbr)
   - [Demo 9: Installing and Configuring a Second Stage Bootloader](#demo-9-installing-and-configuring-a-second-stage-bootloader)
   - [Demo 10: Inspecting the Superblock](#demo-10-inspecting-the-superblock)
10. [Conclusion](#conclusion)

---

## Introduction

The Linux operating system handles storage and filesystems with remarkable flexibility and scalability. Understanding Linux storage systems, the evolution of storage technologies, and how the Linux filesystem operates is crucial for system administrators, developers, and anyone managing Linux environments.

---

## Storage in Linux: A Historical Overview

1. **1960s–1970s**:

   - Early storage relied on tape drives and magnetic disks.
   - **Unix File System (UFS)** was developed to manage files efficiently.

2. **1980s–1990s**:

   - The emergence of **SCSI** (Small Computer System Interface) enabled faster, more reliable storage.
   - Linux introduced support for **ext (Extended Filesystem)** and later **ext2**, bringing improvements in stability and performance.

3. **2000s–2010s**:

   - Development of journaling filesystems like **ext3**, **ext4**, and **ReiserFS**.
   - Adoption of networked storage solutions (e.g., NAS and SAN).

4. **2020s and Beyond**:
   - Advanced filesystems like **Btrfs** and **ZFS** offer snapshot capabilities and advanced data integrity checks.
   - Increasing use of NVMe and SSD technologies for higher throughput and lower latency.

---

## Types of Storage in Linux

### Direct-Attached Storage (DAS)

- **Definition**: Storage devices directly connected to a computer (e.g., HDDs, SSDs).
- **Examples**: SATA drives, USB drives.
- **Advantages**: High-speed access, simple setup.
- **Use Cases**: Local data storage, backup drives.

### Network-Attached Storage (NAS)

- **Definition**: Storage accessed over a network using protocols like NFS or SMB.
- **Examples**: Dedicated NAS appliances, shared drives.
- **Advantages**: Centralized storage, easy file sharing.
- **Use Cases**: Home networks, small businesses.

### Storage Area Networks (SAN)

- **Definition**: High-speed network providing access to block-level storage.
- **Examples**: Fibre Channel SANs, iSCSI SANs.
- **Advantages**: Scalable, high performance.
- **Use Cases**: Enterprise databases, virtualization environments.

---

## Understanding the Inode Table

### What is an Inode?

An **inode** is a data structure used by Linux filesystems to store metadata about files. Every file and directory has an inode, which contains:

- File type (e.g., regular file, directory, symlink)
- Permissions (read, write, execute)
- Owner (user and group)
- Timestamps (creation, modification, access)
- Number of hard links
- File size
- Pointers to data blocks

### Key Concepts

- **Inode Number**: A unique identifier for each file within a filesystem.
- **Inode Table**: A structure that holds all inodes for a filesystem.
- **Metadata Separation**: Inodes store metadata separately from file content.

### Inode Table Structure and Example

The inode table is a critical component of Linux filesystems, maintaining information about each file. Below is a table outlining the typical fields in an inode and an example entry.

| Field                   | Description                                                    | Example Value                        |
| ----------------------- | -------------------------------------------------------------- | ------------------------------------ |
| **Inode Number**        | Unique identifier within the filesystem                        | `128394`                             |
| **File Type**           | Type of the file (`regular file`, `directory`, etc.)           | `Regular File`                       |
| **Permissions**         | Access permissions (`rwxr-xr-x`)                               | `-rw-r--r--`                         |
| **Owner**               | User and group ownership                                       | `alice:developers`                   |
| **Timestamps**          | Creation, modification, and access times                       | `2024-04-10 12:34`                   |
| **Hard Links**          | Number of hard links pointing to the inode                     | `1`                                  |
| **File Size**           | Size of the file in bytes                                      | `675 bytes`                          |
| **Data Block Pointers** | Pointers to the data blocks where the file's content is stored | `Block 1024, Block 2048, Block 3072` |

**Example Inode Entry**

| Field                   | Value                                |
| ----------------------- | ------------------------------------ |
| **Inode Number**        | `128394`                             |
| **File Type**           | `Regular File`                       |
| **Permissions**         | `-rw-r--r--`                         |
| **Owner**               | `alice:developers`                   |
| **Timestamps**          | `2024-04-10 12:34`                   |
| **Hard Links**          | `1`                                  |
| **File Size**           | `675 bytes`                          |
| **Data Block Pointers** | `Block 1024, Block 2048, Block 3072` |

### Linux Inode Structure and Metadata

```c
struct inode {
    umode_t            i_mode;      /* File mode (permissions) */
    unsigned short     i_opflags;   /* Internal flags */
    kuid_t             i_uid;       /* Owner's user ID */
    kgid_t             i_gid;       /* Owner's group ID */
    unsigned int       i_flags;     /* File flags */
    struct timespec64  i_atime;     /* Last access time */
    struct timespec64  i_mtime;     /* Last modification time */
    struct timespec64  i_ctime;     /* Last status change time */
    blkcnt_t           i_blocks;    /* Number of 512B blocks allocated */
    loff_t             i_size;      /* File size in bytes */
    struct hlist_node  i_hash;      /* Hash list node */
    struct list_head   i_io_list;   /* IO list */
    struct list_head   i_wb_list;   /* Write-back list */
    struct address_space *i_mapping; /* Page cache mapping */
    struct address_space i_data;    /* Private data mapping */
    struct inode_operations *i_op;  /* Inode operations */
    struct super_block *i_sb;       /* Associated superblock */
    struct file_operations *i_fop;  /* File operations */
    struct lockref     i_lockref;   /* Reference count with spinlock */
    atomic_t           i_count;     /* Reference counter */
    unsigned long      i_state;     /* State flags */
    unsigned long      dirtied_when;/* Time when dirtied */
    unsigned long      i_version;   /* Version number */
    __u32              i_generation;/* Generation number */
    struct xattr       *i_xattrs;   /* Extended attributes */
};
```

### Key Fields:

- **`i_mode`**: Describes the file type and permissions (regular file, directory, symlink, etc.).
- **`i_uid` / `i_gid`**: Owner and group identifiers.
- **`i_size`**: Size of the file in bytes.
- **`i_atime, i_mtime, i_ctime`**: Access, modification, and change times.
- **`i_blocks`**: Number of 512-byte blocks allocated.
- **`i_sb`**: Points to the superblock associated with the inode.
- **`i_mapping`**: Links to the page cache for the file.
- **`i_op` / `i_fop`**: Pointers to inode and file operations (e.g., read, write, open).

---

## Understanding the Dentry Table

### What is a Dentry?

A **dentry** (directory entry) is a data structure used by the Linux Virtual Filesystem (VFS) to cache information about directory entries. Dentries facilitate efficient file path resolution by storing the association between filenames and their corresponding inodes.

### Key Concepts

- **Dentry Cache**: A cache that holds dentries to speed up filesystem operations by avoiding repeated disk accesses.
- **Parent-Child Relationship**: Dentries maintain relationships between directories and their subdirectories or files.
- **Hierarchical Navigation**: Enables quick traversal of the filesystem hierarchy.

### Dentry Table Structure and Example

The dentry table maintains mappings between directory entries (names) and their corresponding inodes. Below is a table outlining the typical fields in a dentry and an example entry.

| Field               | Description                                          | Example Value        |
| ------------------- | ---------------------------------------------------- | -------------------- |
| **Dentry Name**     | Name of the directory entry (filename)               | `passwd`             |
| **Inode Number**    | Corresponding inode number of the file               | `128394`             |
| **Parent Dentry**   | Pointer/reference to the parent directory dentry     | `/etc`               |
| **Child Dentries**  | Pointers/references to child dentries (if directory) | `hosts, shadow, ssh` |
| **Reference Count** | Number of active references to the dentry            | `3`                  |

**Example Dentry Entry**

| Field               | Value                             |
| ------------------- | --------------------------------- |
| **Dentry Name**     | `passwd`                          |
| **Inode Number**    | `128394`                          |
| **Parent Dentry**   | `/etc`                            |
| **Child Dentries**  | `None` (since `passwd` is a file) |
| **Reference Count** | `3`                               |

**Example of a Directory Dentry**

| Field               | Value                        |
| ------------------- | ---------------------------- |
| **Dentry Name**     | `/etc`                       |
| **Inode Number**    | `567890`                     |
| **Parent Dentry**   | `/`                          |
| **Child Dentries**  | `passwd, hosts, shadow, ssh` |
| **Reference Count** | `5`                          |

**Comparison Table: Inode vs. Dentry**

| Feature           | Inode                                               | Dentry                                             |
| ----------------- | --------------------------------------------------- | -------------------------------------------------- |
| **Purpose**       | Stores metadata about files and directories         | Caches directory entry information for fast lookup |
| **Key Fields**    | Inode Number, File Type, Permissions, Owner, etc.   | Dentry Name, Inode Number, Parent Dentry, etc.     |
| **Relationship**  | Inodes are referenced by dentries                   | Dentries reference inodes                          |
| **Functionality** | Represents file metadata and storage locations      | Facilitates efficient path resolution and caching  |
| **Lifecycle**     | Exists as long as the file exists in the filesystem | Exists as long as the directory entry is cached    |

---

## Understanding the Superblock

### What is a Superblock?

The **superblock** is a critical metadata structure in Linux filesystems that contains information about the filesystem as a whole. It holds essential data required for the filesystem's operation, including its size, status, and configuration parameters.

### Key Concepts

- **Filesystem Metadata**: The superblock stores metadata that describes the filesystem's properties.
- **Recovery and Redundancy**: Multiple copies of the superblock may exist to ensure recovery in case of corruption.
- **Dynamic Information**: The superblock may track dynamic information like free blocks and inodes.

### Superblock Structure and Example

The superblock typically includes the following fields:

| Field                   | Description                                          | Example Value                          |
| ----------------------- | ---------------------------------------------------- | -------------------------------------- |
| **Magic Number**        | Identifies the filesystem type                       | `0xEF53` (for ext2/ext3/ext4)          |
| **Filesystem Size**     | Total size of the filesystem in blocks               | `1000000 blocks`                       |
| **Block Size**          | Size of each block in bytes                          | `4096 bytes`                           |
| **Free Blocks**         | Number of free blocks available                      | `50000`                                |
| **Free Inodes**         | Number of free inodes available                      | `20000`                                |
| **Mount Count**         | Number of times the filesystem has been mounted      | `50`                                   |
| **Maximum Mount Count** | Number of mounts before a filesystem check is needed | `100`                                  |
| **Filesystem State**    | Current state (clean, errors detected, etc.)         | `Clean`                                |
| **Last Mount Time**     | Timestamp of the last mount                          | `2024-04-10 12:34`                     |
| **Last Write Time**     | Timestamp of the last write                          | `2024-04-15 08:21`                     |
| **UUID**                | Universally Unique Identifier for the filesystem     | `123e4567-e89b-12d3-a456-426614174000` |
| **Volume Name**         | Human-readable name for the filesystem               | `MyData`                               |
| **Journal UUID**        | UUID of the journal (if journaling is enabled)       | `abcdef01-2345-6789-abcd-ef0123456789` |

**Example Superblock Entry**

| Field                   | Value                                  |
| ----------------------- | -------------------------------------- |
| **Magic Number**        | `0xEF53`                               |
| **Filesystem Size**     | `1000000 blocks`                       |
| **Block Size**          | `4096 bytes`                           |
| **Free Blocks**         | `50000`                                |
| **Free Inodes**         | `20000`                                |
| **Mount Count**         | `50`                                   |
| **Maximum Mount Count** | `100`                                  |
| **Filesystem State**    | `Clean`                                |
| **Last Mount Time**     | `2024-04-10 12:34`                     |
| **Last Write Time**     | `2024-04-15 08:21`                     |
| **UUID**                | `123e4567-e89b-12d3-a456-426614174000` |
| **Volume Name**         | `MyData`                               |
| **Journal UUID**        | `abcdef01-2345-6789-abcd-ef0123456789` |

### Superblock and Its Relationship with Inodes and Dentries

The superblock plays a pivotal role in managing the filesystem by maintaining the inode table and facilitating the dentry cache. Here's how they interrelate:

- **Superblock ↔ Inode Table**: The superblock contains pointers to the inode table, enabling the filesystem to manage file metadata efficiently.
- **Superblock ↔ Dentry Cache**: The superblock helps in maintaining the dentry cache by providing necessary filesystem parameters and state information.
- **Inode ↔ Dentry**: While inodes store metadata about files, dentries cache the association between filenames and inodes, allowing for rapid file access and path resolution.

**Comparison Table: Superblock vs. Inode vs. Dentry**

| Feature           | Superblock                                             | Inode                                                  | Dentry                                             |
| ----------------- | ------------------------------------------------------ | ------------------------------------------------------ | -------------------------------------------------- |
| **Purpose**       | Stores overall filesystem metadata and state           | Stores metadata about individual files and directories | Caches directory entry information for fast lookup |
| **Key Fields**    | Magic Number, Filesystem Size, Block Size, UUID, etc.  | Inode Number, File Type, Permissions, Owner, etc.      | Dentry Name, Inode Number, Parent Dentry, etc.     |
| **Relationship**  | Points to the inode table and manages filesystem state | Referenced by dentries                                 | References inodes and facilitates path resolution  |
| **Functionality** | Manages filesystem-wide parameters and integrity       | Represents file metadata and storage locations         | Facilitates efficient path resolution and caching  |
| **Lifecycle**     | Exists as long as the filesystem exists                | Exists as long as the file exists in the filesystem    | Exists as long as the directory entry is cached    |

---

## Boot Process and Master Boot Record (MBR)

### What is the MBR?

The **Master Boot Record (MBR)** is a special type of boot sector at the very beginning of partitioned computer mass storage devices like hard disks or removable drives. It contains:

- **Bootloader**: The initial code to start the boot process.
- **Partition Table**: Information about the disk's partitions.
- **Signature**: A specific value indicating a valid MBR.

### MBR Structure

The MBR is typically 512 bytes in size and structured as follows:

| Offset | Size (Bytes) | Description                                |
| ------ | ------------ | ------------------------------------------ |
| 0      | 446          | Bootloader code                            |
| 446    | 64           | Partition table (4 entries, 16 bytes each) |
| 510    | 2            | Boot signature (0x55AA)                    |

### Boot Process Overview

1. **BIOS Execution**:

   - The Basic Input/Output System (BIOS) performs POST (Power-On Self-Test).
   - BIOS reads the MBR from the boot device.

2. **MBR Execution**:

   - BIOS loads the bootloader code from the MBR into memory.
   - Bootloader reads the partition table to identify active partitions.

3. **Second Stage Bootloader**:
   - The bootloader (e.g., GRUB) loads the operating system's kernel from the active partition.
   - The kernel initializes the system and mounts the root filesystem.

### MBR and Partition Tables

The partition table within the MBR can define up to four primary partitions. Each partition entry includes:

| Field              | Description                                                 | Size (Bytes) |
| ------------------ | ----------------------------------------------------------- | ------------ |
| **Boot Indicator** | Indicates if the partition is bootable (0x80) or not (0x00) | 1            |
| **Starting CHS**   | Cylinder-Head-Sector address where the partition starts     | 3            |
| **Partition Type** | Specifies the filesystem type or partition usage            | 1            |
| **Ending CHS**     | Cylinder-Head-Sector address where the partition ends       | 3            |
| **Starting LBA**   | Logical Block Address where the partition starts            | 4            |
| **Size in LBA**    | Number of sectors in the partition                          | 4            |

**Example Partition Table Entry**

| Field              | Value                     |
| ------------------ | ------------------------- |
| **Boot Indicator** | `0x80` (Bootable)         |
| **Starting CHS**   | `0x1BE`                   |
| **Partition Type** | `0x83` (Linux filesystem) |
| **Ending CHS**     | `0x1FF`                   |
| **Starting LBA**   | `2048`                    |
| **Size in LBA**    | `2097152`                 |

### Second Stage Bootloader

The second stage bootloader, such as **GRUB (GRand Unified Bootloader)**, performs the following:

1. **Loading Configuration**:

   - Reads configuration files (e.g., `grub.cfg`) to determine OS options.

2. **Presenting Boot Menu**:

   - Displays a menu for the user to select the desired operating system or kernel.

3. **Loading the Kernel**:
   - Loads the selected kernel into memory.
   - Passes necessary parameters and control to the kernel.

### GPT vs. MBR

While MBR has been the traditional partitioning scheme, **GPT (GUID Partition Table)** is the modern alternative offering:

| Feature                | MBR                    | GPT                                              |
| ---------------------- | ---------------------- | ------------------------------------------------ |
| **Maximum Partitions** | 4 primary partitions   | Typically 128 partitions                         |
| **Disk Size Support**  | Up to 2TB              | Up to 9.4 ZB                                     |
| **Redundancy**         | Single partition table | Primary and backup partition tables              |
| **Data Integrity**     | No built-in protection | CRC32 checksums for headers and partition tables |
| **Compatibility**      | Legacy BIOS systems    | UEFI systems, some legacy support                |

---

## Linux Filesystem Overview

### Filesystem Types

Linux supports various filesystems, including:

- **ext4**: Default filesystem for many distributions; supports journaling and large files.
- **Btrfs**: Advanced features like snapshots, compression, and subvolumes.
- **XFS**: High-performance journaling filesystem, suitable for large-scale storage.
- **ZFS**: Robust, scalable filesystem with advanced data integrity checks.

### Filesystem Hierarchy Standard (FHS)

The **Filesystem Hierarchy Standard (FHS)** defines the structure and purpose of directories in Linux, ensuring consistency across distributions.

---

## Practical Examples and Demos

### Demo 1: Checking Storage Devices

**Objective**: Identify connected storage devices.

**Command**:

```bash
lsblk
```

_Output Example_:

```
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 238.5G  0 disk
├─sda1   8:1    0   512M  0 part /boot
└─sda2   8:2    0 238G    0 part /
sdb      8:16   1  14.5G  0 disk
└─sdb1   8:17   1  14.5G  0 part /media/usb
```

**Explanation**:

- **sda**: Primary storage device.
- **sda1**: Boot partition.
- **sda2**: Root partition.
- **sdb**: Removable storage (e.g., USB drive).
- **sdb1**: Partition mounted at `/media/usb`.

---

### Demo 2: Creating and Mounting a Filesystem

**Objective**: Create a new filesystem and mount it.

**Steps**:

1. **Create a Partition**:

   ```bash
   sudo fdisk /dev/sdb
   ```

   - Follow `fdisk` prompts to create a new partition (e.g., `/dev/sdb1`).

2. **Format the Partition**:

   ```bash
   sudo mkfs.ext4 /dev/sdb1
   ```

   - Formats the partition with the `ext4` filesystem.

3. **Mount the Partition**:

   ```bash
   sudo mkdir /mnt/mydisk
   sudo mount /dev/sdb1 /mnt/mydisk
   ```

4. **Verify the Mount**:
   ```bash
   df -h | grep /mnt/mydisk
   ```

_Expected Output_:

```
/dev/sdb1       14G   5G  9G  36% /mnt/mydisk
```

**Explanation**:

- **fdisk**: Utility to manipulate disk partitions.
- **mkfs.ext4**: Creates an `ext4` filesystem.
- **mount**: Attaches the filesystem to the directory tree.
- **df -h**: Displays disk space usage in a human-readable format.

---

### Demo 3: Viewing and Managing Inodes

**Objective**: Explore inodes on a filesystem.

**Commands**:

1. **Check Inode Usage**:

   ```bash
   df -i
   ```

   _Output Example_:

   ```
   Filesystem     Inodes IUsed IFree IUse% Mounted on
   /dev/sda2       1.5M  300k  1.2M   20% /
   /dev/sdb1       1.0M   50k  950k    5% /mnt/mydisk
   ```

2. **View the Inode Number of a File**:

   ```bash
   ls -i /etc/passwd
   ```

   _Output_:

   ```
   128394 /etc/passwd
   ```

3. **Find Files with Specific Inode Numbers**:
   ```bash
   find / -inum 128394
   ```
   _Output_:
   ```
   /etc/passwd
   ```

**Explanation**:

- **df -i**: Shows inode usage per filesystem.
- **ls -i**: Lists inode numbers alongside filenames.
- **find -inum**: Searches for files by inode number.

---

### Demo 4: Exploring Filesystem Hierarchy

**Objective**: Navigate and understand top-level directories.

**Commands**:

1. **List Contents of the Root Directory**:

   ```bash
   ls /
   ```

   _Output Example_:

   ```
   bin   dev  home  lib64       media  opt   root  sbin  sys  usr
   boot  etc  lib   lost+found  mnt    proc  run   srv   tmp  var
   ```

2. **Explore `/home` for User Directories**:

   ```bash
   ls /home
   ```

   _Output Example_:

   ```
   alice  bob
   ```

3. **Check System Configuration Files in `/etc`**:
   ```bash
   ls /etc
   ```
   _Output Example_:
   ```
   apache2  cron.d  hosts  passwd  shadow  ssh
   ```

**Explanation**:

- **`/bin`**: Essential user binaries.
- **`/dev`**: Device files.
- **`/home`**: User home directories.
- **`/etc`**: Configuration files.
- **`/lib64`**: Shared libraries.
- **`/media`**: Mount points for removable media.
- **`/mnt`**: Temporary mount points.
- **`/opt`**: Optional software packages.
- **`/proc`**: Virtual filesystem providing process and kernel information.
- **`/root`**: Root user's home directory.
- **`/run`**: Runtime data since the last boot.
- **`/sbin`**: System binaries.
- **`/srv`**: Data for services provided by the system.
- **`/sys`**: Interface to the kernel.
- **`/tmp`**: Temporary files.
- **`/usr`**: User utilities and applications.
- **`/var`**: Variable data files.

---

### Demo 5: Interacting with the Filesystem Using C and Syscalls

**Objective**: Demonstrate how to interact with the filesystem using C programming and system calls.

**Prerequisites**:

- Basic knowledge of C programming.
- GCC compiler installed (`sudo apt install build-essential`).

**Steps**:

1. **Create a C Program to List Files in a Directory**:

   ```c
   // list_files.c
   #include <stdio.h>
   #include <dirent.h>
   #include <errno.h>
   #include <string.h>

   int main(int argc, char *argv[]) {
       DIR *d;
       struct dirent *dir;
       if (argc < 2) {
           printf("Usage: %s <directory>\n", argv[0]);
           return 1;
       }
       d = opendir(argv[1]);
       if (d) {
           while ((dir = readdir(d)) != NULL) {
               printf("%s\n", dir->d_name);
           }
           closedir(d);
       } else {
           printf("Error opening directory '%s': %s\n", argv[1], strerror(errno));
           return 1;
       }
       return 0;
   }
   ```

2. **Compile the Program**:

   ```bash
   gcc -o list_files list_files.c
   ```

3. **Run the Program**:

   ```bash
   ./list_files /etc
   ```

   _Sample Output_:

   ```
   .
   ..
   apache2
   cron.d
   hosts
   passwd
   shadow
   ssh
   ```

**Explanation**:

- **`opendir`**: Opens a directory stream corresponding to the directory name.
- **`readdir`**: Reads the next directory entry.
- **`closedir`**: Closes the directory stream.
- **Error Handling**: Checks if the directory can be opened and handles errors gracefully.

---

### Demo 6: Creating a Custom Inode Manipulation Program

**Objective**: Create a C program that retrieves and displays inode information for a given file using syscalls.

**Prerequisites**:

- Basic knowledge of C programming.
- GCC compiler installed.

**Steps**:

1. **Create the C Program**:

   ```c
   // inode_info.c
   #include <stdio.h>
   #include <sys/stat.h>
   #include <errno.h>
   #include <string.h>

   int main(int argc, char *argv[]) {
       struct stat fileStat;
       if (argc < 2) {
           printf("Usage: %s <file>\n", argv[0]);
           return 1;
       }

       if (stat(argv[1], &fileStat) < 0) {
           printf("Error retrieving stats for '%s': %s\n", argv[1], strerror(errno));
           return 1;
       }

       printf("Inode Number: %ld\n", (long)fileStat.st_ino);
       printf("File Size: %ld bytes\n", (long)fileStat.st_size);
       printf("Number of Links: %ld\n", (long)fileStat.st_nlink);
       printf("File Permissions: ");
       printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
       printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
       printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
       printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
       printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
       printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
       printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
       printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
       printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
       printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
       printf("\n");

       return 0;
   }
   ```

2. **Compile the Program**:

   ```bash
   gcc -o inode_info inode_info.c
   ```

3. **Run the Program**:

   ```bash
   ./inode_info /etc/passwd
   ```

   _Sample Output_:

   ```
   Inode Number: 128394
   File Size: 675 bytes
   Number of Links: 1
   File Permissions: -rw-r--r--
   ```

**Explanation**:

- **`stat`**: Retrieves information about the file.
- **`st_ino`**: Inode number.
- **`st_size`**: Size of the file in bytes.
- **`st_nlink`**: Number of hard links.
- **`st_mode`**: File mode (type and permissions).
- **Permission Formatting**: Converts `st_mode` into a human-readable string.

**Advanced Extension**:

- Modify the program to list all inodes in a directory.
- Implement functionality to search for files with the same inode number (hard links).

---

### Demo 7: Inspecting the Master Boot Record

**Objective**: Examine the Master Boot Record (MBR) and understand its structure.

**Prerequisites**:

- Administrative privileges.
- `hexdump` installed (`sudo apt install bsdmainutils` if not present).

**Steps**:

1. **Identify the Boot Device**:

   - Typically, the primary hard drive is `/dev/sda`.
   - Confirm using `lsblk`:
     ```bash
     lsblk
     ```

2. **Read the MBR**:

   ```bash
   sudo dd if=/dev/sda bs=512 count=1 | hexdump -C
   ```

   _Sample Output_:

   ```
   00000000  55 aa 83 c4 00 00 00 00  02 01 01 00 00 00 00 00  |U................|
   00000010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000040  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000060  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
   00000070  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 55  |...............U|
   00000080  aa                                             |.|
   00000081
   ```

3. **Interpret the Partition Table**:

   - **Bytes 0-445**: Bootloader code.
   - **Bytes 446-509**: Partition table (4 entries, 16 bytes each).
   - **Bytes 510-511**: Boot signature (`55 AA`).

4. **Analyze the Partition Table**:

   - Each 16-byte entry represents a partition.
   - Use tools like `fdisk` for a more readable format:
     ```bash
     sudo fdisk -l /dev/sda
     ```

   _Sample Output_:

   ```
   Disk /dev/sda: 238.5 GiB, 256060514304 bytes, 500118192 sectors
   Units: sectors of 1 * 512 = 512 bytes
   Sector size (logical/physical): 512 bytes / 512 bytes
   I/O size (minimum/optimal): 512 bytes / 512 bytes
   Disklabel type: dos
   Disk identifier: 0x12345678

   Device     Boot Start       End   Sectors  Size Id Type
   /dev/sda1  *     2048    1050623    1048576  512M 83 Linux
   /dev/sda2       1050624 500118191 499067568 238G 83 Linux
   ```

**Explanation**:

- **`dd`**: Low-level data copying utility; used here to read the first 512 bytes (MBR).
- **`hexdump`**: Converts binary data into a hexadecimal format for readability.
- **`fdisk -l`**: Lists the partition table in a human-readable format.

**Safety Note**:

- Be cautious when using `dd` as it can overwrite data if used incorrectly.
- Always double-check the target device (`/dev/sda` in this example) to prevent data loss.

---

### Demo 8: Exploring Partition Tables with GPT and MBR

**Objective**: Compare and explore Partition Tables using GPT and MBR.

**Prerequisites**:

- `gdisk` installed (`sudo apt install gdisk`).

**Steps**:

1. **Check Partition Table Type**:

   ```bash
   sudo fdisk -l /dev/sda
   ```

   _Output Example_:

   ```
   Disk /dev/sda: 238.5 GiB, 256060514304 bytes, 500118192 sectors
   Units: sectors of 1 * 512 = 512 bytes
   Sector size (logical/physical): 512 bytes / 512 bytes
   I/O size (minimum/optimal): 512 bytes / 512 bytes
   Disklabel type: dos
   Disk identifier: 0x12345678
   ```

   - **Disklabel type**: Indicates `dos` (MBR) or `gpt` (GUID Partition Table).

2. **Convert MBR to GPT** _(Optional and Risky)_:

   - **Warning**: Converting partition tables can lead to data loss. Ensure you have backups before proceeding.

   ```bash
   sudo gdisk /dev/sda
   ```

   - Follow prompts to convert from MBR to GPT.

3. **Explore GPT Partition Table**:

   ```bash
   sudo gdisk -l /dev/sda
   ```

   _Sample Output_:

   ```
   Disk /dev/sda: 238.5 GiB, 256060514304 bytes, 500118192 sectors
   Model: ...
   Sector size (logical/physical): 512/512 bytes
   Disk identifier (GUID): XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
   Partition table holds up to 128 partitions
   First usable sector is 34, last usable sector is 500118158
   Partitions will be aligned on 2048-sector boundaries
   Total free space is 0 sectors (0 bytes)

      Number  Start (sector)    End (sector)  Size       Code  Name
         1          2048        1050623  512.0 MiB   8300  Linux filesystem
         2        1050624        500118191  238.0 GiB   8300  Linux filesystem
   ```

4. **Difference Between GPT and MBR**:
   - **GPT** offers more partitions, larger disk sizes, redundancy, and data integrity through CRC checks.
   - **MBR** is limited to 4 primary partitions and supports disks up to 2TB.

**Explanation**:

- **`gdisk`**: GPT fdisk, a tool for partitioning disks using GPT.
- **Conversion Risks**: Always ensure data is backed up before altering partition tables.

---

### Demo 9: Installing and Configuring a Second Stage Bootloader

**Objective**: Install and configure a second stage bootloader (e.g., GRUB) to manage the boot process.

**Prerequisites**:

- Administrative privileges.
- Internet connection to install bootloader packages.

**Steps**:

1. **Install GRUB**:

   ```bash
   sudo apt update
   sudo apt install grub-pc
   ```

2. **Configure GRUB**:

   - During installation, select the disk where GRUB should be installed (e.g., `/dev/sda`).

3. **Update GRUB Configuration**:

   ```bash
   sudo update-grub
   ```

   _Sample Output_:

   ```
   Generating grub configuration file ...
   Found linux image: /boot/vmlinuz-5.4.0-42-generic
   Found initrd image: /boot/initrd.img-5.4.0-42-generic
   Found linux image: /boot/vmlinuz-5.4.0-40-generic
   Found initrd image: /boot/initrd.img-5.4.0-40-generic
   done
   ```

4. **Reinstall GRUB to MBR (if necessary)**:

   ```bash
   sudo grub-install /dev/sda
   ```

5. **Verify GRUB Installation**:

   ```bash
   sudo grub-install --version
   ```

   _Sample Output_:

   ```
   grub-install (GRUB) 2.04-1ubuntu26.8
   ```

6. **Reboot and Test**:
   ```bash
   sudo reboot
   ```
   - During reboot, GRUB menu should appear, allowing selection of available kernels or operating systems.

**Explanation**:

- **GRUB Installation**: Sets up the second stage bootloader to manage OS selection and kernel loading.
- **`update-grub`**: Scans for installed kernels and updates the GRUB configuration.
- **Verification**: Ensures GRUB is correctly installed and functioning.

**Advanced Extension**:

- Customize GRUB themes and configurations by editing `/etc/default/grub` and adding scripts in `/etc/grub.d/`.
- Implement multi-boot setups with other operating systems.

---

### Demo 10: Inspecting the Superblock

**Objective**: Examine the superblock of a filesystem to understand its metadata.

**Prerequisites**:

- Administrative privileges.
- `dumpe2fs` installed (`sudo apt install e2fsprogs` if not present).

**Steps**:

1. **Identify the Filesystem Device**:

   - Use `lsblk` to identify the device (e.g., `/dev/sda1`).

   ```bash
   lsblk
   ```

   _Sample Output_:

   ```
   NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
   sda      8:0    0 238.5G  0 disk
   ├─sda1   8:1    0   512M  0 part /boot
   └─sda2   8:2    0 238G    0 part /
   sdb      8:16   1  14.5G  0 disk
   └─sdb1   8:17   1  14.5G  0 part /media/usb
   ```

2. **View Superblock Information**:

   ```bash
   sudo dumpe2fs /dev/sda1 | grep -i 'super block'
   ```

   _Sample Output_:

   ```
   Superblock backups stored on blocks:
   32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208, 4096000, 7962624, 11239424
   ```

3. **Display Detailed Superblock Information**:

   ```bash
   sudo dumpe2fs /dev/sda1 | less
   ```

   _Sample Output Snippet_:

   ```
   Filesystem volume name:   MyData
   Last mounted on:          /mnt/mydisk
   Filesystem UUID:          123e4567-e89b-12d3-a456-426614174000
   Filesystem magic number:  0xEF53
   Filesystem state:         clean
   ...
   ```

4. **Extract Specific Superblock Fields**:

   - To extract specific information, use `grep` or other text processing tools.

   **Example**: Get the block size.

   ```bash
   sudo dumpe2fs /dev/sda1 | grep 'Block size:'
   ```

   _Sample Output_:

   ```
   Block size:               4096
   ```

5. **Modify Superblock Parameters** _(Advanced and Risky)_:

   - **Warning**: Altering superblock parameters can corrupt the filesystem. Proceed with caution and ensure backups are available.

   ```bash
   sudo tune2fs -m 1 /dev/sda1
   ```

   - Sets the reserved blocks percentage to 1%.

**Explanation**:

- **`dumpe2fs`**: Displays the superblock and block group information for an ext2/ext3/ext4 filesystem.
- **Superblock Backups**: Multiple copies of the superblock exist to aid in recovery.
- **Detailed Information**: Provides comprehensive metadata about the filesystem, essential for maintenance and troubleshooting.

**Advanced Extension**:

- **Superblock Recovery**: Learn how to recover a corrupted superblock using backup copies.
  ```bash
  sudo e2fsck -b 32768 /dev/sda1
  ```
- **Understanding Superblock Fields**: Delve deeper into each superblock field and its implications on filesystem performance and integrity.

---

## Conclusion

The Linux filesystem and storage systems offer robust, scalable, and flexible solutions for managing data. By understanding the historical evolution, types of storage, and key concepts like inodes, dentries, and the superblock, along with the intricacies of the Master Boot Record (MBR) and the bootloader process, you can effectively manage Linux environments. The provided examples and demos, especially those involving C programming, system calls, and bootloader configurations, enhance your practical knowledge and skills, enabling you to interact with the filesystem and storage at a deeper level.

---

## Additional Resources

- **Filesystem Hierarchy Standard (FHS)**: [FHS 3.0](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html)
- **Linux Documentation Project**: [TLDP](https://www.tldp.org/)
- **GNU Coreutils Manual**: [Coreutils](https://www.gnu.org/software/coreutils/manual/)
- **The Linux Command Line** by William Shotts
- **Arch Linux Wiki - Filesystem Hierarchy**: [Arch Wiki](https://wiki.archlinux.org/title/Filesystem_Hierarchy)
- **Understanding Inodes**: [Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/92394/what-is-an-inode)
- **Understanding Dentries**: [Kernel.org - Dentries](https://www.kernel.org/doc/html/latest/filesystems/dcache.html)
- **C Programming in Linux**: [The Linux Programming Interface](https://man7.org/tlpi/)
- **System Call Interface**: [Linux Man Pages](https://man7.org/linux/man-pages/dir_section_2.html)
- **GCC Documentation**: [GNU GCC](https://gcc.gnu.org/onlinedocs/)
- **Master Boot Record (MBR) Overview**: [Wikipedia - Master Boot Record](https://en.wikipedia.org/wiki/Master_boot_record)
- **GPT vs. MBR Explained**: [Red Hat - MBR vs GPT](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/storage_administration_guide/sect-storage_administration_guide-gpt-vs-mbr)
- **Understanding Superblocks**: [Wikipedia - Superblock](<https://en.wikipedia.org/wiki/Superblock_(computer_filesystem)>)

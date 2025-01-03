# Linux Fundamentals

**Module 1 of Embedded Linux Diploma**

---

## Module Overview

Module 1: **Linux Fundamentals** offers a comprehensive introduction to the Linux operating system, covering its history, architecture, and essential administrative skills. This module is meticulously structured into 11 sessions, each focusing on critical aspects of Linux usage, from basic commands and shell scripting to advanced topics like system programming and networking. Through a blend of theoretical lessons and practical exercises, students will develop a solid foundation in Linux administration, enabling them to efficiently manage and utilize Linux-based systems in embedded environments.

---

## Table of Contents

- [Linux Fundamentals](#linux-fundamentals)
  - [Module Overview](#module-overview)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction to Linux](#1-introduction-to-linux)
    - [Session 01: Introduction to Linux and Linux History](#session-01-introduction-to-linux-and-linux-history)
    - [Session 01: The Linux Programming Interface](#session-01-the-linux-programming-interface)
  - [2. Basic Linux Commands and Shells](#2-basic-linux-commands-and-shells)
    - [Session 02: Linux Basic Commands](#session-02-linux-basic-commands)
    - [Session 02: Linux Magic Numbers System Programming Guide](#session-02-linux-magic-numbers-system-programming-guide)
    - [Session 02: Types of Shells in Linux](#session-02-types-of-shells-in-linux)
    - [Session 02: Ubuntu Boot Process Guide](#session-02-ubuntu-boot-process-guide)
    - [Session 02: Vim Mastery](#session-02-vim-mastery)
  - [3. Advanced Command-Line Tools](#3-advanced-command-line-tools)
    - [Session 03: Getopt and Getopt Long Guide](#session-03-getopt-and-getopt-long-guide)
    - [Session 03: Journaling in Linux Filesystems](#session-03-journaling-in-linux-filesystems)
    - [Session 03: Linux Users and Groups Guide](#session-03-linux-users-and-groups-guide)
    - [Session 03: Wildcard CLI Tasks](#session-03-wildcard-cli-tasks)
    - [Session 03: Wildcard CLI Tasks Solution](#session-03-wildcard-cli-tasks-solution)
    - [Session 03: Wildcards CLI Guide](#session-03-wildcards-cli-guide)
  - [4. Bash Scripting and Process Management](#4-bash-scripting-and-process-management)
    - [Session 04: Introduction to Bash Scripting](#session-04-introduction-to-bash-scripting)
    - [Session 04: Bash Scripting Task Guide](#session-04-bash-scripting-task-guide)
    - [Session 04: Intro to Process Management in Linux](#session-04-intro-to-process-management-in-linux)
    - [Session 04: Linux File Permissions and Special Bits](#session-04-linux-file-permissions-and-special-bits)
    - [Session 04: Linux File Permissions Demonstration](#session-04-linux-file-permissions-demonstration)
    - [Session 04: Linux `su` Command Guide with Environment](#session-04-linux-su-command-guide-with-env)
    - [Session 04: Ubuntu Package Management Guide](#session-04-ubuntu-package-management-guide)
  - [5. C Programming and System Calls](#5-c-programming-and-system-calls)
    - [Session 05: C Build Process Step by Step](#session-05-c-build-process-step-by-step)
    - [Session 05: ELF File Analysis Readme](#session-05-elf-file-analysis-readme)
    - [Session 05: Linux Architecture Layered Design](#session-05-linux-architecture-layered-design)
    - [Session 05: Static and Shared Libraries in C](#session-05-static-and-shared-libraries-in-c)
    - [Session 05: Syscalls in Linux](#session-05-syscalls-in-linux)
  - [6. Advanced Bash and Networking](#6-advanced-bash-and-networking)
    - [Session 06: Bash Exercises with Solutions](#session-06-bash-exercises-with-solutions)
    - [Session 06: Bash Scripting Guide](#session-06-bash-scripting-guide)
    - [Session 06: Cut Command Guide](#session-06-cut-command-guide)
    - [Session 06: Linux Networking Guide](#session-06-linux-networking-guide)
    - [Session 06: Sed Command Guide](#session-06-sed-command-guide)
    - [Session 06: Tar Command Guide](#session-06-tar-command-guide)
  - [7. Filesystem and Boot Management](#7-filesystem-and-boot-management)
    - [Session 07: Linux Filesystem Storage Guide](#session-07-linux-filesystem-storage-guide)
    - [Session 07: Master Boot Record Comprehensive Guide](#session-07-master-boot-record-comprehensive-guide)
    - [Session 07: MBR Partitioning and EBR Guide](#session-07-mbr-partitioning-and-ebr-guide)
    - [Session 07: Secure Boot Demo Guide](#session-07-secure-boot-demo-guide)
    - [Session 07: Secure Boot Linux Guide](#session-07-secure-boot-linux-guide)
    - [Session 07: Simple Linux Distro](#session-07-simple-linux-distro)
    - [Session 07: Special Bits Linux Permissions Demo](#session-07-special-bits-linux-permissions-demo)
  - [8. Filesystem Operations and Virtualization](#8-filesystem-operations-and-virtualization)
    - [Session 08: Copy on Write in Linux](#session-08-copy-on-write-in-linux)
    - [Session 08: Guide to `dmesg` in Linux](#session-08-guide-to-dmesg-in-linux)
    - [Session 08: Linux File Operations and Filesystem Guide](#session-08-linux-file-operations-and-filesystem-guide)
    - [Session 08: Linux Filesystem Operations Advanced](#session-08-linux-filesystem-operations-advanced)
    - [Session 08: Linux Links Guide](#session-08-linux-links-guide)
    - [Session 08: Linux Mounting Guide](#session-08-linux-mounting-guide)
    - [Session 08: USB Partition Format Demo](#session-08-usb-partition-format-demo)
    - [Session 08: Virtual Filesystems in Linux](#session-08-virtual-filesystems-in-linux)
  - [9. Bootloader and Process Management](#9-bootloader-and-process-management)
    - [Session 09: Guide to the GRUB Menu Configuration](#session-09-guide-to-the-grub-menu-configuration)
    - [Session 09: Linux `bg` and `fg` Process Management](#session-09-linux-bg-fg-process-management)
    - [Session 09: Linux Daemon Process Guide](#session-09-linux-daemon-process-guide)
    - [Session 09: Linux Process Priority and Niceness Guide](#session-09-linux-process-priority-and-niceness-guide)
    - [Session 09: Linux Signals Guide](#session-09-linux-signals-guide)
    - [Session 09: PGID Management Guide](#session-09-pgid-management-guide)
    - [Session 09: Simple Linux Distro](#session-09-simple-linux-distro)
  - [10. Networking and Virtualization](#10-networking-and-virtualization)
    - [Session 10: `iptables` Firewall Cheatsheet](#session-10-iptables-firewall-cheatsheet)
    - [Session 10: Linux Virtual and Tunnel Interfaces Guide](#session-10-linux-virtual-and-tunnel-interfaces-guide)
    - [Session 10: Networking and Virtualization in Linux](#session-10-networking-and-virtualization-in-linux)
    - [Session 10: Networking Virtualization Guide](#session-10-networking-virtualization-guide)
    - [Session 10: SSH Comprehensive Guide](#session-10-ssh-comprehensive-guide)
    - [Session 10: Yocto Package Installation](#session-10-yocto-package-installation)
  - [11. Advanced Bash Scripting](#11-advanced-bash-scripting)
    - [Session 11: Advanced Bash Scripting Guide](#session-11-advanced-bash-scripting-guide)
    - [Session 11: Bash Parameter Expansion Guide](#session-11-bash-parameter-expansion-guide)
    - [Session 11: Custom CLI Prompt and Output Colors](#session-11-custom-cli-prompt-and-output-colors)
  - [Additional Resources](#additional-resources)
  - [Contact and Support](#contact-and-support)

---

## 1. Introduction to Linux

### Session 01: Introduction to Linux and Linux History

- **Introduction to Linux**: Overview of the Linux operating system, its origins, and evolution.
- **Linux History**: Detailed exploration of the development milestones and key contributors to Linux.

### Session 01: The Linux Programming Interface

- **Linux Programming Interface**: Comprehensive guide to system calls, libraries, and application programming on Linux.

---

## 2. Basic Linux Commands and Shells

### Session 02: Linux Basic Commands

- **Essential Commands**: Introduction to fundamental Linux commands for file manipulation, navigation, and system monitoring.

### Session 02: Linux Magic Numbers System Programming Guide

- **Magic Numbers**: Understanding magic numbers in Linux for system programming and file identification.

### Session 02: Types of Shells in Linux

- **Shell Variants**: Overview of different shell environments available in Linux, their features, and use cases.

### Session 02: Ubuntu Boot Process Guide

- **Boot Process**: Step-by-step explanation of the Ubuntu boot sequence, including BIOS, bootloader, and initialization.

### Session 02: Vim Mastery

- **Vim Editor**: Advanced techniques and tips for efficient text editing using Vim.

---

## 3. Advanced Command-Line Tools

### Session 03: Getopt and Getopt Long Guide

- **Argument Parsing**: Utilizing `getopt` and `getopt_long` for handling command-line arguments in scripts and applications.

### Session 03: Journaling in Linux Filesystems

- **Journaling Filesystems**: Understanding the role and implementation of journaling in Linux filesystems for data integrity.

### Session 03: Linux Users and Groups Guide

- **User Management**: Managing users and groups, permissions, and access control in Linux.

### Session 03: Wildcard CLI Tasks

- **Wildcard Operations**: Practical exercises using wildcards in the command line for efficient file handling.

### Session 03: Wildcard CLI Tasks Solution

- **Solutions**: Detailed solutions to wildcard CLI tasks for self-assessment and learning reinforcement.

### Session 03: Wildcards CLI Guide

- **Comprehensive Wildcard Guide**: In-depth exploration of wildcard usage in various shell environments.

---

## 4. Bash Scripting and Process Management

### Session 04: Introduction to Bash Scripting

- **Bash Basics**: Fundamentals of writing and executing Bash scripts for automation and task management.

### Session 04: Bash Scripting Task Guide

- **Practical Tasks**: Step-by-step tasks to practice and enhance Bash scripting skills.

### Session 04: Intro to Process Management in Linux

- **Process Control**: Managing and controlling processes, understanding process states and lifecycle.

### Session 04: Linux File Permissions and Special Bits

- **File Permissions**: Detailed explanation of Linux file permission models and special permission bits.

### Session 04: Linux File Permissions Demonstration

- **Hands-On Demo**: Practical demonstration of setting and modifying file permissions in Linux.

### Session 04: Linux `su` Command Guide with Environment

- **`su` Command**: Comprehensive guide to using the `su` command for user switching and environment management.

### Session 04: Ubuntu Package Management Guide

- **Package Management**: Managing software packages in Ubuntu using `apt`, including installation, updates, and removals.

---

## 5. C Programming and System Calls

### Session 05: C Build Process Step by Step

- **Build Process**: Detailed walkthrough of compiling and building C programs in a Linux environment.

### Session 05: ELF File Analysis Readme

- **ELF Files**: Understanding the Executable and Linkable Format (ELF) for binaries in Linux.

### Session 05: Linux Architecture Layered Design

- **System Architecture**: Exploration of Linux's layered architecture and its components.

### Session 05: Static and Shared Libraries in C

- **Libraries in C**: Differences between static and shared libraries, and their usage in C programming.

### Session 05: Syscalls in Linux

- **System Calls**: Comprehensive guide to using system calls for interacting with the Linux kernel.

---

## 6. Advanced Bash and Networking

### Session 06: Bash Exercises with Solutions

- **Practice Exercises**: A set of advanced Bash scripting exercises with provided solutions for self-learning.

### Session 06: Bash Scripting Guide

- **Advanced Scripting**: Techniques and best practices for writing robust and efficient Bash scripts.

### Session 06: Cut Command Guide

- **Text Processing**: Utilizing the `cut` command for extracting sections from each line of input.

### Session 06: Linux Networking Guide

- **Networking Basics**: Fundamental networking concepts and commands in Linux.

### Session 06: Sed Command Guide

- **Stream Editing**: Mastering the `sed` command for advanced text manipulation and processing.

### Session 06: Tar Command Guide

- **Archiving Files**: Using the `tar` command for creating and extracting archive files.

---

## 7. Filesystem and Boot Management

### Session 07: Linux Filesystem Storage Guide

- **Storage Management**: Understanding storage devices, partitions, and filesystem types in Linux.

### Session 07: Master Boot Record Comprehensive Guide

- **MBR Details**: In-depth guide to the Master Boot Record, its structure, and management.

### Session 07: MBR Partitioning and EBR Guide

- **Partitioning Schemes**: Exploring MBR and Extended Boot Record partitioning for disk management.

### Session 07: Secure Boot Demo Guide

- **Secure Boot**: Demonstration of implementing Secure Boot in a Linux environment.

### Session 07: Secure Boot Linux Guide

- **Secure Boot Configuration**: Step-by-step guide to configuring Secure Boot on Linux systems.

### Session 07: Simple Linux Distro

- **Custom Distro Creation**: Basics of creating and customizing a simple Linux distribution.

### Session 07: Special Bits Linux Permissions Demo

- **Advanced Permissions**: Practical demonstration of using special bits in Linux file permissions.

---

## 8. Filesystem Operations and Virtualization

### Session 08: Copy on Write in Linux

- **CoW Mechanism**: Understanding the Copy-on-Write technique and its applications in Linux.

### Session 08: Guide to `dmesg` in Linux

- **Kernel Messages**: Utilizing the `dmesg` command to view and interpret kernel messages.

### Session 08: Linux File Operations and Filesystem Guide

- **File Operations**: Comprehensive guide to performing file operations and managing filesystems in Linux.

### Session 08: Linux Filesystem Operations Advanced

- **Advanced Filesystem Tasks**: Exploring advanced filesystem operations and maintenance techniques.

### Session 08: Linux Links Guide

- **File Linking**: Understanding and creating hard and symbolic links in Linux.

### Session 08: Linux Mounting Guide

- **Mounting Filesystems**: Detailed instructions on mounting and unmounting filesystems in Linux.

### Session 08: USB Partition Format Demo

- **USB Management**: Demonstration of partitioning and formatting USB drives in Linux.

### Session 08: Virtual Filesystems in Linux

- **Virtual FS**: Exploring virtual filesystems and their roles within the Linux operating system.

---

## 9. Bootloader and Process Management

### Session 09: Guide to the GRUB Menu Configuration

- **GRUB Configuration**: Detailed guide to configuring the GRUB bootloader for system customization.

### Session 09: Linux `bg` and `fg` Process Management

- **Background and Foreground Processes**: Managing process states using `bg` and `fg` commands.

### Session 09: Linux Daemon Process Guide

- **Daemon Processes**: Understanding and managing daemon processes in Linux.

### Session 09: Linux Process Priority and Niceness Guide

- **Process Prioritization**: Managing process priorities and niceness levels for optimal system performance.

### Session 09: Linux Signals Guide

- **Signal Handling**: Comprehensive guide to sending, receiving, and handling signals in Linux.

### Session 09: PGID Management Guide

- **Process Group ID**: Understanding and managing Process Group IDs (PGIDs) in Linux.

### Session 09: Simple Linux Distro

- **Custom Distro Creation**: Further exploration into creating and customizing a simple Linux distribution.

---

## 10. Networking and Virtualization

### Session 10: `iptables` Firewall Cheatsheet

- **Firewall Management**: Quick reference guide for managing firewalls using `iptables` in Linux.

### Session 10: Linux Virtual and Tunnel Interfaces Guide

- **Virtual Interfaces**: Understanding and configuring virtual and tunnel interfaces in Linux networking.

### Session 10: Networking and Virtualization in Linux

- **Network Virtualization**: Exploring networking concepts and virtualization technologies within Linux.

### Session 10: Networking Virtualization Guide

- **Advanced Networking**: Detailed guide to advanced networking and virtualization setups in Linux.

### Session 10: SSH Comprehensive Guide

- **Secure Shell (SSH)**: Comprehensive guide to using SSH for secure remote access and management.

### Session 10: Yocto Package Installation

- **Yocto Project**: Instructions for installing and managing packages using the Yocto Project in Linux.

---

## 11. Advanced Bash Scripting

### Session 11: Advanced Bash Scripting Guide

- **Advanced Techniques**: Exploring advanced Bash scripting techniques for complex automation tasks.

### Session 11: Bash Parameter Expansion Guide

- **Parameter Expansion**: Mastering parameter expansion for dynamic variable handling in Bash scripts.

### Session 11: Custom CLI Prompt and Output Colors

- **Customization**: Customizing the command-line interface with personalized prompts and color schemes.

---

## Additional Resources

- [Official Linux Documentation](https://www.kernel.org/doc/)
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Vim Documentation](https://www.vim.org/docs.php)
- [GRUB Bootloader Documentation](https://www.gnu.org/software/grub/documentation/)
- [Yocto Project Documentation](https://www.yoctoproject.org/docs/)
- [iptables Tutorial](https://iptables-tutorial.frozentux.net/iptables-tutorial.html)

## Contact and Support

For any queries or support related to this module, please reach out to the course instructor or visit the [course forum](https://forum.embedded-linux-diploma.com).

---

**© 2025 Embedded Linux Diploma Program. All rights reserved.**

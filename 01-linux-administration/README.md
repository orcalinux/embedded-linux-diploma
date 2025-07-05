# Linux Fundamentals

**Module 1 of Embedded Linux Diploma**

---

## Module Overview

Module 1: **Linux Fundamentals** offers a comprehensive introduction to the Linux operating system, covering its history, architecture, and essential administrative skills. This module is now structured into **14 sessions**, each focusing on critical aspects of Linux usage—from basic commands and shell scripting to advanced topics like system programming, network administration, and bootloaders. Through a blend of theoretical lessons and practical exercises, students will develop a solid foundation in Linux administration, enabling them to efficiently manage and utilize Linux-based systems in embedded environments.

---

## Table of Contents

- [Linux Fundamentals](#linux-fundamentals)
  - [Module Overview](#module-overview)
  - [Table of Contents](#table-of-contents)
  - [Session 01: Introduction to Linux & Its History](#session-01-introduction-to-linux--its-history)
  - [Session 02: Essential Linux Commands, Shells, and Boot Process](#session-02-essential-linux-commands-shells-and-boot-process)
  - [Session 03: Advanced CLI Tools, File System Journaling, and User Management](#session-03-advanced-cli-tools-file-system-journaling-and-user-management)
  - [Session 04: Bash Scripting Basics, Process Management, and File Permissions](#session-04-bash-scripting-basics-process-management-and-file-permissions)
  - [Session 05: C Build Process, Linux Architecture, and System Calls](#session-05-c-build-process-linux-architecture-and-system-calls)
  - [Session 06: Bash Exercises, Networking Fundamentals, and Core CLI Tools](#session-06-bash-exercises-networking-fundamentals-and-core-cli-tools)
  - [Session 07: Filesystems, MBR Partitioning, and Secure Boot](#session-07-filesystems-mbr-partitioning-and-secure-boot)
  - [Session 08: Advanced Filesystem Operations, Copy-on-Write, and System Utilities](#session-08-advanced-filesystem-operations-copy-on-write-and-system-utilities)
  - [Session 09: ARM64 QEMU, Process Management, and GRUB Configuration](#session-09-arm64-qemu-process-management-and-grub-configuration)
  - [Session 10: Computer Networking Fundamentals](#session-10-computer-networking-fundamentals)
  - [Session 11: Firewalls, Virtual Network Interfaces, and SSH](#session-11-firewalls-virtual-network-interfaces-and-ssh)
  - [Session 12: Getting Started with Yocto & Networking Virtualization](#session-12-getting-started-with-yocto--networking-virtualization)
  - [Session 13: Advanced Bash Scripting and Custom CLI Features](#session-13-advanced-bash-scripting-and-custom-cli-features)
  - [Session 14: Bash Script Projects & Advanced Linux Lab Setup](#session-14-bash-script-projects--advanced-linux-lab-setup)
  - [Additional Resources](#additional-resources)
  - [Contact and Support](#contact-and-support)

---

## Session 01: Introduction to Linux & Its History

**Contents:**
- `introduction-to-linux-and-linux-history.pdf`
- `the-linux-programming-interface.pdf`

**Highlights:**
- Origins and evolution of the Linux OS  
- Key milestones and contributors to Linux  
- Introduction to system calls and the Linux programming interface  

---

## Session 02: Essential Linux Commands, Shells, and Boot Process

**Contents:**
- `linux-basic-commands.pdf`
- `linux-magic-numbers-system-programming-guide.pdf`
- `types-of-shells-in-linux.pdf`
- `ubuntu-boot-process-guide.pdf`
- `vim-mastery.pdf`

**Highlights:**
- Fundamental Linux commands for file manipulation and system monitoring  
- Understanding magic numbers in system programming  
- Overview of different Linux shell environments  
- Ubuntu’s boot sequence and key initialization steps  
- Mastering Vim for efficient text editing  

---

## Session 03: Advanced CLI Tools, File System Journaling, and User Management

**Contents:**
- `getopt-getopt-long-guide.md`
- `journaling-in-linux-filesystems.pdf`
- `linux-users-and-groups-guide.pdf`
- `wildcard-cli-tasks.pdf`
- `wildcard-cli-tasks-solution.pdf`
- `wildcards_cli_guide.pdf`

**Highlights:**
- Parsing command-line arguments using `getopt` and `getopt_long`  
- Understanding journaling in Linux filesystems for data integrity  
- Managing users, groups, and permissions  
- Working with wildcards for efficient file operations  

---

## Session 04: Bash Scripting Basics, Process Management, and File Permissions

**Contents:**
- `bash-scripting-task-guide.md`
- `introduction-to-bash-scripting.md`
- `intro-to-process-management-in-linux.md`
- `linux-file-permissions-and-special-bits.md`
- `linux-file-permissions-demonstration.md`
- `linux_su_command_guide_with_env.md`
- `ubuntu-package-management-guide.md`

**Highlights:**
- Fundamentals of Bash scripting and automation  
- Basic process management: states, lifecycle, and control  
- Detailed exploration of Linux file permissions and special bits  
- Using `su` effectively and handling environment variables  
- Introduction to Ubuntu package management with `apt`  

---

## Session 05: C Build Process, Linux Architecture, and System Calls

**Contents:**
- `c_build_process_step_by_step.md`
- `elf_file_analysis_readme.md`
- `linux_architecture_layered_design.md`
- `static_and_shared_libraries_in_c.md`
- `syscalls_in_linux.md`

**Highlights:**
- Step-by-step C compilation and build process  
- Analyzing ELF files in Linux  
- Layered design of the Linux operating system  
- Differences between static and shared libraries  
- Writing and using system calls in Linux  

---

## Session 06: Bash Exercises, Networking Fundamentals, and Core CLI Tools

**Contents:**
- `bash_exercises_with_solutions.md`
- `bash_scripting_guide.md`
- `cut_command_guide.md`
- `linux_networking_guide.md`
- `sed_command_guide.md`
- `tar_command_guide.md`

**Highlights:**
- Hands-on Bash scripting exercises (with solutions)  
- Best practices for writing robust Bash scripts  
- Using `cut` and `sed` for advanced text processing  
- Introduction to Linux networking essentials  
- Archiving and extracting files with `tar`  

---

## Session 07: Filesystems, MBR Partitioning, and Secure Boot

**Contents:**
- `linux-filesystem-storage-guide.md`
- `master-boot-record-comprehensive-guide.md`
- `mbr-partitioning-and-ebr-guide.md`
- `secure_boot_demo_guide.md`
- `secure_boot_linux_guide.md`
- `simple-linux-distro.md`
- `special_bits_linux_permissions_demo.md`

**Highlights:**
- Storage management, partitions, and filesystem types in Linux  
- Comprehensive look at Master Boot Record (MBR) and Extended Boot Record (EBR)  
- Configuring and demonstrating Secure Boot in a Linux environment  
- Building a simple Linux distro from scratch  
- Advanced file permission demos and special bits  

---

## Session 08: Advanced Filesystem Operations, Copy-on-Write, and System Utilities

**Contents:**
- `copy-on-write-in-Linux.md`
- `guide-to-dmesg-in-linux.md`
- `linux_file_operations_and_filesystem_guide.md`
- `linux_filesystem_operations_advanced.md`
- `linux_links_guide.md`
- `linux_mounting_guide.md`
- `usb_partition_format_demo.md`
- `virtual_filesy_tems_in_linux.md`

**Highlights:**
- Copy-on-write (CoW) principles and use cases  
- Interpreting kernel messages with `dmesg`  
- Advanced file operations and maintenance tasks  
- Working with hard and symbolic links  
- Mounting and unmounting filesystems  
- Formatting and partitioning USB devices  
- Overview of virtual filesystems in Linux  

---

## Session 09: ARM64 QEMU, Process Management, and GRUB Configuration

**Contents:**
- `arm64_qemu_pl011.md`
- `guide-to-the-grub-menu-configuration.md`
- `linux_bg_fg_process_management.md`
- `linux_daemon_process_guide.md`
- `linux_process_priority_niceness_guide.md`
- `linux_signals_guide.md`
- `pgid_management_guide.md`
- `process_groups_and_sessions.md`
- `simple-linux-distro.md`
- `usb_monitor_daemon.md`

**Highlights:**
- Running ARM64 kernels under QEMU with PL011 console support  
- Configuring the GRUB bootloader for Linux systems  
- Managing processes in background/foreground modes  
- Daemon processes, priorities, niceness, and signals  
- Creating custom Linux distributions  
- Monitoring USB devices with a daemon  

---

## Session 10: Computer Networking Fundamentals

**Contents:**
- `chapter01_introduction.pdf`
- `chapter02_application_layer.pdf`
- `chapter03_transport_layer.pdf`
- `chapter04_network_layer_data_plane.pdf`
- `chapter05_network_layer_control_plane.pdf`
- `chapter06_the_link_layer_and_lans.pdf`
- `chapter07_wireless_and_mobile_networks.pdf`
- `chapter08_security.pdf`

**Highlights:**
- Comprehensive introduction to computer networking concepts  
- In-depth coverage of the OSI model layers (Application, Transport, Network, Link)  
- Wireless/mobile networking overviews  
- Network security fundamentals  

---

## Session 11: Firewalls, Virtual Network Interfaces, and SSH

**Contents:**
- `iptables_firewall_cheatsheet.md`
- `linux_virtual_and_tunnel_interfaces_guide.md`
- `ssh-comprehensive-guide.md`

**Highlights:**
- Managing firewall rules with `iptables`  
- Configuring virtual and tunnel network interfaces in Linux  
- Secure Shell (SSH) best practices for remote system administration  

---

## Session 12: Getting Started with Yocto & Networking Virtualization

**Contents:**
- `getting-started-with-yocto.pdf`
- `networking_virtualization_guide.md`
- `yocto-package-installation.md`

**Highlights:**
- Introduction to the Yocto Project and its build environment  
- Basics of networking virtualization on Linux  
- Installing and managing packages within Yocto-based systems  

---

## Session 13: Advanced Bash Scripting and Custom CLI Features

**Contents:**
- `advanced_bash_scripting_guide.md`
- `bash_parameter_expansion_guide.md`
- `custom_cli_prompt_and_output_colors.md`

**Highlights:**
- Advanced Bash scripting techniques for complex automation  
- Mastering parameter expansion for dynamic scripting  
- Customizing the CLI prompt and adding color output for readability  

---

## Session 14: Bash Script Projects & Advanced Linux Lab Setup

**Contents:**
- `images/` (directory for supporting images)
- `linux_lab_setup.md`
- `project1-user-and-account-creation.md`

**Highlights:**
- Hands-on Bash scripting projects to reinforce scripting skills  
- Setting up a comprehensive Linux lab environment  
- Practical user and account creation workflows for real-world administration  

---

## Additional Resources

- [Official Linux Documentation](https://www.kernel.org/doc/)
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Vim Documentation](https://www.vim.org/docs.php)
- [GRUB Bootloader Documentation](https://www.gnu.org/software/grub/documentation/)
- [Yocto Project Documentation](https://www.yoctoproject.org/docs/)
- [iptables Tutorial](https://iptables-tutorial.frozentux.net/iptables-tutorial.html)

## Contact and Support

For any queries or support related to this module, please reach out to the course instructor.

---

**© 2025 Embedded Linux Diploma Program. All rights reserved.**

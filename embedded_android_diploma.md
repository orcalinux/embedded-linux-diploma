# Comprehensive Embedded Linux, Android, Containerization, and Qt Diploma – Full Course Content

This document provides a **complete** overview of the diploma’s curriculum, covering Embedded Android, Containerization (Docker and Kubernetes), Yocto, Modern C++, and Qt (Core and GUI). Each module is designed to give you in-depth knowledge and hands-on experience in building, deploying, and customizing embedded systems and modern C++ applications using Qt.

## Table of Contents

1. [Android-Focused Modules](#android-focused-modules)  
   1.1. [Session 1: Introduction to Embedded Android](#session-1-introduction-to-embedded-android)  
   1.2. [Session 2: Building and Flashing Android Source](#session-2-building-and-flashing-android-source)  
   1.3. [Session 3: Exploring and Customizing Android System](#session-3-exploring-and-customizing-android-system)  
   1.4. [Session 4: Advanced Android Development & System Debugging](#session-4-advanced-android-development--system-debugging)

2. [Containerization, Docker, and Kubernetes](#containerization-docker-and-kubernetes)  
   2.1. [Session 5: Container Session 1 – Objectives](#session-5-container-session-1--objectives)  
   2.2. [Session 6: Control Groups (CGroups)](#session-6-control-groups-cgroups)  
   2.3. [Session 7: Control Groups (CGroups) – Cont](#session-7-control-groups-cgroups--cont)  
   2.4. [Session 8: CGroups & Namespaces](#session-8-cgroups--namespaces)  
   2.5. [Session 9: Intro to Containers – Podman](#session-9-intro-to-containers--podman)  
   2.6. [Session 10: Intro to Containers – Podman Cont](#session-10-intro-to-containers--podman-cont)  
   2.7. [Session 11: Intro to Containers – Basic Concepts](#session-11-intro-to-containers--basic-concepts)  
   2.8. [Session 12: Docker (Part 1)](#session-12-docker-part-1)  
   2.9. [Session 13: Docker (Part 2)](#session-13-docker-part-2)  
   2.10. [Session 14: Docker & Kubernetes](#session-14-docker--kubernetes)

3. [Yocto (~20 Hours)](#yocto-20-hours)

4. [Modern C++ (~30 Hours)](#modern-c-30-hrs)

5. [Qt Core (~40 Hours)](#qt-core-40-hrs)

6. [Qt 6 C++ GUI (~20 Hours)](#qt-6-c-gui-20-hrs)

---

## Android-Focused Modules

### Session 1: Introduction to Embedded Android

1. **Course Promotional Video**
2. **Introduction to Embedded Systems**
3. **A Generic View on Embedded Systems**
4. **Android vs Linux**
5. **Linux Architecture Basics**
6. **Android Architecture**
7. **How Linux and Android Boot?**

### Session 2: Building and Flashing Android Source

1. **Obtaining and Building Android Source**
2. **Downloading Android 11 Source for ASUS Tinkerboard 2**
3. **Building Android 11 Source for ASUS Tinkerboard 2**
4. **Update: Building Instructions for Ubuntu 22.04 and Ubuntu 24.04 Users**
5. **Flashing Android 11 Image to ASUS Tinkerboard 2**
6. **Android Source Code Directories Explained**
7. **Android Filesystem Partitions**

### Session 3: Exploring and Customizing Android System

1. **Introduction to ASUS Tinkerboard 2 Hardware and Interfacing using Serial**
2. **Introduction to ADB and Fastboot**
3. **Flashing Separate Partitions using Fastboot Tool**
4. **ADB Remote Screen**
5. **Board, Build, and Device Configuration Files**
6. **Init Scripts (RC Files)**
7. **Devicetree and Kernel Config Files**
8. **Integrating a Custom Launcher in Android Build System**
9. **Creating a New Device Workspace to Contain Our Changes**
10. **Creating a New App/Application (APK) in Android Build System**
11. **Customizing Android Framework to Enable Night Mode**
12. **Customizing Android Framework to Modify Default Wallpaper**

### Session 4: Advanced Android Development & System Debugging

1. **Android System Properties**
2. **Integrating Plain C Programs in Android Build System**
3. **Deploying Binaries to Various Partitions using Android**
4. **Taking a Partial Build in Android Build System**
5. **Introduction to Binder**
6. **Creating Native AIDL Service using C++**
7. **Setting up Environment for our Example Service**
8. **Modifying Manifest Files for AIDL Interface**
9. **Creating a Test Application to Talk with Service**
10. **SELinux Configuration for Example Service**
11. **Creating Test Application to Talk with Example Service over AIDL Interface**
12. **An Example Approach to Fixing System-wide Issues**
13. **Testing and Certification in Android**
14. **ADB Commands for System-wide Debugging**
15. **Introduction and Example for HAL and Driver Integration**

---

## Containerization, Docker, and Kubernetes

### Session 5: Container Session 1 – Objectives

- Overview of containerization principles and session objectives.
- Introduction to the benefits of containerization in isolated and reproducible environments.
- High-level look at how containers are used to package and deploy applications consistently.

### Session 6: Control Groups (CGroups)

- **Concept Overview:**  
  CGroups (Control Groups) are a Linux kernel feature that allows for the allocation, prioritization, and monitoring of system resources (CPU, memory, disk I/O, etc.) for a set of processes.
- **Key Learning Points:**
  - How CGroups manage and limit resource usage.
  - The configuration and practical usage of CGroups in embedded and containerized environments.
  - Real-world examples of resource isolation using CGroups.

### Session 7: Control Groups (CGroups) – Cont

- **Advanced Concepts:**  
  Extends the basics of CGroups to explore more advanced configurations and tuning techniques.
- **Key Learning Points:**
  - Strategies to combine multiple CGroups for complex resource management.
  - Troubleshooting common issues related to resource limits.
  - Integration of CGroups into container orchestration systems to maintain performance and stability.

### Session 8: CGroups & Namespaces

- **Combining Isolation Techniques:**  
  Introduction to Linux namespaces, which isolate system resources such as process IDs, network interfaces, and file systems.
- **Key Learning Points:**
  - How namespaces complement CGroups by isolating the environment of processes.
  - The combined use of CGroups and namespaces to create lightweight, secure containers.
  - Practical demonstrations on setting up isolated environments using both CGroups and namespaces.

### Session 9: Intro to Containers – Podman

- **Introduction to Podman:**  
  Podman is a daemonless container engine for developing, managing, and running OCI Containers on your Linux system.
- **Key Learning Points:**
  - Basic architecture and features of Podman.
  - Differences between Podman and other container tools like Docker.
  - Running simple container operations using Podman commands.

### Session 10: Intro to Containers – Podman Cont

- **Deep Dive into Podman:**
  This session explores advanced usage scenarios.
- **Key Learning Points:**
  - Advanced container lifecycle management using Podman.
  - Integrating Podman with development tools such as VSCode.
  - Use cases for Podman in production and development environments.

### Session 11: Intro to Containers – Basic Concepts

- **Fundamental Container Concepts:**  
  Covers the essential ideas behind containerization beyond just the tooling.
- **Key Learning Points:**
  - What containers are and how they differ from virtual machines.
  - The concept of image layers and container registries.
  - Overview of container orchestration and its significance.

### Session 12: Docker (Part 1)

1. **Intro**
2. **Introduction to Containers**
3. **Container Architecture**
4. **Introduction to Docker**
5. **Installing Docker**
6. **Container = Application**
7. **Docker Engine Architecture**
8. **Images – Deep Dive**
9. **Docker in VSCode**
10. **Containers – Deep Dive**

### Session 13: Docker (Part 2)

1. **Network**
2. **Storage**
3. **Containerizing an Application**
4. **Dockerfile – Deep Dive**

### Session 14: Docker & Kubernetes

1. **Image Registries**
2. **Docker Compose**
3. **Docker Swarm**
4. **Docker Stack**
5. **Portainer**
6. **Introduction to Kubernetes**
7. **K8s High-Level Architecture**
8. **Installing Minikube**
9. **K8s Logical Architecture**
10. **K8s Sample Deployment**
11. **K8s in VSCode**
12. **Jupyter in Containers**

---

## Yocto (~20 Hours)

- **High-Level Overview**

  - Understand the core philosophy behind Embedded Linux systems.
  - Why we use Embedded Linux in certain products.
  - How Linux systems and Raspberry Pi 5 boot.

- **Embedded Linux Tasks**

  - Unpack, patch, configure, compile, install, deploy, package.
  - Distributions and package managers.

- **Yocto Project – Introduction and Configuration**

  - Comfortably handle tasks regarding Yocto Project and its configuration.
  - Understand how Raspberry Pi 5 layer and board configuration work (meta-raspberrypi, hardware specs, serial console).
  - Create your own machine configurations within Yocto Project.
  - Create your own layers for your Linux distribution.
  - Create new recipes for software packages that use multiple build systems (GCC, GNU Make, CMake, PyPi).

- **Integrations and Customization**

  - Integrate third-party software (e.g. GNOME, XFCE, Qt) in Embedded Linux products.
  - Integrate graphical desktop in your Embedded Linux system.
  - Deploy system images to Raspberry Pi 5 and work with secure shells and serial console software.
  - Create patches for existing software packages using DEVTOOL.

- **Kernel and Version Management**
  - Understand and modify kernel configurations (Kconfig, config fragments).
  - Downgrade and upgrade Linux Kernel version of your embedded Linux distribution.

---

## Modern C++ (~30 Hrs)

- **Object-Oriented Programming with C++**

  - Using C++ as an object-oriented language.
  - Classes, inheritance, polymorphism, and encapsulation.

- **Templates**

  - Function templates and class templates.
  - Generic programming fundamentals.

- **Standard Template Library (STL)**

  - STL components and how to use them (containers, iterators, algorithms).
  - Real-world application of STL in various scenarios.

- **Modern C++ (C++11/14/17)**

  - Lambda expressions, auto keyword, smart pointers, move semantics, etc.
  - Writing robust, efficient, and maintainable code in modern C++.

- **Build & Debugging Tools**

  - Introduction to Makefiles: building and organizing C++ projects.
  - Using GDB (GNU Debugger) to step through code, inspect variables, and set breakpoints.
  - Detecting memory leaks with Valgrind to ensure code reliability.
  - Logging errors and capturing runtime input/output for troubleshooting.

- **Real-World Applications**
  - Applying best practices and design patterns in production-level C++ projects.
  - Integrating testing frameworks for continuous integration and validation.
  - Performance considerations and optimization techniques.

---

## Qt Core (~40 Hrs)

### C++ Fundamentals (Review / Beginners)

- **C++ Essentials**

  - Variables, scope, pointers.
  - Flow control, functions, error handling.

- **Qt Introduction**
  - Basic Qt concepts: `QObject`, signals, slots.
  - Command-line programs: input/output, handling arguments.

### Intermediate Qt 6 Core

- **QObject Class & Macro**

  - `Q_OBJECT` macro and meta-object features (signals, slots, properties).
  - Memory management: stack vs. heap, smart pointers, parent-child relationships.

- **Containers & Collections**

  - `QString`, `QList`, `QVector`, `QMap`, `QVariant`.
  - Sorting containers, filling containers, iterators.

- **File & Folder Operations**

  - Navigating folders, reading/writing files, handling binary data.
  - Encoding (ASCII, UTF-8, UTF-16, Base64, Hex).

- **Process Management**

  - Starting external processes, exit codes, process lifecycle.
  - Communication with processes (pipes, standard input/output).

- **Threading & Concurrency**

  - Basic threading, thread pools, synchronization, mutexes, semaphores.
  - `Qt Concurrent`, futures, waiting on future values, concurrency best practices.

- **Networking**

  - Sockets (UDP, TCP), network proxies, SSL.
  - `QNetworkAccessManager`, handling HTTP requests.

- **Creating & Using Libraries**

  - Shared vs. static libraries, plugins, plugin loaders, dependency trees.

- **Databases**

  - Database drivers, connecting to databases, writing SQL queries in Qt.
  - Plugin loaders, QSql classes, and integration with Qt’s Model-View classes.

- **Unit Testing**

  - Data-driven tests, handling test failures, best practices for unit tests in Qt.

- **Deployment**
  - Deploying Qt applications on Linux.
  - Handling shared libraries and runtime dependencies.

---

## Qt 6 C++ GUI (~20 Hrs)

- **Fundamentals of Qt GUI Applications**

  - Working with Qt Widget classes to build desktop GUIs.
  - Understanding the Qt event loop, signals, and slots for UI components.

- **Dialogs & Resources**

  - Creating custom dialogs, using Qt resource system for images and assets.
  - Modal vs. modeless dialogs, user interaction flows.

- **Styling & Theming**

  - Applying stylesheets, customizing widget appearance.
  - Working with themes to create a consistent look and feel.

- **Networking & File System**

  - Fetching HTTP data, displaying network data in the GUI.
  - File open/save dialogs, managing user input/output from files.

- **Model-View Architecture**
  - Implementing custom models, views, and delegates for complex data handling.
  - Leveraging built-in models (QStandardItemModel) for rapid prototyping.

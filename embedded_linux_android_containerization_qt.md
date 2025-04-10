# Embedded Linux, Android, Containerization, and Qt Diploma – Full Course Content

This document provides a **complete** overview of the diploma’s curriculum, covering Yocto, Modern C++, Qt (Core, GUI, and Design Patterns), Containerization (Docker and Kubernetes), and **optionally** Embedded Android. Each module is designed to give you in-depth knowledge and hands-on experience in building, deploying, and customizing embedded systems and modern C++/Qt applications.

> **Note**: The Embedded Android module is **optional**.

## Table of Contents

- [Embedded Linux, Android, Containerization, and Qt Diploma – Full Course Content](#embedded-linux-android-containerization-and-qt-diploma--full-course-content)
  - [Table of Contents](#table-of-contents)
  - [1. Yocto (~20 Hours)](#1-yocto-20-hours)
  - [2. Modern C++ (~30 Hours)](#2-modern-c-30-hours)
  - [3. Qt Core (~40 Hours)](#3-qt-core-40-hours)
    - [C++ Fundamentals (Review / Beginners)](#c-fundamentals-review--beginners)
    - [Intermediate Qt 6 Core](#intermediate-qt-6-core)
  - [4. Qt 6 C++ GUI (~20 Hours)](#4-qt-6-c-gui-20-hours)
  - [5. Qt Design Patterns (~25 Hours)](#5-qt-design-patterns-25-hours)
  - [6. Containerization, Docker, and Kubernetes](#6-containerization-docker-and-kubernetes)
    - [Container – Objectives](#container--objectives)
    - [Control Groups (CGroups)](#control-groups-cgroups)
    - [Control Groups (CGroups) – Cont](#control-groups-cgroups--cont)
    - [CGroups \& Namespaces](#cgroups--namespaces)
    - [Intro to Containers – Podman](#intro-to-containers--podman)
    - [Intro to Containers – Podman Cont](#intro-to-containers--podman-cont)
    - [Intro to Containers – Basic Concepts](#intro-to-containers--basic-concepts)
    - [Docker (Part 1)](#docker-part-1)
    - [Docker (Part 2)](#docker-part-2)
    - [Docker \& Kubernetes](#docker--kubernetes)
  - [7. \[OPTIONAL\] Embedded Android](#7-optional-embedded-android)
    - [Introduction to Embedded Android](#introduction-to-embedded-android)
    - [Building and Flashing Android Source](#building-and-flashing-android-source)
    - [Exploring and Customizing Android System](#exploring-and-customizing-android-system)
    - [Advanced Android Development \& System Debugging](#advanced-android-development--system-debugging)

---

## 1. Yocto (~20 Hours)

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

## 2. Modern C++ (~30 Hours)

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

  - Lambda expressions, `auto` keyword, smart pointers, move semantics, etc.
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

## 3. Qt Core (~40 Hours)

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

## 4. Qt 6 C++ GUI (~20 Hours)

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

---

## 5. Qt Design Patterns (~25 Hours)

**Design patterns using Qt 5 and C++**

- **Creational Patterns**
  - Abstract Factory, Builder, Factory Method, Object Pool, Prototype, Magic Static
- **Structural Patterns**
  - Adapter, Bridge, Composite, Decorator, Facade, Flyweight
- **Behavioral Patterns**
  - Chain of Responsibility, Command, Interpreter, Iterator, Mediator, Memento, Null Object, Strategy, Visitor
- **IO Patterns**
  - Handling file streams, network streams, data serialization
- **State Patterns**
  - State machine framework in Qt

**Additional Advanced Topics**

- **Templates**
  - Class construction, memory management, smart pointers, encapsulation, Qt property system
- **SOLID Principles**
  - Single-Responsibility, Open-Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
- **Key Best Practices**
  - DRY (Don’t Repeat Yourself), KIS (Keep It Simple), RAII (Resource Acquisition Is Initialization), exception handling
- **Qt Signal-Slot Mechanisms**
  - Auto-connecting signals and slots, different signal connection types, disconnecting signals
- **Threading**
  - Thread pools, Qt Concurrent, threading in Widgets, threading in QML
- **Qt Template Classes**
  - Pointers in templates, QMake tricks, CMake tricks
- **Libraries & Plugins**
  - Creating shared libraries, using shared libraries, loading them dynamically
  - Creating plugins, loading plugins
- **Data Handling**
  - Text streams, data streams, data classes, storing passwords securely
- **Process Control**
  - Controlling processes, desktop services, `QProcess` in Widgets/QML
- **Serialization & QML**
  - Serializing objects, QML state management

---

## 6. Containerization, Docker, and Kubernetes

### Container – Objectives

- Overview of containerization principles and session objectives.
- Introduction to the benefits of containerization in isolated and reproducible environments.
- High-level look at how containers are used to package and deploy applications consistently.

### Control Groups (CGroups)

- **Concept Overview:**  
  CGroups (Control Groups) are a Linux kernel feature that allows for the allocation, prioritization, and monitoring of system resources (CPU, memory, disk I/O, etc.) for a set of processes.
- **Key Learning Points:**
  - How CGroups manage and limit resource usage.
  - Practical usage of CGroups in embedded and containerized environments.
  - Resource isolation examples.

### Control Groups (CGroups) – Cont

- **Advanced Concepts:**
  - Combining multiple CGroups for complex resource management.
  - Troubleshooting common issues related to resource limits.
  - Integrating CGroups into container orchestration systems.

### CGroups & Namespaces

- **Combining Isolation Techniques:**
  - Linux namespaces (process, network, filesystem isolation).
  - Using CGroups + namespaces to create lightweight, secure containers.
  - Hands-on demonstrations.

### Intro to Containers – Podman

- **Daemonless Container Engine:**
  - Podman architecture and basic features.
  - Differences from Docker.
  - Running simple container operations with Podman.

### Intro to Containers – Podman Cont

- **Advanced Podman Usage:**
  - Lifecycle management of containers.
  - Integrating Podman with VSCode.
  - Production and development use cases.

### Intro to Containers – Basic Concepts

- **Fundamental Container Concepts:**
  - Containers vs Virtual Machines.
  - Image layers, container registries.
  - Container orchestration overview.

### Docker (Part 1)

1. **Introduction to Containers**
2. **Container Architecture**
3. **Introduction to Docker**
4. **Installing Docker**
5. **Container = Application**
6. **Docker Engine Architecture**
7. **Images – Deep Dive**
8. **Docker in VSCode**
9. **Containers – Deep Dive**

### Docker (Part 2)

1. **Networking**
2. **Storage**
3. **Containerizing an Application**
4. **Dockerfile – Deep Dive**

### Docker & Kubernetes

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

## 7. [OPTIONAL] Embedded Android

> This module is fully optional and can be taken if we have a time.

### Introduction to Embedded Android

1. **Course Promotional Video**
2. **Introduction to Embedded Systems**
3. **A Generic View on Embedded Systems**
4. **Android vs Linux**
5. **Linux Architecture Basics**
6. **Android Architecture**
7. **How Linux and Android Boot?**

### Building and Flashing Android Source

1. **Obtaining and Building Android Source**
2. **Downloading Android 11 Source for ASUS Tinkerboard 2**
3. **Building Android 11 Source for ASUS Tinkerboard 2**
4. **Update: Building Instructions for Ubuntu 22.04 and Ubuntu 24.04 Users**
5. **Flashing Android 11 Image to ASUS Tinkerboard 2**
6. **Android Source Code Directories Explained**
7. **Android Filesystem Partitions**

### Exploring and Customizing Android System

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

### Advanced Android Development & System Debugging

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

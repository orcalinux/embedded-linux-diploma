# Embedded Android Diploma – Partial Course Content

This document outlines the core modules and lectures covered in this portion of the Embedded Android Diploma. The content is split into two primary areas: Android-focused modules and containerization topics (covering Docker, Kubernetes, and more). **Note:** This list represents only part of the overall diploma; additional sections and topics will be provided later.

## Table of Contents

- [Embedded Android Diploma – Partial Course Content](#embedded-android-diploma--partial-course-content)
  - [Table of Contents](#table-of-contents)
  - [Android-Focused Modules](#android-focused-modules)
    - [Session 1: Introduction to Embedded Android](#session-1-introduction-to-embedded-android)
    - [Session 2: Building and Flashing Android Source](#session-2-building-and-flashing-android-source)
    - [Session 3: Exploring and Customizing Android System](#session-3-exploring-and-customizing-android-system)
    - [Session 4: Advanced Android Development \& System Debugging](#session-4-advanced-android-development--system-debugging)
  - [Containerization, Docker, and Kubernetes](#containerization-docker-and-kubernetes)
    - [Session 5: Container Session 1 – Objectives](#session-5-container-session-1--objectives)
    - [Session 6: Control Groups (CGroups)](#session-6-control-groups-cgroups)
    - [Session 7: Control Groups (CGroups) – Cont](#session-7-control-groups-cgroups--cont)
    - [Session 8: CGroups \& Namespaces](#session-8-cgroups--namespaces)
    - [Session 9: Intro to Containers – Podman](#session-9-intro-to-containers--podman)
    - [Session 10: Intro to Containers – Podman Cont](#session-10-intro-to-containers--podman-cont)
    - [Session 11: Intro to Containers – Basic Concepts](#session-11-intro-to-containers--basic-concepts)
    - [Session 12: Docker (Part 1)](#session-12-docker-part-1)
    - [Session 13: Docker (Part 2)](#session-13-docker-part-2)
    - [Session 14: Docker \& Kubernetes](#session-14-docker--kubernetes)

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
  This session extends the basics of CGroups to explore more advanced configurations and tuning techniques.
- **Key Learning Points:**
  - Strategies to combine multiple CGroups for complex resource management.
  - Troubleshooting common issues related to resource limits.
  - Integration of CGroups into container orchestration systems to maintain performance and stability.

### Session 8: CGroups & Namespaces

- **Combining Isolation Techniques:**  
  This session introduces Linux namespaces, which isolate system resources such as process IDs, network interfaces, and file systems.
- **Key Learning Points:**
  - How namespaces complement CGroups by isolating the environment of processes.
  - The combined use of CGroups and namespaces to create lightweight, secure containers.
  - Practical demonstrations on setting up isolated environments using both CGroups and namespaces.

### Session 9: Intro to Containers – Podman

- **Introduction to Podman:**  
  Podman is a daemonless container engine for developing, managing, and running OCI Containers on your Linux system.
- **Key Learning Points:**
  - The basic architecture and features of Podman.
  - Differences between Podman and other container tools like Docker.
  - How to run simple container operations using Podman commands.

### Session 10: Intro to Containers – Podman Cont

- **Deep Dive into Podman:**  
  This session builds on the basics of Podman by exploring more advanced usage scenarios.
- **Key Learning Points:**
  - Advanced container lifecycle management using Podman.
  - Integrating Podman with development tools such as VSCode.
  - Use cases for Podman in production and development environments.

### Session 11: Intro to Containers – Basic Concepts

- **Fundamental Container Concepts:**  
  This session covers the essential ideas behind containerization beyond just the tooling.
- **Key Learning Points:**
  - What containers are and how they differ from virtual machines.
  - The concept of image layers and container registries.
  - Overview of container orchestration and its significance in modern application deployment.

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

_Note: This readme is a partial overview. More sections and detailed topics will be added to complete the Embedded Android Diploma curriculum._

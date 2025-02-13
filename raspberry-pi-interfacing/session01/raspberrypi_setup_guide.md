# Raspberry Pi OS, Angry IP Scanner & RealVNC® Viewer Setup Guide

This guide provides step-by-step instructions for installing Raspberry Pi OS using the Raspberry Pi Imager, setting up Angry IP Scanner to locate your Raspberry Pi on your network, and installing RealVNC® Viewer for remote desktop access. It also covers the prerequisites required for Angry IP Scanner on Linux.

---

## Table of Contents

- [Raspberry Pi OS, Angry IP Scanner \& RealVNC® Viewer Setup Guide](#raspberry-pi-os-angry-ip-scanner--realvnc-viewer-setup-guide)
  - [Table of Contents](#table-of-contents)
  - [1. Raspberry Pi OS Installation](#1-raspberry-pi-os-installation)
  - [2. Raspberry Pi Imager Installation](#2-raspberry-pi-imager-installation)
    - [Installation via .deb Package](#installation-via-deb-package)
    - [Alternative Installation on Raspberry Pi OS](#alternative-installation-on-raspberry-pi-os)
  - [3. Downloading Prerequisites for Angry IP Scanner](#3-downloading-prerequisites-for-angry-ip-scanner)
    - [For Ubuntu/Debian/Mint:](#for-ubuntudebianmint)
    - [For Fedora/RedHat/CentOS:](#for-fedoraredhatcentos)
    - [For Arch Linux:](#for-arch-linux)
  - [6. Angry IP Scanner Setup](#6-angry-ip-scanner-setup)
    - [Download Options \& Installation Commands](#download-options--installation-commands)
    - [Running Angry IP Scanner](#running-angry-ip-scanner)
    - [Additional Note for Raspbian/32-bit ARM](#additional-note-for-raspbian32-bit-arm)
  - [4. Finding the Raspberry Pi IP Address](#4-finding-the-raspberry-pi-ip-address)
  - [5. Configuring Raspberry Pi for Remote Desktop Access](#5-configuring-raspberry-pi-for-remote-desktop-access)
  - [6. RealVNC® Viewer Setup](#6-realvnc-viewer-setup)
    - [Download \& Installation Commands for RealVNC® Viewer](#download--installation-commands-for-realvnc-viewer)
  - [7. References](#7-references)

---

## 1. Raspberry Pi OS Installation

Download the latest Raspberry Pi OS from the official website:

- **Raspberry Pi OS:** [https://www.raspberrypi.com/software/](https://www.raspberrypi.com/software/)

---

## 2. Raspberry Pi Imager Installation

### Installation via .deb Package

1. **Download Raspberry Pi Imager:**  
   Obtain the file `imager_1.8.5_amd64.deb` from the official source.

2. **Open Terminal and Navigate to Downloads:**

   ```bash
   cd $HOME/Downloads/
   ```

3. **Install the .deb Package:**

   ```bash
   sudo dpkg -i imager_1.8.5_amd64.deb
   ```

4. **Fix Dependency Issues (if any):**

   ```bash
   sudo apt-get install -f
   ```

5. **Verify the Installation:**
   ```bash
   rpi-imager --version
   ```

### Alternative Installation on Raspberry Pi OS

1. **Install Directly from the Repository:**

   ```bash
   sudo apt install rpi-imager
   ```

2. **Launch the Imager:**
   ```bash
   rpi-imager
   ```

---

## 3. Downloading Prerequisites for Angry IP Scanner

Angry IP Scanner requires **Java 11** or a compatible OpenJDK version. Follow these instructions for your Linux distribution:

### For Ubuntu/Debian/Mint:

1. **Update your package list:**
   ```bash
   sudo apt update
   ```
2. **Install OpenJDK 11:**
   ```bash
   sudo apt install openjdk-11-jdk
   ```
3. **Verify the installation:**
   ```bash
   java -version
   ```

### For Fedora/RedHat/CentOS:

1. **Update your package list:**
   ```bash
   sudo dnf check-update
   ```
2. **Install OpenJDK 11:**
   ```bash
   sudo dnf install java-11-openjdk-devel
   ```
3. **Verify the installation:**
   ```bash
   java -version
   ```

### For Arch Linux:

1. **Install OpenJDK 11:**
   ```bash
   sudo pacman -S jdk11-openjdk
   ```
2. **Verify the installation:**
   ```bash
   java -version
   ```

> **Note for Executable Jar Users:**  
> If you choose to run Angry IP Scanner using the Executable Jar, download the appropriate `swt.jar` from the [Eclipse SWT Project](https://www.eclipse.org/swt/) and include it in your classpath.

---

## 6. Angry IP Scanner Setup

### Download Options & Installation Commands

1. **Download Angry IP Scanner:**  
   Visit the official download page: [https://angryip.org/download/#linux](https://angryip.org/download/#linux)  
   Choose the appropriate package for your system. For example, if you are using Ubuntu/Debian/Mint, download the **x86 64-bit DEB Package** (e.g., `ipscan_3.9.1_amd64.deb`).

2. **Open Terminal and Navigate to the Downloads Directory:**

   ```bash
   cd $HOME/Downloads/
   ```

3. **Install the Downloaded Package:**  
   For Ubuntu/Debian/Mint, run:

   ```bash
   sudo dpkg -i ipscan_3.9.1_amd64.deb
   ```

4. **Fix Dependency Issues (if necessary):**
   ```bash
   sudo apt-get install -f
   ```

### Running Angry IP Scanner

- **Using the Installed Package:**  
  After installation, Angry IP Scanner creates a desktop entry under **Applications** (within **Internet** or **Networking**). You can also launch it from the terminal:

  ```bash
  ipscan
  ```

- **Using the Executable Jar:**  
  Launch the jar by double-clicking it or running:
  ```bash
  java -jar <jar-file>
  ```

### Additional Note for Raspbian/32-bit ARM

For Raspbian/32-bit ARM systems, when using the "any architecture" DEB package, you must use an older 32-bit build of SWT since the current versions provided by Bullseye no longer support 32-bit systems.

---

## 4. Finding the Raspberry Pi IP Address

To locate your Raspberry Pi's IP address, use Angry IP Scanner. This tool scans your network and identifies connected devices, including your Raspberry Pi.

---

## 5. Configuring Raspberry Pi for Remote Desktop Access

Once you have located your Raspberry Pi’s IP address using Angry IP Scanner, follow these steps to configure your device for remote desktop access:

1. **Connect via SSH:**  
   Open a terminal on your computer and connect to your Raspberry Pi by replacing `<raspberry_pi_ip>` with its actual IP address. For example:

   ```bash
   ssh pi@<raspberry_pi_ip>
   ```

   > **Note:** If your username is different (e.g., `mahmoud`), adjust the command accordingly.

2. **Launch the Raspberry Pi Configuration Tool:**  
   Once connected via SSH, run:

   ```bash
   sudo raspi-config
   ```

3. **Set Boot Options for Desktop Autologin:**  
   In the `raspi-config` menu:

   - Navigate to **System Options**.
   - Select **Boot / Auto Login**.
   - Choose **Desktop Autologin** (which automatically logs you into the Desktop GUI as the default user).

4. **Enable VNC for Remote Desktop Access:**  
   In the same `raspi-config` menu:
   - Go to **Interface Options** (or **Interfacing Options**).
   - Select **VNC**.
   - Choose **Enable**.
   - Exit `raspi-config` and reboot if prompted.

After completing these steps, your Raspberry Pi will boot directly into the Desktop GUI with automatic login, and VNC will be enabled, allowing you to connect using RealVNC® Viewer.

---

## 6. RealVNC® Viewer Setup

RealVNC® Viewer enables remote desktop access to your Raspberry Pi, allowing you to control it from another computer.

### Download & Installation Commands for RealVNC® Viewer

1. **Download RealVNC® Viewer:**  
   Visit the official download page for Linux: [https://www.realvnc.com/en/connect/download/viewer/linux/](https://www.realvnc.com/en/connect/download/viewer/linux/)  
   Select the appropriate package for your Linux distribution (for example, the **.deb** package for Ubuntu/Debian).

2. **Open Terminal and Navigate to the Downloads Directory:**

   ```bash
   cd $HOME/Downloads/
   ```

3. **Install the Downloaded Package:**  
   For Ubuntu/Debian, run:
   ```bash
   sudo dpkg -i VNC-Viewer-7.13.1-Linux-x64.deb
   ```
4. **Fix Dependency Issues (if necessary):**

   ```bash
   sudo apt-get install -f
   ```

5. **Launch RealVNC® Viewer:**  
   You can start RealVNC® Viewer from your application menu or by typing:
   ```bash
   vncviewer
   ```

> **Note:** On some versions of Raspberry Pi OS, RealVNC® Viewer may already be pre-installed.

---

## 7. References

- **Raspberry Pi OS:** [https://www.raspberrypi.com/software/](https://www.raspberrypi.com/software/)
- **Angry IP Scanner Download:** [https://angryip.org/download/#linux](https://angryip.org/download/#linux)
- **Eclipse SWT Project:** [https://www.eclipse.org/swt/](https://www.eclipse.org/swt/)
- **RealVNC® Viewer Download:** [https://www.realvnc.com/en/connect/download/viewer/linux/](https://www.realvnc.com/en/connect/download/viewer/linux/)

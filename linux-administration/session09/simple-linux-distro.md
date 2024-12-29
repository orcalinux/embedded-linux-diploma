# Creating a Simple Linux Distribution

This guide provides a step-by-step process to create a basic Linux distribution using **QEMU** and **ARM architecture**. The process encompasses installing necessary tools, configuring and building the Linux kernel, compiling BusyBox, creating the RootFS, compressing the file system, and running QEMU with the created file system.

## Table of Contents

1. [Cloned Steps Source](#cloned-steps-source)
2. [Installation and Setup](#installation-and-setup)
   - [1. Install QEMU](#1-install-qemu)
   - [2. Install Essential Packages for ARM GCC Compilation](#2-install-essential-packages-for-arm-gcc-compilation)
   - [3. Select ARM Versatile PB Board](#3-select-arm-versatile-pb-board)
   - [4. Install Cross Compiler](#4-install-cross-compiler)
3. [Building the Kernel](#building-the-kernel)
   - [5. Download and Extract Linux Kernel](#5-download-and-extract-linux-kernel)
   - [6. Configure Kernel](#6-configure-kernel)
   - [7. Build Kernel and Modules](#7-build-kernel-and-modules)
   - [8. Install Kernel Modules](#8-install-kernel-modules)
4. [Building BusyBox](#building-busybox)
   - [9. Download and Extract BusyBox](#9-download-and-extract-busybox)
   - [10. Compile BusyBox](#10-compile-busybox)
5. [Creating the RootFS](#creating-the-rootfs)
   - [11. Prepare RootFS](#11-prepare-rootfs)
   - [12. Create Init Script](#12-create-init-script)
   - [13. Set Permissions](#13-set-permissions)
   - [14. Copy BusyBox Files](#14-copy-busybox-files)
   - [15. Create RootFS Directory Structure](#15-create-rootfs-directory-structure)
6. [Compressing the File System](#compressing-the-file-system)
   - [16. Compress File System](#16-compress-file-system)
7. [Running QEMU](#running-qemu)
   - [17. Run QEMU](#17-run-qemu)
8. [Conclusion](#conclusion)

---

## Cloned Steps Source

The steps outlined in this guide are adapted from [Minimalistic Linux System on QEMU ARM](https://lukaszgemborowski.github.io/articles/minimalistic-linux-system-on-qemu-arm.html).

---

## Installation and Setup

### 1. Install QEMU

Begin by installing QEMU, a generic and open-source machine emulator and virtualizer.

```bash
sudo apt install qemu-system-arm
```

### 2. Install Essential Packages for ARM GCC Compilation

Install the necessary packages required for compiling ARM GCC. These tools are essential for building the cross-compiler and other dependencies.

```bash
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
```

**Note:** This command installs the required packages for compiling ARM GCC.

### 3. Select ARM Versatile PB Board

For emulation purposes, we will use the **ARM Versatile PB** board. Detailed information about this board can be found in the [QEMU documentation](https://www.qemu.org/docs/master/system/arm/versatile.html).

### 4. Install Cross Compiler

Install the ARM cross-compiler to build software for the ARM architecture on your host machine.

```bash
sudo apt install gcc-arm-linux-gnueabi
```

---

## Building the Kernel

### 5. Download and Extract Linux Kernel

Download the Linux kernel source code and extract it.

```bash
# Download the Linux kernel source tarball
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.7.6.tar.xz

# Extract the downloaded tarball
tar xvf linux-6.7.6.tar.xz
```

### 6. Configure Kernel

Navigate to the Linux kernel source directory and configure the kernel for the ARM architecture.

```bash
# Navigate to the Linux kernel source directory
cd linux-6.7.6

# Configure the kernel for ARM architecture
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- versatile_defconfig
```

You can further customize the kernel configuration using:

```bash
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
```

> **Tip:** In the menu configuration, you can enable or disable features as per your requirements.

### 7. Build Kernel and Modules

Compile the Linux kernel and its modules using multiple cores to speed up the build process.

```bash
# Build the Linux kernel with multiple cores
time make -j8 O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

# Build kernel modules with multiple cores
time make -j8 modules O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
```

### 8. Install Kernel Modules

Install the compiled kernel modules into the RootFS directory.

```bash
time make -j8 modules_install O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- INSTALL_MOD_PATH=../../rootfs
```

---

## Building BusyBox

### 9. Download and Extract BusyBox

Download the latest BusyBox from [https://busybox.net/](https://busybox.net/) and extract it. For this guide, we are using **BusyBox version 1.36.1**.

```bash
# Download the BusyBox source code from the official website.
wget https://busybox.net/downloads/busybox-1.36.1.tar.bz2

# Extract the downloaded BusyBox tarball.
tar xvf busybox-1.36.1.tar.bz2
```

### 10. Compile BusyBox

Navigate to the BusyBox directory, configure it for ARM architecture, and compile it.

```bash
# Step 1: Navigate to the BusyBox directory
cd busybox-1.36.1

# Step 2: Configure BusyBox for ARM architecture
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig

# Step 3: Customize BusyBox configuration
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
# Enable 'Build BusyBox as a static binary' from Settings

# Step 4: Build BusyBox with multiple cores
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8

# Step 5: Install BusyBox on the system
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8 install
```

> **Note:** Ensure that you enable the option to build BusyBox as a static binary during the `menuconfig` step. This simplifies the execution in the minimalistic environment.

---

## Creating the RootFS

### 11. Prepare RootFS

Create the root file system (RootFS) directory structure necessary for the Linux distribution.

```bash
# Navigate to the rootfs directory
cd ../rootfs

# Create necessary directories in the root file system
mkdir -p bin sbin etc proc sys usr/{bin,sbin}
```

### 12. Create Init Script

Create an `init` script that will be executed when the system boots.

```bash
# Navigate back to the parent directory
cd ..

# Edit the init script
vim rootfs/init
```

**Add the following content to `rootfs/init`:**

```sh
#!/bin/sh
echo -e "\nHello from the init process\n"

mount -t proc none /proc
mount -t sysfs none /sys
mknod -m 660 /dev/mem c 1 1

exec /bin/sh
```

#### Detailed Explanation of the `init` Script

The `init` script is the first user-space process executed by the Linux kernel during the boot process. It sets up the necessary environment and starts essential services. Here's a breakdown of each command in the `init` script:

1. **Shebang and Echo Message**

   ```sh
   #!/bin/sh
   echo -e "\nHello from the init process\n"
   ```

   - **`#!/bin/sh`**: Specifies that the script should be run using the Bourne shell.
   - **`echo -e "\nHello from the init process\n"`**: Prints a welcome message to the console.

2. **Mounting `proc` and `sysfs` File Systems**

   ```sh
   mount -t proc none /proc
   mount -t sysfs none /sys
   ```

   - **`mount -t proc none /proc`**: Mounts the `proc` filesystem, which provides an interface to kernel data structures. It's essential for many system utilities to function correctly.
   - **`mount -t sysfs none /sys`**: Mounts the `sysfs` filesystem, which exports information about devices and drivers from the kernel to user space.

3. **Creating the `/dev/mem` Device Node**

   ```sh
   mknod -m 660 /dev/mem c 1 1
   ```

   - **`mknod`**: A command used to create device nodes (special files) in the `/dev` directory.
   - **`-m 660`**: Sets the permissions of the device node to `660` (read and write permissions for the owner and group).
   - **`/dev/mem`**: The name of the device node being created.
   - **`c`**: Indicates that the device node is a **character device**.
   - **`1 1`**: The major and minor numbers of the device.

   **Detailed Explanation of `mknod` Command:**

   The `mknod` command is crucial for creating special files that represent hardware devices or pseudo-devices. In this context, `mknod` is used to create the `/dev/mem` device node, which provides access to the physical memory of the system.

   - **Device Nodes:**

     - **Character Devices (`c`)**: Handle data as a stream of bytes. Examples include serial ports, keyboards, and mice.
     - **Block Devices (`b`)**: Handle data in blocks, typically used for storage devices like hard drives and USB drives.

   - **Major and Minor Numbers:**

     - **Major Number (`1`)**: Identifies the driver associated with the device. In this case, major number `1` corresponds to memory devices.
     - **Minor Number (`1`)**: Identifies the specific device. Minor number `1` corresponds to `/dev/mem`.

   - **Permissions (`-m 660`):**
     - **`6` (read and write) for the owner**
     - **`6` (read and write) for the group**
     - **`0` (no permissions) for others**

   **Purpose of `/dev/mem`:**

   - **`/dev/mem`**: Represents the physical memory of the system. It allows processes with appropriate permissions to access physical memory directly. This can be useful for debugging, low-level hardware interactions, or accessing memory-mapped devices.

   **Why `/dev/mem` is Necessary:**

   - In a minimalistic Linux environment, many standard device nodes are absent. Creating `/dev/mem` provides a basic interface to interact with the system's memory, which can be leveraged by various utilities and the shell.
   - Some kernel modules or user-space applications may require access to physical memory for proper functioning or configuration.

4. **Executing the Shell**

   ```sh
   exec /bin/sh
   ```

   - **`exec`**: Replaces the current shell with `/bin/sh`, effectively handing over control to the shell for user interaction.
   - **`/bin/sh`**: Launches the Bourne shell, allowing the user to execute commands.

   **Flow of the `init` Script:**

   1. **Initialization Messages:** Prints a welcome message to indicate that the init process has started.
   2. **Mounting Essential File Systems:** Sets up the `proc` and `sysfs` filesystems, which are vital for system operations and utilities.
   3. **Creating Device Nodes:** Establishes necessary device interfaces, such as `/dev/mem`, enabling interactions with system hardware.
   4. **Launching the Shell:** Starts an interactive shell session, allowing the user to execute commands and interact with the system.

   **Summary:**

   The `init` script sets up the foundational environment required for a functional Linux system. By mounting essential filesystems and creating necessary device nodes, it ensures that user-space applications and utilities can operate correctly. Finally, by launching the shell, it provides an interface for user interaction and further system configuration.

### 13. Set Permissions

Make the `init` script executable.

```bash
chmod +x rootfs/init
```

### 14. Copy BusyBox Files

Copy the compiled BusyBox binaries and scripts to the RootFS.

```bash
cp -av busybox-1.36.1/_install/* rootfs/
```

### 15. Create RootFS Directory Structure

Ensure that the RootFS has the necessary directory hierarchy.

```bash
mkdir -pv rootfs/{bin,sbin,etc,proc,sys,usr/{bin,sbin}}
```

---

## Compressing the File System

### 16. Compress File System

Create a compressed cpio archive of the RootFS, which will be used by QEMU during emulation.

```bash
# Navigate to the rootfs directory
cd rootfs/

# Create a newc-format cpio archive with null-terminated filenames and gzip compression
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../rootfs.cpio.gz
```

**Explanation:**

- **`find . -print0`**: Lists all files and directories, separating them with a null character to handle filenames with spaces or special characters.
- **`cpio --null -ov --format=newc`**: Creates a cpio archive in the `newc` format, which is a portable and widely supported archive format.
- **`gzip -9`**: Compresses the archive using maximum compression for reduced file size.

---

## Running QEMU

### 17. Run QEMU

Use QEMU to emulate the ARM architecture with the configured kernel and RootFS.

```bash
# Navigate back to the parent directory
cd ..

# Run QEMU with the specified parameters to emulate the ARM architecture
qemu-system-arm -M versatilepb \
    -kernel linux-6.7.6/build/arch/arm/boot/zImage \
    -dtb linux-6.7.6/build/arch/arm/boot/dts/arm/versatile-pb.dtb \
    -initrd rootfs.cpio.gz \
    -serial stdio \
    -append "root=/dev/mem serial=ttyAMA0"
```

**Parameters Explained:**

- **`-M versatilepb`**: Specifies the machine type as ARM Versatile PB.
- **`-kernel`**: Path to the compiled Linux kernel image.
- **`-dtb`**: Path to the device tree blob, which provides hardware configuration information to the kernel.
- **`-initrd`**: Path to the initial ramdisk (RootFS) created earlier.
- **`-serial stdio`**: Redirects the serial port to the standard input/output, allowing interaction through the terminal.
- **`-append "root=/dev/mem serial=ttyAMA0"`**: Passes kernel command-line parameters:
  - **`root=/dev/mem`**: Specifies the root device as `/dev/mem`. This is a minimal setup for this example.
- **`serial=ttyAMA0`**: Sets up the serial console on `ttyAMA0`, which QEMU maps to the standard input/output.

---

## Conclusion

By following these steps, you have successfully created a simple Linux distribution tailored for the ARM architecture using QEMU for emulation. This minimalistic setup serves as a foundation that you can further customize and expand according to your requirements.

### Next Steps

- **Customization:** Modify kernel configurations or BusyBox settings to include additional features or optimizations.
- **Adding Applications:** Incorporate more applications into the RootFS to extend functionality.
- **Automation:** Script the build process to streamline future builds and iterations.
- **Exploration:** Experiment with different QEMU machine types or kernel versions to explore various configurations.

---

## Additional Resources

- [QEMU Documentation](https://www.qemu.org/docs/master/)
- [BusyBox Official Website](https://busybox.net/)
- [Linux Kernel Archives](https://www.kernel.org/)
- [Cross-Compilation for ARM](https://wiki.archlinux.org/title/Cross-compilation)

---

## Troubleshooting Tips

1. **Permission Denied Errors:**
   - Ensure that all scripts and binaries have the correct executable permissions using `chmod +x`.
2. **Missing Device Nodes:**

   - Verify that all necessary device nodes are created in the `init` script using `mknod`.

3. **Kernel Panic:**

   - Double-check kernel configurations to ensure that essential drivers and modules are enabled.
   - Ensure that the `root` parameter points to the correct root filesystem.

4. **QEMU Not Starting:**
   - Verify that all paths to the kernel, device tree blob, and initrd are correct.
   - Ensure that QEMU is properly installed and updated to a compatible version.

---

## Understanding the `mknod` Command in the Init Process

In the context of the `init` script, the `mknod` command plays a critical role in setting up the system's device nodes. Here's an in-depth look at what `mknod` does and why it's essential:

### What is `mknod`?

- **`mknod`** stands for "make node." It is a Unix/Linux command used to create special files, known as device nodes, in the filesystem.
- Device nodes are interfaces to device drivers that appear as files within the `/dev` directory. They allow user-space applications to interact with hardware devices or virtual devices managed by the kernel.

### Syntax of `mknod`

```sh
mknod [options] <filename> <type> <major> <minor>
```

- **`<filename>`**: The path and name of the device node to create (e.g., `/dev/mem`).
- **`<type>`**: The type of device node. Common types include:
  - **`c`**: Character device
  - **`b`**: Block device
- **`<major>`**: The major number identifying the driver associated with the device.
- **`<minor>`**: The minor number identifying the specific device the driver controls.

### Breakdown of the `mknod` Command in the Init Script

```sh
mknod -m 660 /dev/mem c 1 1
```

- **`-m 660`**: Sets the file permissions of the device node to `660` (read and write for the owner and group, no permissions for others).
- **`/dev/mem`**: The name and location of the device node being created.
- **`c`**: Indicates that the device node is a character device.
- **`1`**: The major number, which identifies the driver associated with `/dev/mem`.
- **`1`**: The minor number, which specifies the exact device the driver should manage.

### Understanding `/dev/mem`

- **Purpose**: `/dev/mem` is a special file that provides access to the physical memory of the system. It allows processes to read from and write to physical memory addresses.
- **Usage**:
  - **Debugging**: Developers can use `/dev/mem` to inspect or modify memory contents for debugging purposes.
  - **Hardware Interaction**: Low-level system utilities or kernel modules may interact with hardware devices by accessing specific memory-mapped registers via `/dev/mem`.

### Importance of Creating `/dev/mem`

1. **System Initialization**:
   - During the early stages of system boot, essential device nodes like `/dev/mem` are required for various system operations and utilities.
2. **Access to Physical Memory**:
   - By providing a gateway to physical memory, `/dev/mem` enables direct interactions with hardware, which is crucial in embedded systems or minimalistic environments where higher-level abstractions may be unavailable.
3. **Flexibility and Control**:
   - Creating device nodes manually gives developers fine-grained control over the system's hardware interfaces, which is especially useful in custom or stripped-down Linux distributions.

### Security Considerations

- **Restricted Access**:
  - Access to `/dev/mem` should be tightly controlled because it allows direct manipulation of the system's memory, which can compromise system stability and security.
- **Permissions**:
  - In the `mknod` command, permissions are set to `660`, granting read and write access only to the owner and group. This restricts unauthorized users from accessing `/dev/mem`.

### Alternatives and Modern Practices

- **udev**:
  - Modern Linux systems use `udev`, a device manager for the Linux kernel, to dynamically create and manage device nodes in `/dev`. This automates the process of handling device nodes based on hardware events.
- **Using Static Device Nodes**:
  - In minimalistic environments or custom distributions, manually creating essential device nodes like `/dev/mem` using `mknod` ensures that critical functionalities are available without relying on dynamic device managers.

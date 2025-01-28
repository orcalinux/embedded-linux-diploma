# Creating a Simple Linux Distro

This guide outlines the steps to create a basic Linux distribution using QEMU and ARM architecture. The process involves installing necessary tools, configuring and building the Linux kernel, compiling Busybox, creating the RootFS, compressing the file system, and running QEMU with the created file system.

## Cloned Steps Source
The steps provided here are cloned from [Minimalistic Linux System on QEMU ARM](https://lukaszgemborowski.github.io/articles/minimalistic-linux-system-on-qemu-arm.html).

## Installation and Setup

### 1. Install QEMU
```bash
sudo apt install qemu-system-arm
```

### 2. Additional Step for ARM GCC Compilation
```bash
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
```
**Note:** This command installs necessary packages for compiling ARM GCC. 

### 3. Select ARM Versatile PB board
We will utilize the ARM Versatile PB board for emulation. Refer to the [QEMU documentation](https://www.qemu.org/docs/master/system/arm/versatile.html) for more details.

### 4. Install Cross Compiler
```bash
sudo apt install gcc-arm-linux-gnueabi
```

## Building the Kernel

### 5. Download and Extract Linux Kernel
```bash
# Download the Linux kernel source tarball
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.7.6.tar.xz

# Extract the downloaded tarball
tar xvf linux-6.7.6.tar.xz
```

### 6. Configure Kernel
```bash
# Navigate to the Linux kernel source directory
cd linux-6.7.6

# Configure the kernel for ARM architecture
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- versatile_defconfig
```
You can modify the configuration using:
```bash
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
```

### 7. Build Kernel and Modules
```bash
# Build the Linux kernel with multiple cores
time make -j8 O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

# Build kernel modules with multiple cores
time make -j8 modules O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
```

### 8. Install Kernel Modules
```bash
time make -j8 modules_install O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- INSTALL_MOD_PATH=../../rootfs
```

## Building Busybox

### 9. Download and Extract Busybox
Download the latest Busybox from [https://busybox.net/](https://busybox.net/) and untar it. For this guide, we are using Busybox version 1.36.1.

### 10. Compile Busybox
```bash
# Step 1: Navigate to the Busybox directory
cd busybox-1.36.1

# Step 2: Configure Busybox for ARM architecture
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig

# Step 3: Customize Busybox configuration
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
# Enable 'build busybox as a static binary' from Settings

# Step 4: Build Busybox with multiple cores
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8

# Step 5: Install Busybox on the system
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8 install
```

## Creating the RootFS

### 11. Prepare RootFS
```bash
# Navigate to the rootfs directory
cd ../rootfs

# Create necessary directories in the root file system
mkdir -p bin sbin etc proc sys usr/{bin,sbin}  
```

### 12. Create Init Script
Create the `init` script:
```bash
# Navigate back to the parent directory
cd ..

# Edit the init script
vim rootfs/init  
```
Fill it with the following content:
```bash
#!/bin/sh
echo -e "\nHello from the init process\n"

mount -tproc none /proc
mount -tsysfs none /sys
mknod -m660 /dev/mem c 1 1

exec /bin/sh
```

### 13. Set Permissions
```bash
chmod +x rootfs/init
```

### 14. Copy Busybox Files
```bash
cp -av busybox-1.36.1/_install/* rootfs/
```

### 15. Create RootFS Directory Structure
```bash
mkdir -pv rootfs/{bin,sbin,etc,proc,sys,usr/{bin,sbin}}
```

## Compressing the File System

### 16. Compress File System
```bash
# Navigate to the rootfs directory
cd rootfs/

# Create a newc-format cpio archive with null-terminated filenames and gzip compression
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../rootfs.cpio.gz
```

## Running QEMU

### 17. Run QEMU
```bash
# Navigate back to the parent directory
cd ..

# Run QEMU with the specified parameters to emulate the ARM architecture
qemu-system-arm -M versatilepb -kernel linux-6.7.6/build/arch/arm/boot/zImage -dtb linux-6.7.6/build/arch/arm/boot/dts/arm/versatile-pb.dtb -initrd rootfs.cpio.gz -serial stdio -append "root=/dev/mem serial=ttyAMA0"
```

---
## Conclusion

Follow these steps to create a simple Linux distribution using QEMU and ARM architecture. You can modify the configurations as per your requirements.

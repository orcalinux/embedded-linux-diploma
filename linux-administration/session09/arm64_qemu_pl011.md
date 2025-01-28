# README: Building & Running an ARM64 Kernel on QEMU (with PL011 Console)

## Table of Contents

- [README: Building \& Running an ARM64 Kernel on QEMU (with PL011 Console)](#readme-building--running-an-arm64-kernel-on-qemu-with-pl011-console)
  - [Table of Contents](#table-of-contents)
  - [1. Prerequisites](#1-prerequisites)
  - [2. Configure the Kernel (ARM64)](#2-configure-the-kernel-arm64)
  - [3. Build the Kernel](#3-build-the-kernel)
  - [4. Create or Verify Your Initramfs](#4-create-or-verify-your-initramfs)
    - [4.1 Minimal BusyBox Initramfs (Optional Example)](#41-minimal-busybox-initramfs-optional-example)
    - [4.2 Verify `/bin/sh` in the Initramfs](#42-verify-binsh-in-the-initramfs)
  - [5. Run Under QEMU](#5-run-under-qemu)
    - [5.1 Explanation of Flags](#51-explanation-of-flags)
  - [6. Troubleshooting](#6-troubleshooting)
  - [7. References](#7-references)

---

## 1. Prerequisites

1. **GNU Make** and related build tools.
2. **Cross-Compiler for aarch64** (unless you’re building natively on an ARM64 host).
   - On Debian/Ubuntu-based systems:
     ```bash
     sudo apt-get update
     sudo apt-get install gcc-aarch64-linux-gnu
     ```
3. **QEMU for aarch64**:
   ```bash
   sudo apt-get install qemu-system-arm
   ```
4. **Linux kernel source** (e.g., from kernel.org or a Git repository).

## 2. Configure the Kernel (ARM64)

1. Clone or download the kernel source, then move into its directory:
   ```bash
   cd ~/linux
   ```
2. Clean or reset your source tree if needed (optional):
   ```bash
   make mrproper
   ```
3. Open menuconfig **for ARM64** (important):
   ```bash
   make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
   ```
4. In menuconfig, ensure the following options are enabled (**built-in**, `[ * ]` not `<M>`):

   - **`CONFIG_SERIAL_AMBA_PL011`** = **y**
     - Found under:  
       `Device Drivers → Character devices → Serial drivers → ARM AMBA PL011 serial port support`
   - **`CONFIG_SERIAL_AMBA_PL011_CONSOLE`** = **y**
     - This option typically appears next to or under the PL011 driver option.
     - Allows using `ttyAMA0` as a console.
   - **`CONFIG_DEVTMPFS`** and **`CONFIG_DEVTMPFS_MOUNT`** = **y**
     - Found under:  
       `Device Drivers → Generic Driver Options`
   - **`CONFIG_BLK_DEV_INITRD`** = **y**
     - Under “General setup” or “Device Drivers” depending on your kernel version.
   - (Optional) **Early Console** support, such as `CONFIG_EARLY_PRINTK` or `CONFIG_EARLYCON` if available.

5. Save and exit.

## 3. Build the Kernel

After configuring:

```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
```

If successful, the kernel image will be in:

```
arch/arm64/boot/Image
```

You can verify it’s really an ARM64 kernel:

```bash
file arch/arm64/boot/Image
# Should say: "Linux kernel ARM64 boot executable Image, little-endian..."
```

## 4. Create or Verify Your Initramfs

### 4.1 Minimal BusyBox Initramfs (Optional Example)

1. **Build or install BusyBox** (preferably statically linked for simplicity).
2. Create a directory to assemble initramfs contents:
   ```bash
   mkdir -p rootfs/{bin,sbin,proc,sys,usr/bin,usr/sbin}
   ```
3. Copy or symlink BusyBox to `rootfs/bin/sh`:
   ```bash
   cp /path/to/busybox rootfs/bin
   ln -s busybox rootfs/bin/sh
   chmod +x rootfs/bin/busybox
   ```
4. Create a simple `init` script (optional if you are just using `rdinit=/bin/sh`). Or if you want a typical `init`, place a script in `rootfs/init` and make it executable.
5. Build the cpio:
   ```bash
   cd rootfs
   find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.cpio.gz
   ```

### 4.2 Verify `/bin/sh` in the Initramfs

Unpack the cpio:

```bash
mkdir /tmp/initramfs-check
cd /tmp/initramfs-check
zcat /path/to/initramfs.cpio.gz | cpio -idmv
ls -l bin/sh
ldd bin/sh   # Should say "not a dynamic executable" if static
```

A BusyBox link to `sh` is ideal for a minimal environment.

## 5. Run Under QEMU

From your kernel source top-level (or anywhere you have the correct paths):

```bash
qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a57 \
  -m 1G \
  -nographic \
  -kernel arch/arm64/boot/Image \
  -initrd arch/arm64/boot/initramfs.cpio.gz \
  -append "console=ttyAMA0 earlycon=pl011,0x9000000 rdinit=/bin/sh"
```

### 5.1 Explanation of Flags

- **`-M virt`**: Use QEMU’s “virt” platform, an emulated machine for 64-bit ARM.
- **`-cpu cortex-a57`**: Emulated CPU type (other valid choices exist, like `cortex-a53`).
- **`-m 1G`**: Allocate 1 GB of RAM to the guest.
- **`-nographic`**: Use the serial console in the terminal (no GUI window).
- **`-kernel ...`**: Path to our newly built ARM64 kernel.
- **`-initrd ...`**: Path to your initramfs CPIO.
- **`-append "console=ttyAMA0 earlycon=pl011,0x9000000 rdinit=/bin/sh"`**:
  - `console=ttyAMA0` instructs the kernel to use the PL011 UART as its main console.
  - `earlycon=pl011,0x9000000` enables early boot messages on the same UART.
  - `rdinit=/bin/sh` sets the root init process to BusyBox’s `sh`.

If everything is correct, you should see kernel boot messages in your terminal and eventually drop to a BusyBox shell prompt. Press **Enter** a couple of times if you see a black screen.

## 6. Troubleshooting

1. **No Output?**

   - Confirm `CONFIG_SERIAL_AMBA_PL011=y` **and** `CONFIG_SERIAL_AMBA_PL011_CONSOLE=y`.
   - Ensure you’re using the **arm64** kernel config, not x86.
   - Check your QEMU command lines for correct file paths.

2. **Missing `/bin/sh`**

   - Unpack your `initramfs.cpio.gz` to confirm `bin/sh` exists and is executable.

3. **Dynamic Library Errors**

   - If BusyBox is dynamically linked, ensure all required libraries are also inside the initramfs at the correct `/lib` or `/lib64` paths.

4. **Kernel Panics or Hangs**
   - Add more debug flags to the kernel command line:
     ```
     loglevel=8 initcall_debug
     ```
   - Enable early print support in the kernel config (`CONFIG_EARLY_PRINTK` or `CONFIG_EARLYCON`) for extra messages.

## 7. References

- [Kernel.org Documentation](https://www.kernel.org/doc/html/latest/)
- [BusyBox Official Site](https://www.busybox.net/)
- [QEMU User Documentation](https://www.qemu.org/docs/master/)

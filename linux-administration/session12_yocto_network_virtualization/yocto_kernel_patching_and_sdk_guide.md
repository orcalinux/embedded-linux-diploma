# Complete Guide: Patching the Linux Kernel in Yocto, Testing with QEMU, and Generating an SDK

## Table of Contents

- [Complete Guide: Patching the Linux Kernel in Yocto, Testing with QEMU, and Generating an SDK](#complete-guide-patching-the-linux-kernel-in-yocto-testing-with-qemu-and-generating-an-sdk)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Prerequisites \& Environment Setup](#prerequisites--environment-setup)
  - [3. Set Up Your Yocto Environment](#3-set-up-your-yocto-environment)
  - [4. Locate the Kernel Source in Yocto](#4-locate-the-kernel-source-in-yocto)
  - [5. Patch or Modify the Kernel Source](#5-patch-or-modify-the-kernel-source)
    - [Option A: Use `devtool` (Recommended)](#option-a-use-devtool-recommended)
    - [Option B: Manually Add Patches to Your Kernel Recipe](#option-b-manually-add-patches-to-your-kernel-recipe)
  - [6. Rebuild the Kernel](#6-rebuild-the-kernel)
  - [7. Running a QEMU Machine to Test](#7-running-a-qemu-machine-to-test)
  - [8. Viewing Your New Kernel Message](#8-viewing-your-new-kernel-message)
  - [9. Generate a Cross-Compiler SDK (Optional)](#9-generate-a-cross-compiler-sdk-optional)
    - [Recommended Method: `-c populate_sdk`](#recommended-method--c-populate_sdk)
    - [Older Method: `meta-toolchain`](#older-method-meta-toolchain)
  - [10. Use the Installed SDK](#10-use-the-installed-sdk)
  - [11. Tips \& Best Practices](#11-tips--best-practices)
  - [Summary](#summary)

---

## Overview

This guide demonstrates how to:

-   **Set up** a Yocto Project build environment.
-   **Locate** and **patch** the Linux kernel source (including a `printk()` example).
-   **Rebuild** the kernel with custom modifications.
-   **Run** a QEMU machine to see your new kernel in action.
-   **Generate** a cross-compiler SDK for additional kernel or user-space development.

---

## Prerequisites & Environment Setup

1. A **Yocto Project** release (Poky) for your chosen branch (e.g., `dunfell`, `kirkstone`, `master`, etc.).
2. A Linux host environment that meets the [Yocto Project build requirements](https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html).
3. Basic familiarity with **BitBake** and how to run commands like `bitbake virtual/kernel`.
4. A typical Yocto directory structure, for example:
    ```
    poky/
    ├── meta
    ├── meta-poky
    ├── meta-yocto-bsp
    └── oe-init-build-env
    ```

---

## 3. Set Up Your Yocto Environment

1. **Clone** or otherwise acquire **Poky** (the Yocto Project reference distribution). For example:

    ```bash
    git clone -b kirkstone git://git.yoctoproject.org/poky.git
    cd poky
    ```

    _(Adjust branch names to match your chosen release.)_

2. **Initialize** the build environment:

    ```bash
    source oe-init-build-env
    ```

    This creates or enters a `build/` directory and sets up the necessary environment variables.

3. In `build/conf/local.conf`, set **MACHINE** to match your target. For QEMU testing:

    ```ini
    MACHINE ?= "qemux86-64"
    ```

    _(For hardware targets, use their respective MACHINE definitions, e.g., `beaglebone`.)_

4. If you have custom BSP or meta-layers, **add** them in `conf/bblayers.conf`.

---

## 4. Locate the Kernel Source in Yocto

After you build or prepare `virtual/kernel`, Yocto unpacks the kernel source in:

```
build/tmp/work-shared/<MACHINE>/kernel-source
```

-   **build/** is your build directory (default name `build`).
-   **tmp/** is the default output directory.
-   **work-shared/** holds common components like kernel sources.
-   **\<MACHINE\>** matches your chosen MACHINE (e.g., `qemux86-64`).

> **Tip**: If the directory doesn’t exist yet, run:
>
> ```bash
> bitbake virtual/kernel
> ```
>
> to trigger the kernel source unpack and patching process.

---

## 5. Patch or Modify the Kernel Source

There are two common approaches to modifying the kernel in Yocto:

### Option A: Use `devtool` (Recommended)

1. **Prepare** the kernel for local development:

    ```bash
    devtool modify virtual/kernel
    ```

    This copies the kernel sources to a workspace directory (e.g., `workspace/sources/linux-yocto/`).

2. **Make your changes**. For example, add a `printk()` in `init/main.c`:
    ```c
    static noinline void __init_refok rest_init(void)
    {
        printk(KERN_INFO "Hello from my custom kernel patch!\n");
        ...
    }
    ```
3. **Build and test** your modified kernel:

    ```bash
    devtool build virtual/kernel
    ```

    The rebuilt kernel image appears under `tmp/deploy/images/<MACHINE>/`.

4. **Finish** your changes into a proper patch/recipe in your custom layer:
    ```bash
    devtool finish virtual/kernel ../meta-custom
    ```
    This ensures you have a maintainable set of patches in your layer.

### Option B: Manually Add Patches to Your Kernel Recipe

1. **Modify** the kernel source in `build/tmp/work-shared/<MACHINE>/kernel-source`.
2. **Create a patch** from your diff:
    ```bash
    cd build/tmp/work-shared/<MACHINE>/kernel-source
    git diff > my-custom.patch
    ```
3. **Place** `my-custom.patch` in your layer (e.g., `recipes-kernel/linux/files/`).
4. **Update** the kernel recipe (`linux-yocto.bb` or similar):
    ```bb
    SRC_URI += "file://my-custom.patch"
    ```
5. **Increment** the PR (package release) or adjust `SRCREV` as needed, then:
    ```bash
    bitbake virtual/kernel
    ```

---

## 6. Rebuild the Kernel

Regardless of which patching approach you use:

```bash
bitbake virtual/kernel
```

The new kernel image(s) will be in:

```
build/tmp/deploy/images/<MACHINE>/
```

For QEMU x86-64, it might be `bzImage` in:

```
build/tmp/deploy/images/qemux86-64/
```

---

## 7. Running a QEMU Machine to Test

Yocto provides the `runqemu` script to quickly boot a QEMU machine with your newly built kernel and root filesystem.

1. **Build** a Yocto image (e.g., `core-image-minimal`) that includes your kernel:
    ```bash
    bitbake core-image-minimal
    ```
2. **Launch** QEMU:
    ```bash
    runqemu qemux86-64
    ```
    Or explicitly specify:
    ```bash
    runqemu qemux86-64 core-image-minimal
    ```
    The system should boot using the newly built kernel.

---

## 8. Viewing Your New Kernel Message

Inside the QEMU console, run:

```bash
dmesg | grep "Hello from my custom kernel patch"
```

You should see your **`printk()`** message indicating the kernel patch is active.

---

## 9. Generate a Cross-Compiler SDK (Optional)

If you want to build additional kernel modules or user-space apps matching your kernel’s environment, generate a **Yocto SDK**.

### Recommended Method: `-c populate_sdk`

1. **BitBake** your chosen image (e.g., `core-image-minimal`) with the `populate_sdk` task:
    ```bash
    bitbake core-image-minimal -c populate_sdk
    ```
2. An **SDK installer** appears in:
    ```
    build/tmp/deploy/sdk/poky-glibc-<host_arch>-core-image-minimal-<target_arch>-toolchain-<VERSION>.sh
    ```
3. **Run** that installer script:
    ```bash
    ./poky-glibc-x86_64-core-image-minimal-qemux86-64-toolchain-3.1.10.sh
    ```
    By default, it installs into something like `/opt/poky/3.1.10`.

### Older Method: `meta-toolchain`

If you just need a generic toolchain (not tied to a specific image’s libraries):

```bash
bitbake meta-toolchain
```

Installer is placed in `build/tmp/deploy/sdk/` (e.g., `poky-glibc-x86_64-meta-toolchain-<target_arch>-toolchain-3.1.10.sh`).

---

## 10. Use the Installed SDK

After installing:

1. **Source** the environment setup file:

    ```bash
    source /opt/poky/3.1.10/environment-setup-x86_64-poky-linux
    ```

    _(Path and filenames vary by architecture and version.)_

2. Verify the cross-compiler:
    ```bash
    which x86_64-poky-linux-gcc
    x86_64-poky-linux-gcc --version
    ```
3. You can now cross-compile applications (or external kernel modules) matching your new kernel environment. For instance:
    ```bash
    cmake -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake .
    make
    ```

---

## 11. Tips & Best Practices

-   **Use `devtool`** for a streamlined kernel-development workflow; it automates patch management.
-   **Keep patches small** and well-documented. This simplifies reviewing and debugging.
-   **Regenerate the SDK** whenever you change major kernel ABI aspects or user-space libraries that your apps depend on.
-   **Test changes** in QEMU or on real hardware if possible. Always verify your new kernel boots properly and logs your `printk()` messages.

---

## Summary

1. **Set up** your Yocto environment by sourcing `oe-init-build-env` and configuring `MACHINE`.
2. **Locate** the kernel source in `build/tmp/work-shared/<MACHINE>/kernel-source`, or use `devtool modify virtual/kernel`.
3. **Patch** the kernel (e.g., add a `printk()`) via `devtool` or manual patching in the kernel recipe.
4. **Rebuild** the kernel with `bitbake virtual/kernel`.
5. **Build** an image (e.g., `core-image-minimal`) and **run** it in QEMU (`runqemu`) to see your kernel changes in action.
6. **Check** the console logs (e.g., `dmesg`) for your custom `printk()`.
7. **(Optional)** Generate an SDK (`-c populate_sdk`) and **use** it to cross-compile additional modules or applications.

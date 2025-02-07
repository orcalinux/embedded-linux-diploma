# **Adding Packages to Your Yocto Image**

## **Overview**

This guide walks through two key methods for including software packages in a Yocto image:

1. **Pre-Build (Static Inclusion):**  
   Statically add packages by modifying image recipes or configuration files (`local.conf`) so that they are **automatically** included in the final image.

2. **Post-Build (Dynamic Installation):**  
   Dynamically add packages **after** the system is already built and booted (e.g., via `opkg`, `dnf`, or another package manager running inside the target).

By leveraging these two approaches, you can flexibly meet your distribution requirements. For example, **pre-build** inclusion is ideal for a minimal, consistent production image, while **post-build** installation offers a more dynamic or development-friendly workflow.

---

## **Table of Contents**

- [**Adding Packages to Your Yocto Image**](#adding-packages-to-your-yocto-image)
  - [**Overview**](#overview)
  - [**Table of Contents**](#table-of-contents)
  - [1. **Prerequisites**](#1-prerequisites)
  - [2. **Adding Packages Pre-Build**](#2-adding-packages-pre-build)
    - [Setting Up the Build Environment](#setting-up-the-build-environment)
    - [Modifying `local.conf` (Option 1)](#modifying-localconf-option-1)
    - [Creating a Custom Image Recipe (Option 2)](#creating-a-custom-image-recipe-option-2)
    - [Best Practices for Pre-Build Inclusion](#best-practices-for-pre-build-inclusion)
  - [3. **Adding Packages Post-Build**](#3-adding-packages-post-build)
    - [Ensuring Package Management Support](#ensuring-package-management-support)
    - [Booting the Yocto Image](#booting-the-yocto-image)
    - [Installing Packages via `opkg`](#installing-packages-via-opkg)
    - [Other Package Managers](#other-package-managers)
  - [4. **Example: Installing Quagga Using `opkg`**](#4-example-installing-quagga-using-opkg)
  - [5. **Additional Tips \& Best Practices**](#5-additional-tips--best-practices)
  - [6. **References**](#6-references)
  - [**Conclusion**](#conclusion)

---

## 1. **Prerequisites**

-   A functional **Yocto environment** (Poky or another distribution) with your **MACHINE** set (e.g. `qemux86-64`).
-   Basic familiarity with BitBake commands and recipes (e.g., `bitbake core-image-minimal`).
-   Enough disk space and network connectivity for downloads and builds.

---

## 2. **Adding Packages Pre-Build**

### Setting Up the Build Environment

1. **Initialize Your Yocto Build Environment**  
   Navigate to your Yocto installation (e.g., `poky` directory) and source the environment:
    ```bash
    cd poky
    source oe-init-build-env
    ```
    This sets up environment variables like `BBPATH` and enters your build directory (e.g., `build-qemux86-64`).

---

### Modifying `local.conf` (Option 1)

A quick way to add packages is by appending them to `IMAGE_INSTALL` in `conf/local.conf`.

1. **Open `local.conf`:**
    ```bash
    nano conf/local.conf
    ```
2. **Append Packages:**

    ```plaintext
    IMAGE_INSTALL_append = " quagga python3"
    ```

    - **Note**: The space before the first package name is important.
    - This ensures the packages (`quagga` and `python3` in this example) are installed into your final image.

3. **Save & Close** the file.

4. **Build the Image:**
    ```bash
    bitbake core-image-minimal
    ```
    or any other image recipe you use (e.g. `my-custom-image`).

---

### Creating a Custom Image Recipe (Option 2)

For a cleaner, more maintainable approach, create a **custom image recipe** in your own layer.

1. **Create a Custom Recipe: `my-image.bb`**  
   In, for example, `meta-my-layer/recipes-core/images/my-image.bb`:

    ```plaintext
    require recipes-core/images/core-image-minimal.bb

    DESCRIPTION = "My custom Yocto image with additional packages."

    # Append desired packages
    IMAGE_INSTALL_append = " quagga python3 nano"
    ```

2. **Add Your Layer to `bblayers.conf`**  
   Ensure `meta-my-layer` is listed in `conf/bblayers.conf`.

3. **Build Your Image:**
    ```bash
    bitbake my-image
    ```
    The resulting image includes the additional packages.

---

### Best Practices for Pre-Build Inclusion

-   **Use a Dedicated Layer**: Keep custom changes separate from Poky’s default metadata.
-   **Avoid Local.conf for Production**: For large or shared projects, prefer a dedicated **image recipe** rather than cluttering `local.conf`.
-   **Check Dependencies**: Some packages have additional dependencies that might need to be appended (e.g., dev packages, libraries).
-   **Use `IMAGE_FEATURES`**: For certain features (e.g., debugging tools), you can set `EXTRA_IMAGE_FEATURES += "tools-debug"` or similar in your recipe.

---

## 3. **Adding Packages Post-Build**

### Ensuring Package Management Support

1. **Enable Package Manager in the Image**  
   Edit `conf/local.conf` to add:

    ```plaintext
    EXTRA_IMAGE_FEATURES += "package-management"
    ```

    This ensures your built image contains a functional package manager (e.g., `opkg`, `dnf`, or `rpm` tools).

2. **Rebuild the Image**
    ```bash
    bitbake core-image-minimal
    ```
    or your custom recipe if you prefer.

---

### Booting the Yocto Image

1. **Launch with QEMU**  
   Example (for x86_64):

    ```bash
    runqemu qemux86-64 nographic
    ```

    or use a more manual QEMU command:

    ```bash
    qemu-system-x86_64 \
      -m 512 \
      -hda tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.ext4 \
      -net nic -net tap,ifname=tap0,script=no,downscript=no \
      -daemonize
    ```

2. **Obtain the VM’s IP**  
   If using `runqemu`, BitBake often sets up user-mode networking. If bridging/tap is used, you might assign a static IP or use DHCP.

---

### Installing Packages via `opkg`

Assuming `opkg` is included in your image:

1. **SSH into the VM**
    ```bash
    ssh root@<vm-ip>
    ```
2. **Update Package Lists**
    ```bash
    opkg update
    ```
3. **Install the Package**
    ```bash
    opkg install quagga
    ```
    This downloads and installs the package from your configured feeds.

---

### Other Package Managers

Depending on your Yocto configuration, you may have **`dnf`** or **`rpm`** in place of `opkg`. The process is similar:

-   **Update**: `dnf update` or `dnf makecache`
-   **Install**: `dnf install <pkg>`
-   **Remove**: `dnf remove <pkg>`

Ensure your feed configuration (e.g., `/etc/opkg/` or `/etc/yum.repos.d/`) is correct.

---

## 4. **Example: Installing Quagga Using `opkg`**

1. **Set Up the Build Environment**
    ```bash
    source oe-init-build-env
    ```
2. **Add Package Management**  
   In `local.conf`:
    ```plaintext
    EXTRA_IMAGE_FEATURES += "package-management"
    ```
3. **Build the Image**
    ```bash
    bitbake core-image-minimal
    ```
4. **Boot the Image**
    ```bash
    runqemu qemux86-64 nographic
    ```
    or your preferred machine.
5. **Install Quagga**
    1. **SSH**: `ssh root@<vm-ip>`
    2. **Update**: `opkg update`
    3. **Install**: `opkg install quagga`

---

## 5. **Additional Tips & Best Practices**

-   **Choosing the Right Packages**: Ensure the packages exist in your configured **layers** or **feeds**. If a package isn’t found, you may need to add a meta-layer that provides it or create a new recipe.
-   **Controlling Image Size**: Pre-building numerous packages can bloat your image. Balance minimal images vs. comprehensive tool inclusion.
-   **Version Pinning**: For precise control, specify the recipe version or hash in your layer, or use `PREFERRED_VERSION` in `conf/local.conf`.
-   **Deploying to Target Hardware**: After building, you can flash the image to SD/eMMC (for embedded boards) or run on QEMU for x86 targets.

---

## 6. **References**

-   [Yocto Project Documentation](https://docs.yoctoproject.org/)
-   [Yocto Project Development Tasks Manual](https://docs.yoctoproject.org/dev-manual/index.html)
-   [Poky Reference Manual](https://docs.yoctoproject.org/ref-manual/index.html)
-   [OpenEmbedded Layer Index](http://layers.openembedded.org/)

---

## **Conclusion**

By following the instructions in this guide, you can **customize your Yocto image** by adding packages either:

-   **Pre-Build**: Automatically include packages by modifying `local.conf` or creating a custom image recipe.
-   **Post-Build**: Dynamically install additional packages at runtime, provided your image has a package manager.

This two-tiered approach offers a flexible development workflow, ensuring you can ship minimal, production-grade images while still having the ability to install or test new software on the fly.

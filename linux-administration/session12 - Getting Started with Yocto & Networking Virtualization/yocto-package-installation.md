# Adding Packages to Yocto Image

## Overview

This guide provides detailed instructions on how to add packages to a Yocto image both during the build process and after the image has been built and is running. This is useful for customizing your Yocto image with specific software packages required for your application.

## Table of Contents

1. [Adding Packages Pre-Build](#adding-packages-pre-build)
   - [Setting Up Yocto Build Environment](#setting-up-yocto-build-environment)
   - [Modifying Local Configuration](#modifying-local-configuration)
   - [Creating a Custom Image Recipe](#creating-a-custom-image-recipe)
   - [Building the Yocto Image](#building-the-yocto-image)
2. [Adding Packages Post-Build](#adding-packages-post-build)
   - [Ensuring Package Management Support](#ensuring-package-management-support)
   - [Booting the Yocto Image](#booting-the-yocto-image)
   - [Installing Packages Using Package Manager](#installing-packages-using-package-manager)

---

## Adding Packages Pre-Build

### Setting Up Yocto Build Environment

1. **Set Up Your Yocto Build Environment**:
   Ensure that you have set up your Yocto build environment correctly. Source the environment setup script.
   ```sh
   source oe-init-build-env
   ```

### Modifying Local Configuration

2. **Modify the Image Recipe**:
   Edit the image recipe to include the additional packages you need.

   ### Option 1: Modify `local.conf`
   Add the following line to `conf/local.conf`:
   ```plaintext
   IMAGE_INSTALL_append = " quagga"
   ```

### Creating a Custom Image Recipe

   ### Option 2: Create a Custom Image Recipe
   Create a custom image recipe, e.g., `my-image.bb` in your layer (e.g., `meta-my-layer/recipes-core/images/my-image.bb`):
   ```plaintext
   require recipes-core/images/core-image-minimal.bb

   IMAGE_INSTALL_append = " quagga"
   ```

### Building the Yocto Image

3. **Build the Image**:
   Run the build command to create the new image with the added packages.
   ```sh
   bitbake core-image-minimal
   ```

---

## Adding Packages Post-Build

### Ensuring Package Management Support

1. **Ensure Package Management Support in Yocto Image**:
   First, make sure your Yocto image has a package manager included. You can add package management support to your image by modifying the `local.conf` file.
   ```plaintext
   EXTRA_IMAGE_FEATURES += "package-management"
   ```

### Booting the Yocto Image

2. **Rebuild Your Yocto Image**:
   Rebuild your Yocto image to include the package manager.
   ```sh
   bitbake core-image-minimal
   ```

3. **Boot the Yocto Image with QEMU**:
   Boot your Yocto image with QEMU.
   ```sh
   qemu-system-x86_64 -m 512 -hda tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.ext4 -net nic -net tap,ifname=tap0,script=no,downscript=no -daemonize
   ```

### Installing Packages Using Package Manager

4. **Install Packages Using the Package Manager**:
   Once the image is running, you can install additional packages using the package manager. Here’s how you can do it with `opkg` (assuming `opkg` is the package manager in your image).

   **a. SSH into the Running Yocto VM**:
   ```sh
   ssh root@<vm-ip>
   ```

   **b. Update the Package List**:
   ```sh
   opkg update
   ```

   **c. Install the Desired Package (e.g., `quagga`)**:
   ```sh
   opkg install quagga
   ```

### Example: Installing Quagga Using `opkg`

1. **Set Up Yocto Build Environment**:
   ```sh
   source oe-init-build-env
   ```

2. **Add Package Management to `local.conf`**:
   ```plaintext
   EXTRA_IMAGE_FEATURES += "package-management"
   ```

3. **Build the Image**:
   ```sh
   bitbake core-image-minimal
   ```

4. **Boot the Yocto Image with QEMU**:
   ```sh
   qemu-system-x86_64 -m 512 -hda tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.ext4 -net nic -net tap,ifname=tap0,script=no,downscript=no -daemonize
   ```

5. **SSH into the VM and Install Quagga**:
   ```sh
   ssh root@<vm-ip>
   opkg update
   opkg install quagga
   ```

---

By following these steps, you can add packages to your Yocto image both during the build process and after the image has been built and is running. This provides flexibility in customizing your Yocto image to suit your specific needs.


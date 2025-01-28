# Secure Boot in Linux: Comprehensive Guide with Demonstrations

Welcome to the **Secure Boot in Linux** guide. This README provides an in-depth exploration of Secure Boot technology, its implementation in Linux systems, and practical demonstrations to help you understand and utilize Secure Boot effectively. Whether you're a system administrator, developer, or Linux enthusiast, this guide will equip you with the knowledge and hands-on experience needed to secure your Linux environment.

## Table of Contents

1. [Introduction to Secure Boot](#introduction-to-secure-boot)
2. [How Secure Boot Works](#how-secure-boot-works)
3. [Prerequisites](#prerequisites)
4. [Setting Up Secure Boot on a Linux System](#setting-up-secure-boot-on-a-linux-system)
   - [Demo 1: Installing a Linux Distribution with Secure Boot Enabled](#demo-1-installing-a-linux-distribution-with-secure-boot-enabled)
   - [Demo 2: Verifying Secure Boot Status](#demo-2-verifying-secure-boot-status)
5. [Managing Secure Boot Keys](#managing-secure-boot-keys)
   - [Demo 3: Enrolling a Custom Key](#demo-3-enrolling-a-custom-key)
   - [Demo 4: Signing the Bootloader and Kernel](#demo-4-signing-the-bootloader-and-kernel)
6. [Handling Third-Party Drivers and Modules](#handling-third-party-drivers-and-modules)
   - [Demo 5: Signing a Third-Party Kernel Module](#demo-5-signing-a-third-party-kernel-module)
7. [Troubleshooting Secure Boot](#troubleshooting-secure-boot)
   - [Demo 6: Disabling Secure Boot](#demo-6-disabling-secure-boot)
8. [Best Practices](#best-practices)
9. [Additional Resources](#additional-resources)

---

## Introduction to Secure Boot

**Secure Boot** is a security standard developed by the Unified Extensible Firmware Interface (UEFI) consortium. It ensures that a device boots using only software that is trusted by the Original Equipment Manufacturer (OEM). When enabled and properly configured, Secure Boot helps protect against malware and unauthorized software from running during the boot process.

### Key Benefits

- **Protection Against Bootkits and Rootkits**: Prevents malicious software from loading before the operating system.
- **Integrity Verification**: Ensures that bootloaders and kernel images are signed and unaltered.
- **Compliance**: Meets security requirements for certain industries and applications.

---

## How Secure Boot Works

Secure Boot operates by verifying the digital signatures of each component involved in the boot process. The verification chain typically follows these steps:

1. **Firmware Verification**: The UEFI firmware verifies its own signature to ensure it's trusted.
2. **Bootloader Verification**: The firmware verifies the bootloader's signature.
3. **Kernel Verification**: The bootloader verifies the kernel's signature.
4. **Module Verification**: Any additional kernel modules are verified before loading.

If any component fails verification, the boot process is halted, preventing potentially malicious software from executing.

---

## Prerequisites

Before proceeding with the demonstrations, ensure you have the following:

- **Hardware Requirements**:

  - A system with UEFI firmware (most modern systems support UEFI).
  - Access to BIOS/UEFI settings to enable/disable Secure Boot.

- **Software Requirements**:

  - A Linux distribution that supports Secure Boot (e.g., Ubuntu, Fedora, openSUSE).
  - Tools for managing keys and signing binaries (`openssl`, `sbsigntool`, `shim`, etc.).

- **Administrative Privileges**:

  - Ability to perform actions with `sudo` or root access.

- **Backup**:
  - It's recommended to back up important data before modifying firmware settings or performing key management tasks.

---

## Setting Up Secure Boot on a Linux System

This section guides you through installing a Linux distribution with Secure Boot enabled and verifying its status.

### Demo 1: Installing a Linux Distribution with Secure Boot Enabled

**Objective**: Install a Linux distribution ensuring Secure Boot is enabled throughout the process.

**Steps**:

1. **Prepare Installation Media**:

   - Download the desired Linux distribution ISO (e.g., Ubuntu).
   - Create a bootable USB drive using tools like `Rufus` or `Etcher`.

2. **Enable Secure Boot in UEFI Firmware**:

   - Restart your computer and enter the BIOS/UEFI settings (commonly by pressing `F2`, `F10`, `Del`, or `Esc` during boot).
   - Navigate to the `Security` or `Boot` tab.
   - Ensure that **Secure Boot** is enabled.
   - Save changes and exit.

3. **Boot from Installation Media**:

   - Insert the bootable USB drive.
   - Restart the system and boot from the USB (may require selecting the boot device manually).

4. **Proceed with Installation**:

   - Follow the on-screen instructions to install the Linux distribution.
   - The installer should recognize that Secure Boot is enabled and configure necessary components (like `shim` and signed bootloaders).

5. **Post-Installation Verification**:
   - After installation, boot into the newly installed Linux system.

**Notes**:

- Most mainstream Linux distributions handle Secure Boot automatically during installation.
- If prompted, allow the installation to enroll the distribution's key into the firmware.

---

### Demo 2: Verifying Secure Boot Status

**Objective**: Confirm whether Secure Boot is enabled on your Linux system.

**Steps**:

#### Method 1: Using `mokutil`

1. **Install `mokutil`**:

   ```bash
   sudo apt update
   sudo apt install mokutil
   ```

2. **Check Secure Boot Status**:

   ```bash
   mokutil --sb-state
   ```

   _Expected Output_:

   ```
   SecureBoot enabled
   ```

   or

   ```
   SecureBoot disabled
   ```

#### Method 2: Using `bootctl`

1. **Install `systemd-boot` (if not already installed)**:

   ```bash
   sudo apt install systemd-boot
   ```

2. **Check Secure Boot Status**:

   ```bash
   bootctl status
   ```

   _Expected Output_:

   ```
   System:
       Firmware: UEFI  X.Y
       Secure Boot: enabled
       ...
   ```

   or

   ```
   System:
       Firmware: UEFI  X.Y
       Secure Boot: disabled
       ...
   ```

**Notes**:

- The `bootctl` method provides a comprehensive status including firmware details.
- Ensure that `systemd-boot` is installed to use `bootctl`. Some distributions may already have it set up.

#### Method 3: Checking UEFI Variables

1. **View Secure Boot Variable**:

   ```bash
   sudo cat /sys/firmware/efi/vars/SecureBoot-*/data | hexdump -C
   ```

   _Interpretation_:

   - A value of `01` typically indicates Secure Boot is enabled.
   - A value of `00` indicates it is disabled.

#### Method 4: Using `dmesg`

1. **Search Boot Messages for Secure Boot Status**:

   ```bash
   dmesg | grep -i secureboot
   ```

   _Expected Output_:

   ```
   [    0.000000] Secure boot enabled
   ```

   or

   ```
   [    0.000000] Secure boot disabled
   ```

**Summary of Commands**:

| Method         | Command                                             | Description                               |
| -------------- | --------------------------------------------------- | ----------------------------------------- | --------------------------------------------- |
| `mokutil`      | `mokutil --sb-state`                                | Directly displays Secure Boot status      |
| `bootctl`      | `bootctl status`                                    | Provides comprehensive Secure Boot status |
| UEFI Variables | `sudo cat /sys/firmware/efi/vars/SecureBoot-\*/data | hexdump -C`                               | Checks the raw Secure Boot variable data      |
| `dmesg`        | `dmesg                                              | grep -i secureboot`                       | Searches kernel boot messages for Secure Boot |

**Recommendation**:

- **Primary Method**: Use `mokutil --sb-state` for a straightforward status check.
- **Alternative**: Use `bootctl status` for additional firmware details if `bootctl` is available.

---

## Managing Secure Boot Keys

Secure Boot relies on a set of cryptographic keys to verify the integrity of boot components. Managing these keys involves enrolling custom keys, signing binaries, and maintaining the trust chain.

### Demo 3: Enrolling a Custom Key

**Objective**: Add a custom Secure Boot key to the system's key database.

**Steps**:

1. **Generate a Custom Key Pair**:

   ```bash
   mkdir ~/secureboot-keys
   cd ~/secureboot-keys

   # Generate private key
   openssl req -new -x509 -newkey rsa:2048 -keyout custom_key.key -out custom_key.crt -days 3650 -nodes -subj "/CN=Custom Secure Boot Key/"

   # Convert the certificate to DER format
   openssl x509 -in custom_key.crt -outform DER -out custom_key.cer
   ```

2. **Enroll the Key Using `mokutil`**:

   ```bash
   sudo mokutil --import custom_key.crt
   ```

   _Instructions_:

   - You will be prompted to create a password. This password will be used to confirm the enrollment in the next step.

3. **Reboot and Complete Enrollment**:

   - Restart your system.
   - During boot, the **Machine Owner Key (MOK)** manager will appear.
   - Select `Enroll MOK`.
   - Choose `Continue`.
   - Enter the password you set earlier.
   - Confirm and reboot.

4. **Verify Key Enrollment**:

   ```bash
   mokutil --list-enrolled
   ```

   _Expected Output_:

   ```
   Certificate 0:
       Hash of database contents: ...
       Subject: CN=Custom Secure Boot Key
       Issuer: CN=Custom Secure Boot Key
       Serial Number: ...
   ```

**Notes**:

- Enrolling a custom key allows you to sign your own binaries, maintaining the Secure Boot trust chain.
- Handle private keys securely; unauthorized access can compromise system security.

---

### Demo 4: Signing the Bootloader and Kernel

**Objective**: Sign the bootloader and kernel using the custom key to ensure they are trusted by Secure Boot.

**Steps**:

1. **Install `sbsigntool`**:

   ```bash
   sudo apt install sbsigntool
   ```

2. **Locate the Bootloader and Kernel**:

   - **Bootloader**: Typically located at `/boot/efi/EFI/<distribution>/shimx64.efi` or `grubx64.efi`.
   - **Kernel**: Located at `/boot/vmlinuz-<version>`.

3. **Sign the Bootloader**:

   ```bash
   sudo sbsign --key ~/secureboot-keys/custom_key.key --cert ~/secureboot-keys/custom_key.crt --output /boot/efi/EFI/<distribution>/shimx64.efi.signed /boot/efi/EFI/<distribution>/shimx64.efi
   ```

   _Replace `<distribution>` with your Linux distribution's folder name._

4. **Sign the Kernel**:

   ```bash
   sudo sbsign --key ~/secureboot-keys/custom_key.key --cert ~/secureboot-keys/custom_key.crt --output /boot/vmlinuz-<version>.signed /boot/vmlinuz-<version>
   ```

   _Replace `<version>` with your kernel version._

5. **Update Bootloader Configuration**:

   - Modify the bootloader's configuration to use the signed binaries.
   - For GRUB, edit `/etc/default/grub` and update the `GRUB_CMDLINE_LINUX` parameter if necessary.
   - Regenerate GRUB configuration:

     ```bash
     sudo update-grub
     ```

6. **Reboot and Verify**:

   ```bash
   sudo reboot
   ```

   - Ensure the system boots without Secure Boot errors.
   - Verify that the signed kernel is in use:

     ```bash
     uname -v
     ```

**Notes**:

- Signing the bootloader and kernel is essential for maintaining the Secure Boot trust chain.
- Ensure that any updates to the bootloader or kernel are re-signed with the custom key.

---

## Handling Third-Party Drivers and Modules

Third-party kernel modules must be signed to be loaded under Secure Boot. This section demonstrates how to sign a custom kernel module.

### Demo 5: Signing a Third-Party Kernel Module

**Objective**: Sign a custom kernel module so it can be loaded with Secure Boot enabled.

**Steps**:

1. **Prepare the Kernel Module**:

   - Obtain or compile a third-party kernel module (e.g., `example_module.ko`).

2. **Sign the Kernel Module**:

   ```bash
   sudo sbsign --key ~/secureboot-keys/custom_key.key --cert ~/secureboot-keys/custom_key.crt --output /lib/modules/$(uname -r)/kernel/drivers/example_module.ko.signed /lib/modules/$(uname -r)/kernel/drivers/example_module.ko
   ```

3. **Update Module Dependencies**:

   ```bash
   sudo depmod -a
   ```

4. **Load the Signed Module**:

   ```bash
   sudo modprobe example_module.ko.signed
   ```

   _Alternatively, rename the signed module to replace the original:_

   ```bash
   sudo mv /lib/modules/$(uname -r)/kernel/drivers/example_module.ko.signed /lib/modules/$(uname -r)/kernel/drivers/example_module.ko
   sudo depmod -a
   sudo modprobe example_module
   ```

5. **Verify Module Loading**:

   ```bash
   lsmod | grep example_module
   ```

   _Expected Output_:

   ```
   example_module        16384  0
   ```

**Notes**:

- Ensure that the module's `.ko` file is correctly signed.
- Unsigned modules will fail to load with Secure Boot enabled, maintaining system security.

---

## Troubleshooting Secure Boot

Issues may arise when Secure Boot is enabled, such as failure to load unsigned binaries or modules. This section guides you through disabling Secure Boot as a troubleshooting measure.

### Demo 6: Disabling Secure Boot

**Objective**: Disable Secure Boot in UEFI firmware to allow loading of unsigned binaries.

**Steps**:

1. **Access UEFI Firmware Settings**:

   - Restart your computer.
   - Enter BIOS/UEFI settings (commonly by pressing `F2`, `F10`, `Del`, or `Esc` during boot).

2. **Navigate to Secure Boot Settings**:

   - Typically found under the `Security`, `Boot`, or `Authentication` tab.

3. **Disable Secure Boot**:

   - Change the **Secure Boot** option to `Disabled`.
   - Save changes and exit.

4. **Verify Secure Boot Status**:

   ```bash
   sudo mokutil --sb-state
   ```

   _Expected Output_:

   ```
   SecureBoot disabled
   ```

**Notes**:

- Disabling Secure Boot reduces protection against certain types of malware.
- Only disable Secure Boot if necessary for specific operations or troubleshooting.
- Re-enable Secure Boot after resolving issues to maintain system security.

---

## Best Practices

1. **Use Trusted Keys**: Always use secure and trusted keys for signing binaries. Protect private keys with strong passwords and store them securely.

2. **Regularly Update Keys**: Rotate keys periodically and revoke compromised keys promptly.

3. **Sign All Boot Components**: Ensure that all components in the boot chain, including bootloaders, kernels, and modules, are properly signed.

4. **Maintain Backup Keys**: Keep backups of your signing keys in secure locations to prevent lockout in case of key loss.

5. **Automate Signing Processes**: Utilize scripts or automation tools to streamline the signing of binaries, especially after updates.

6. **Monitor Secure Boot Status**: Regularly check the status of Secure Boot to ensure it remains enabled and properly configured.

7. **Educate Users**: Inform users and administrators about the importance of Secure Boot and proper key management practices.

---

## Additional Resources

- **UEFI Secure Boot Specification**: [UEFI Forum](https://uefi.org/specifications)
- **Microsoft Secure Boot Documentation**: [Microsoft Docs](https://docs.microsoft.com/en-us/windows-hardware/design/device-experiences/oem-secure-boot)
- **`sbsigntool` GitHub Repository**: [sbsigntool](https://github.com/rhboot/sbsigntool)
- **`mokutil` Documentation**: [mokutil GitHub](https://github.com/rhboot/shim)
- **Linux Foundation's Secure Boot Guide**: [Linux Foundation](https://wiki.linuxfoundation.org/secureboot)
- **Arch Linux Wiki - Secure Boot**: [Arch Wiki](https://wiki.archlinux.org/title/Secure_Boot)
- **Ubuntu Community Help - Secure Boot**: [Ubuntu Community](https://help.ubuntu.com/community/UEFI/SecureBoot)
- **Fedora Documentation - Secure Boot**: [Fedora Docs](https://docs.fedoraproject.org/en-US/fedora/f35/system-administrators-guide/secure-boot/)
- **openSUSE Secure Boot Guide**: [openSUSE Wiki](https://en.opensuse.org/SDB:Secure_Boot)

---

This **Secure Boot in Linux** guide aims to provide a thorough understanding of Secure Boot technology, its implementation, and practical demonstrations to enhance your system's security. By following the steps outlined in the demonstrations, you can effectively manage Secure Boot on your Linux systems, ensuring a trusted and secure boot process.

For further assistance, refer to the additional resources provided or consult the official documentation of your Linux distribution.

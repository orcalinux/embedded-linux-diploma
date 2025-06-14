# Resolving "Operation not permitted" Errors in Yocto/BitBake Builds

This guide explains the "Operation not permitted" error that may occur during Yocto builds with BitBake and provides two main approaches to resolve the issue:

-   **Option A:** Disable the network sandbox (the simplest workaround)
-   **Option B:** Enable unprivileged user namespaces (for full sandbox functionality)

---

## Table of Contents

- [Resolving "Operation not permitted" Errors in Yocto/BitBake Builds](#resolving-operation-not-permitted-errors-in-yoctobitbake-builds)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [The Problem](#the-problem)
  - [Understanding the Error](#understanding-the-error)
  - [Solution Options](#solution-options)
    - [Option A: Disable the Network Sandbox](#option-a-disable-the-network-sandbox)
    - [Option B: Enable Unprivileged User Namespaces](#option-b-enable-unprivileged-user-namespaces)
      - [Step 1: Verify Kernel Support](#step-1-verify-kernel-support)
      - [Step 2: Enable Unprivileged User Namespaces at Runtime](#step-2-enable-unprivileged-user-namespaces-at-runtime)
      - [Step 3: Disable AppArmor Restrictions](#step-3-disable-apparmor-restrictions)
      - [Step 4: Re-run the Build](#step-4-re-run-the-build)
  - [Summary and Troubleshooting](#summary-and-troubleshooting)
  - [Additional Notes](#additional-notes)
    - [Conclusion](#conclusion)

---

## Overview

When running a Yocto build (for example, using `bitbake core-image-minimal`), BitBake attempts to disable network access for some tasks by leveraging unprivileged user namespaces. On some Ubuntu systems, security restrictions (especially from AppArmor) may block this operation, causing errors such as:

```
ERROR: PermissionError: [Errno 1] Operation not permitted
```

This README explains why this happens and how to fix it.

---

## The Problem

During the build, you may see error messages like:

```
ERROR: PermissionError: [Errno 1] Operation not permitted
...
with open("/proc/self/uid_map", "w") as f:
PermissionError: [Errno 1] Operation not permitted
```

This indicates BitBake cannot write to `/proc/self/uid_map` because creating an unprivileged user namespace is being blocked by your system’s security policies.

---

## Understanding the Error

-   **User Namespaces:**  
    BitBake uses unprivileged user namespaces to sandbox network access during tasks. This requires writing to `/proc/self/uid_map` and `/proc/self/gid_map`.

-   **Kernel Requirements:**  
    Your kernel must have `CONFIG_USER_NS=y` and the runtime setting `kernel.unprivileged_userns_clone=1` must be enabled.

-   **Security Modules:**  
    Even if the kernel supports user namespaces, security frameworks like **AppArmor** may restrict their use. For example, if `kernel.apparmor_restrict_unprivileged_userns` is set to `1`, it will block unprivileged namespace creation.

---

## Solution Options

### Option A: Disable the Network Sandbox

If you do not require the sandboxing feature (i.e., if you’re running a personal build), you can disable it:

1. **Edit your build configuration:**  
   Open the `local.conf` file (typically found at `build-qemux86-64/conf/local.conf`) and add the following line:

    ```bash
    BB_ENABLE_NETWORK_SANDBOX = "0"
    ```

    _(For older Yocto versions, you might use `BB_NO_NETWORK_SANDBOX = "1"`.)_

2. **Save the file and re-run the build:**
    ```bash
    bitbake core-image-minimal
    ```

This bypasses the user-namespace setup, preventing the “Operation not permitted” error.

---

### Option B: Enable Unprivileged User Namespaces

If you want to use the full sandbox functionality, follow these steps:

#### Step 1: Verify Kernel Support

Ensure your kernel supports user namespaces:

```bash
grep CONFIG_USER_NS /boot/config-$(uname -r)
```

You should see:

```
CONFIG_USER_NS=y
```

If not, you may need to update or rebuild your kernel.

#### Step 2: Enable Unprivileged User Namespaces at Runtime

1. **Set the runtime parameter:**
    ```bash
    sudo sysctl -w kernel.unprivileged_userns_clone=1
    ```
2. **Persist the setting:**  
   Create a sysctl configuration file:
    ```bash
    echo "kernel.unprivileged_userns_clone=1" | sudo tee /etc/sysctl.d/99-userns.conf
    sudo sysctl --system
    ```

#### Step 3: Disable AppArmor Restrictions

AppArmor may still prevent namespace creation. Check its status:

```bash
sysctl kernel.apparmor_restrict_unprivileged_userns
```

If it returns `1`, disable it:

1. **Temporarily disable:**
    ```bash
    sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
    ```
2. **Persist the change:**
    ```bash
    echo "kernel.apparmor_restrict_unprivileged_userns=0" | sudo tee /etc/sysctl.d/99-apparmor-allow-userns.conf
    sudo sysctl --system
    ```

#### Step 4: Re-run the Build

Now that user namespaces are enabled and AppArmor is not restricting them, re-run your build:

```bash
bitbake core-image-minimal
```

The BitBake sandbox should now operate correctly without errors.

---

## Summary and Troubleshooting

-   **Quick Fix:** If you encounter "Operation not permitted" errors, the easiest solution is to disable the network sandbox by setting `BB_ENABLE_NETWORK_SANDBOX = "0"` in your `local.conf`.
-   **Full Sandbox Support:** To use the sandbox:
    -   Ensure your kernel supports user namespaces (`CONFIG_USER_NS=y`).
    -   Enable unprivileged namespaces (`kernel.unprivileged_userns_clone=1`).
    -   Disable AppArmor’s restriction (`kernel.apparmor_restrict_unprivileged_userns=0`).
-   **Additional Checks:**  
    If issues persist:
    -   Confirm you are not building inside a container (like Docker) that might have additional restrictions.
    -   Verify that your filesystem is Linux-native (e.g., ext4) to avoid permission complications.

---

## Additional Notes

-   **Host Distribution Warning:**  
    You might see a warning that your host distribution (e.g., Ubuntu 24.04) is not officially validated. This is informational and usually does not cause the build to fail.
-   **Security Considerations:**  
    Disabling AppArmor restrictions may reduce your system’s security. Use this method only on trusted, personal systems.
-   **Container Environments:**  
    If building inside a container, further configuration may be required to allow unprivileged user namespaces.

---

### Conclusion

By following these instructions, you can resolve the "Operation not permitted" error encountered during Yocto builds. Choose between disabling the network sandbox for a quick workaround or enabling unprivileged user namespaces (and adjusting AppArmor settings) for full sandbox functionality.

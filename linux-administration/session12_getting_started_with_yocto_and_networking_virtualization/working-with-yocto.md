# **Session 03: Advanced Yocto Usage**

## **Overview**

This guide provides a comprehensive workflow for setting up **Yocto**, building images, customizing layers, running QEMU, and configuring networked virtual machines with static IP addresses.

**Yocto** is a powerful build system for creating highly customized, embedded Linux distributions. With it, you can control every aspect of your Linux image—from the kernel to package management, networking, and more.

---

## **Table of Contents**

- [**Session 03: Advanced Yocto Usage**](#session-03-advanced-yocto-usage)
  - [**Overview**](#overview)
  - [**Table of Contents**](#table-of-contents)
  - [1. **Install Prerequisites**](#1-install-prerequisites)
  - [2. **Downloading and Setting Up Yocto**](#2-downloading-and-setting-up-yocto)
  - [3. **Building an Image**](#3-building-an-image)
  - [4. **Advanced Configuration and Layers**](#4-advanced-configuration-and-layers)
    - [4.1 **Add Additional Layers**](#41-add-additional-layers)
    - [4.2 **Advanced Local.conf Options**](#42-advanced-localconf-options)
  - [5. **Post-Build Steps and Optimizations**](#5-post-build-steps-and-optimizations)
  - [6. **QEMU Monitor and Advanced Usage**](#6-qemu-monitor-and-advanced-usage)
  - [7. **Saving the Kernel and Root Filesystem**](#7-saving-the-kernel-and-root-filesystem)
  - [8. **Networking Two Yocto VMs**](#8-networking-two-yocto-vms)
    - [**`start_vms.sh`**](#start_vmssh)
  - [9. **Machine Configurations for Static IPs**](#9-machine-configurations-for-static-ips)
    - [**Machine 1: `node-alpha`**](#machine-1-node-alpha)
    - [**Machine 2: `node-beta`**](#machine-2-node-beta)
  - [10. **Troubleshooting and Tips**](#10-troubleshooting-and-tips)
  - [11. **Resources**](#11-resources)

---

## 1. **Install Prerequisites**

Install the required packages (Ubuntu/Debian example):

```bash
sudo apt-get update
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat libsdl1.2-dev xterm lz4 \
    libpulse-dev libvirt-daemon-system qemu-kvm virt-manager
```

For official guidance, see the [Yocto Project Quick Start Guide](https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html).

---

## 2. **Downloading and Setting Up Yocto**

1. **Clone the Poky Repository**  
   Choose the correct branch (e.g., `kirkstone`, `dunfell`, etc.):

    ```bash
    git clone -b <release-name> git://git.yoctoproject.org/poky
    ```

2. **Set Up the Build Environment**
    ```bash
    cd poky
    source oe-init-build-env ../build-qemux86-64
    ```
    This creates a `build-qemux86-64` directory with default configurations in `conf/`.

---

## 3. **Building an Image**

1. **Configure `local.conf`**
    ```bash
    MACHINE ??= "qemux86-64"
    DL_DIR ?= "${TOPDIR}/../downloads"
    ```
2. **Build the Image**
    ```bash
    bitbake core-image-minimal
    ```
3. **Check Artifacts**  
   Built images appear in `tmp/deploy/images/<machine>/`. For example, you might see:
    - `bzImage-<machine>.bin`
    - `core-image-minimal-<machine>.rootfs.ext4`

---

## 4. **Advanced Configuration and Layers**

### 4.1 **Add Additional Layers**

1. **Clone Additional Repos**
    ```bash
    git clone https://github.com/akuster/meta-odroid
    ```
2. **Update `bblayers.conf`**
    ```bash
    BBLAYERS ?= " \
      /home/$USER/yocto/<release-name>/poky/meta \
      /home/$USER/yocto/<release-name>/poky/meta-poky \
      /home/$USER/yocto/<release-name>/poky/meta-yocto-bsp \
      /home/$USER/yocto/<release-name>/meta-odroid \
    "
    ```

### 4.2 **Advanced Local.conf Options**

-   `BB_NUMBER_THREADS` / `PARALLEL_MAKE`: Set concurrency to speed builds.
-   `EXTRA_IMAGE_FEATURES`: Add `debug-tweaks`, `tools-debug`, etc.

---

## 5. **Post-Build Steps and Optimizations**

1. **Check Build Results**

    - `tmp/deploy/licenses/` for licenses
    - `tmp/deploy/sdk/` if building SDK packages

2. **Cleanup**

    - `bitbake -c clean <recipe>` removes build artifacts for one recipe.
    - `rm_work` class can remove work dirs to save space.

3. **Sstate Caching**
    - `SSTATE_DIR` can be set for reusing artifacts in CI or repeated builds.

---

## 6. **QEMU Monitor and Advanced Usage**

-   **Graphical Mode**:
    ```bash
    runqemu core-image-minimal-qemux86-64
    ```
-   **Headless (`nographic`)**:
    ```bash
    runqemu core-image-minimal-qemux86-64 nographic
    ```
-   **KVM Acceleration**:

    ```bash
    runqemu qemux86-64 kvm nographic
    ```

    (Requires host CPU virtualization.)

-   **QEMU Monitor**: Press `Ctrl + Alt + 2`; commands include `stop`, `cont`, `quit`.

---

## 7. **Saving the Kernel and Root Filesystem**

1. **Create a Backup Directory**
    ```bash
    mkdir -p ~/yocto/<release-name>/saved-images
    ```
2. **Copy the Files**
    ```bash
    cp -L tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.rootfs.ext4 \
       ~/yocto/<release-name>/saved-images
    cp -L tmp/deploy/images/qemux86-64/bzImage-qemux86-64.bin \
       ~/yocto/<release-name>/saved-images
    ```
3. **Run the Saved Image**
    ```bash
    runqemu \
      ~/yocto/<release-name>/saved-images/core-image-minimal-qemux86-64.rootfs.ext4 \
      ~/yocto/<release-name>/saved-images/bzImage-qemux86-64.bin \
      nographic
    ```

---

## 8. **Networking Two Yocto VMs**

The following script creates a Linux **bridge** (`br1`) and two TAP interfaces. Then it launches two separate QEMU VMs, each with a **static IP** on the same subnet.

### **`start_vms.sh`**

```bash
#!/bin/bash

# -----------------------------
# Configuration
# -----------------------------
BRIDGE_NAME="br1"

# TAP devices for each VM
TAP1="vport11"
TAP2="vport12"

# Machine 1 (node-alpha)
VM1_KERNEL="/home/$USER/yocto/saved-images/bzImage-machine1.bin"
VM1_ROOTFS="/home/$USER/yocto/saved-images/rootfs-machine1.ext4"
VM1_MAC="12:34:56:AB:CD:7B"
VM1_IP="192.168.10.2"
VM1_NAME="node-alpha"

# Machine 2 (node-beta)
VM2_KERNEL="/home/$USER/yocto/saved-images/bzImage-machine2.bin"
VM2_ROOTFS="/home/$USER/yocto/saved-images/rootfs-machine2.ext4"
VM2_MAC="12:34:56:AB:CD:7C"
VM2_IP="192.168.10.3"
VM2_NAME="node-beta"

# -----------------------------
# 1) Create and Set Up the Bridge
# -----------------------------
echo "[+] Creating bridge: $BRIDGE_NAME"
sudo ip link add name $BRIDGE_NAME type bridge
sudo ip link set $BRIDGE_NAME up

# -----------------------------
# 2) Create and Attach TAP Devices
# -----------------------------
for TAP in $TAP1 $TAP2; do
    echo "[+] Creating tap device: $TAP"
    sudo ip tuntap add mode tap $TAP
    sudo ip link set $TAP up
    sudo ip link set $TAP master $BRIDGE_NAME
done

# -----------------------------
# 3) Launch VM 1
# -----------------------------
echo "[+] Launching $VM1_NAME with IP: $VM1_IP"
sudo qemu-system-x86_64 \
    -kernel "$VM1_KERNEL" \
    -m 1G \
    -drive "file=$VM1_ROOTFS,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net1,mac=$VM1_MAC \
    -netdev tap,id=net1,ifname=$TAP1,script=no,downscript=no \
    -name "$VM1_NAME" \
    -daemonize \
    --append "root=/dev/vda rw ip=$VM1_IP::192.168.10.1:255.255.255.0::eth0:off"

# -----------------------------
# 4) Launch VM 2
# -----------------------------
echo "[+] Launching $VM2_NAME with IP: $VM2_IP"
sudo qemu-system-x86_64 \
    -kernel "$VM2_KERNEL" \
    -m 1G \
    -drive "file=$VM2_ROOTFS,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net2,mac=$VM2_MAC \
    -netdev tap,id=net2,ifname=$TAP2,script=no,downscript=no \
    -name "$VM2_NAME" \
    -daemonize \
    --append "root=/dev/vda rw ip=$VM2_IP::192.168.10.1:255.255.255.0::eth0:off"

echo "[+] Machines launched successfully."
echo "    $VM1_NAME (IP: $VM1_IP) and $VM2_NAME (IP: $VM2_IP)."
echo "    Bridge: $BRIDGE_NAME, TAPs: $TAP1, $TAP2."
```

---

## 9. **Machine Configurations for Static IPs**

Edit `/etc/network/interfaces` (or your distro’s equivalent) **inside each VM** to set up a **static IP**. Here’s an example of two machines on the `10.20.10.x` subnet, each using `10.20.10.1` as the default gateway.

### **Machine 1: `node-alpha`**

```ini
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.2
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.10.1 dev eth0
```

### **Machine 2: `node-beta`**

```ini
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.1
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.10.1 dev eth0
```

> **Note**: In these examples, both machines share the same subnet (`10.20.10.x`) **and** the same default gateway (`10.20.10.1`). Ensure the addresses you choose do not overlap with your host’s local network or any other DHCP range. Adjust if you have a different topology in mind.

---

## 10. **Troubleshooting and Tips**

1. **QEMU Permission Errors**

    - Ensure `.ext4` images are writable by your user if you’re not using snapshot mode.
    - If you see “Operation Not Permitted” while creating user namespaces, either disable BitBake’s network sandbox or enable user namespace support on your host (`kernel.unprivileged_userns_clone=1`).

2. **Network Conflicts**

    - If bridging to a physical network, watch out for IP overlap.
    - If using NAT or user-mode networking, configure QEMU’s `-net user` settings or use the `runqemu` built-in NAT.

3. **Performance**

    - **KVM** acceleration can be a big boost if your CPU supports it (Intel VT or AMD-V).
    - Increase VM memory (`-m 2G`) if you have enough host RAM.

4. **Debugging**
    - `bitbake -c devshell <recipe>` enters a dev shell for that recipe.
    - Check `tmp/work/.../temp/log.do_*.log` for build logs.

---

## 11. **Resources**

-   [**Yocto Project Documentation**](https://docs.yoctoproject.org/index.html)
-   [**Yocto Project Releases**](https://wiki.yoctoproject.org/wiki/Releases)
-   [**Yocto Project Overview Video**](https://youtu.be/8M8U1EgnUVw?si=1cH194i2Bgcd8TZJ)
-   [**OpenEmbedded**](https://www.openembedded.org/)
-   [**RedHat Virtio-networking series**](https://www.redhat.com/en/virtio-networking-series)

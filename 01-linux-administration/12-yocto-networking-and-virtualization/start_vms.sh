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

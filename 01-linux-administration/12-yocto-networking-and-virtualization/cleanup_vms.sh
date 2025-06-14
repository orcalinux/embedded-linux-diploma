#!/bin/bash

# Detach the tap device vport11 from its bridge
sudo ip link set dev vport11 nomaster
# Delete the tap device vport11
sudo ip tuntap del mode tap vport11

# Detach the tap device vport12 from its bridge
sudo ip link set dev vport12 nomaster
# Delete the tap device vport12
sudo ip tuntap del mode tap vport12

# Delete the bridge device br1
sudo ip link delete dev br1

echo "[+] Cleanup complete. The bridge and TAP devices have been removed."

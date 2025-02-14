# Comprehensive Guide to Network Management in Linux

## Table of Contents

1. [Introduction](#introduction)
2. [Understanding Network Interfaces](#understanding-network-interfaces)
   - [Types of Network Interfaces](#types-of-network-interfaces)
   - [Interface Naming Conventions](#interface-naming-conventions)
   - [Viewing Network Interfaces](#viewing-network-interfaces)
3. [Network Configuration Tools](#network-configuration-tools)
   - [ifconfig and Net-Tools](#ifconfig-and-net-tools)
   - [iproute2 (`ip` command)](#iproute2-ip-command)
   - [NetworkManager (`nmcli` & `nmtui`)](#networkmanager-nmcli--nmtui)
   - [systemd-networkd](#systemd-networkd)
   - [wpa_supplicant](#wpa_supplicant)
   - [Other Network Management Tools](#other-network-management-tools)
4. [Configuration Files](#configuration-files)
   - [/etc/network/interfaces](#etcnetworkinterfaces)
   - [/etc/NetworkManager/](#etcnetworkmanager)
   - [/etc/systemd/network/](#etcsystemdnetwork)
   - [/etc/wpa_supplicant/](#etcwpasupplicant)
   - [/etc/resolv.conf](#etcresolvconf)
   - [/etc/hosts](#etchosts)
5. [Managing Network Interfaces](#managing-network-interfaces)
   - [Bringing Interfaces Up and Down](#bringing-interfaces-up-and-down)
   - [Assigning IP Addresses](#assigning-ip-addresses)
     - [Static IP Configuration](#static-ip-configuration)
     - [DHCP Configuration](#dhcp-configuration)
   - [Virtual Interfaces](#virtual-interfaces)
     - [VLANs](#vlans)
     - [Bridging](#bridging)
     - [Bonding (Link Aggregation)](#bonding-link-aggregation)
   - [Routing Tables](#routing-tables)
   - [DNS Configuration](#dns-configuration)
6. [Wireless Networking](#wireless-networking)
   - [Understanding Wireless Concepts](#understanding-wireless-concepts)
   - [Scanning for Wi-Fi Networks](#scanning-for-wi-fi-networks)
   - [Connecting to Wi-Fi Networks](#connecting-to-wi-fi-networks)
   - [Security Protocols](#security-protocols)
   - [Managing Wi-Fi with `wpa_supplicant`](#managing-wi-fi-with-wpasupplicant)
   - [Managing Wi-Fi with NetworkManager (`nmcli` & `nmtui`)](#managing-wi-fi-with-networkmanager-nmcli--nmtui)
7. [Advanced Network Configurations](#advanced-network-configurations)
   - [Virtual Private Networks (VPN)](#virtual-private-networks-vpn)
   - [IPv6 Configuration](#ipv6-configuration)
   - [Quality of Service (QoS)](#quality-of-service-qos)
   - [Firewall Integration](#firewall-integration)
8. [Scripting and Automation](#scripting-and-automation)
   - [Network Scripts](#network-scripts)
   - [Using `cron` for Scheduled Tasks](#using-cron-for-scheduled-tasks)
   - [Systemd Services for Network Tasks](#systemd-services-for-network-tasks)
9. [Command-Line Tools for Networking and Firewall Management](#command-line-tools-for-networking-and-firewall-management)
   - [iptables](#iptables)
   - [nftables](#nftables)
   - [ufw (Uncomplicated Firewall)](#ufw-uncomplicated-firewall)
   - [firewalld](#firewalld)
   - [Other Networking Tools](#other-networking-tools)
10. [Troubleshooting](#troubleshooting)
    - [Diagnosing Connectivity Issues](#diagnosing-connectivity-issues)
    - [Analyzing Logs](#analyzing-logs)
    - [Common Network Issues and Solutions](#common-network-issues-and-solutions)
    - [Useful Diagnostic Tools](#useful-diagnostic-tools)
11. [Practical Examples](#practical-examples)
    - [Example 1: Configuring a Static IP Address](#example-1-configuring-a-static-ip-address)
    - [Example 2: Setting Up DHCP](#example-2-setting-up-dhcp)
    - [Example 3: Connecting to a Wi-Fi Network](#example-3-connecting-to-a-wi-fi-network)
    - [Example 4: Creating a Wi-Fi Hotspot](#example-4-creating-a-wi-fi-hotspot)
    - [Example 5: Configuring Network Bonding](#example-5-configuring-network-bonding)
    - [Example 6: Setting Up a Network Bridge](#example-6-setting-up-a-network-bridge)
    - [Example 7: Setting Up a VPN Connection](#example-7-setting-up-a-vpn-connection)
12. [Demos](#demos)
    - [Demo 1: Configuring a Static IP](#demo-1-configuring-a-static-ip)
    - [Demo 2: Connecting to a Wi-Fi Network](#demo-2-connecting-to-a-wi-fi-network)
    - [Demo 3: Creating a Wi-Fi Hotspot](#demo-3-creating-a-wi-fi-hotspot)
    - [Demo 4: Configuring Network Bonding](#demo-4-configuring-network-bonding)
    - [Demo 5: Setting Up a VPN Connection](#demo-5-setting-up-a-vpn-connection)
13. [Best Practices](#best-practices)
    - [Security Considerations](#security-considerations)
    - [Managing Multiple Network Connections](#managing-multiple-network-connections)
    - [Performance Optimizations](#performance-optimizations)
    - [Documentation and Change Management](#documentation-and-change-management)
14. [Conclusion](#conclusion)
15. [Further Resources](#further-resources)

---

## Introduction

Network management in Linux is a critical aspect of system administration, encompassing the configuration, maintenance, and troubleshooting of network interfaces and services. Whether you're managing a personal desktop, a server, or a complex network of devices, understanding Linux network management equips you with the tools to ensure reliable and secure connectivity.

This guide delves deep into the intricacies of Linux network management, providing in-depth explanations, practical examples, and demonstrations to empower instructors and learners alike.

---

## Understanding Network Interfaces

### Types of Network Interfaces

1. **Ethernet Interfaces:**

   - **Description:** Physical network interfaces used for wired connections.
   - **Common Names:** `eth0`, `enp3s0`, `eno1`, etc.
   - **Use Cases:** Desktop PCs, servers, network switches.

2. **Wireless Interfaces:**

   - **Description:** Interfaces for wireless networking (Wi-Fi).
   - **Common Names:** `wlan0`, `wlp3s0`, `wlo1`, etc.
   - **Use Cases:** Laptops, mobile devices, wireless access points.

3. **Loopback Interface:**

   - **Description:** Virtual interface used for internal communication within the host.
   - **Name:** `lo`
   - **Use Cases:** Testing, inter-process communication.

4. **Virtual Interfaces:**

   - **Description:** Software-based interfaces used for various purposes.
   - **Types:**
     - **Bridges:** `br0`, used to connect multiple interfaces.
     - **Bonds:** `bond0`, for link aggregation.
     - **VLANs:** `eth0.10`, for virtual LANs.
     - **Tunnels:** `tun0`, used in VPNs.

5. **Tunnel Interfaces:**
   - **Description:** Interfaces that encapsulate network packets within another protocol.
   - **Common Names:** `tun0`, `tap0`
   - **Use Cases:** VPNs, network virtualization.

### Interface Naming Conventions

Linux has transitioned from traditional interface naming (e.g., `eth0`, `wlan0`) to predictable naming schemes to avoid inconsistencies across reboots and hardware changes. Predictable naming is based on firmware, topology, and other factors.

**Examples:**

- `enp3s0`:
  - `en` — Ethernet
  - `p3` — PCI bus 3
  - `s0` — Slot 0
- `wlp2s0`:
  - `wl` — Wireless LAN
  - `p2` — PCI bus 2
  - `s0` — Slot 0

**Advantages:**

- Predictable and consistent across reboots.
- Avoids confusion in systems with multiple network interfaces.

**Disabling Predictable Naming:**
For systems requiring traditional naming, you can disable predictable naming by adding kernel parameters or creating symlinks. However, this approach is generally not recommended for modern systems.

### Viewing Network Interfaces

1. **Using `ip` Command:**

   ```bash
   ip link show
   ```

   - **Output Explanation:**
     - Lists all network interfaces with their status (UP/DOWN), MAC addresses, etc.

2. **Using `ifconfig` (Deprecated):**

   ```bash
   ifconfig -a
   ```

   - **Note:** `ifconfig` is part of the `net-tools` package and is deprecated in favor of `iproute2`.

3. **Using `ls /sys/class/net`:**

   ```bash
   ls /sys/class/net
   ```

   - **Output:** Lists the names of all network interfaces.

4. **Using `lshw`:**

   ```bash
   sudo lshw -C network
   ```

   - **Output:** Detailed hardware information about network interfaces.

5. **Using `nmcli`:**
   ```bash
   nmcli device status
   ```
   - **Output:** Status of all network devices managed by NetworkManager.

---

## Network Configuration Tools

Linux provides a variety of tools for network configuration and management, each with its own strengths and use cases.

### ifconfig and Net-Tools

**Overview:**

- `ifconfig` is part of the older `net-tools` package.
- Historically used for configuring network interfaces.
- Deprecated in favor of `iproute2` (`ip` command).

**Common Commands:**

1. **View All Interfaces:**

   ```bash
   ifconfig -a
   ```

   - **Explanation:** Lists all network interfaces, including those that are down.

2. **Bring an Interface Up:**

   ```bash
   sudo ifconfig eth0 up
   ```

   - **Explanation:** Activates the `eth0` interface.

3. **Bring an Interface Down:**

   ```bash
   sudo ifconfig eth0 down
   ```

   - **Explanation:** Deactivates the `eth0` interface.

4. **Assign an IP Address:**

   ```bash
   sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0
   ```

   - **Explanation:** Assigns the IP address `192.168.1.100` with the specified netmask to `eth0`.

5. **Set a Broadcast Address:**
   ```bash
   sudo ifconfig eth0 broadcast 192.168.1.255
   ```
   - **Explanation:** Sets the broadcast address for `eth0`.

**Limitations:**

- Lacks advanced features present in `iproute2`.
- Does not handle modern networking concepts like namespaces, tunnels, etc.

### iproute2 (`ip` command)

**Overview:**

- Modern and versatile tool for network management.
- Replaces many functionalities of `ifconfig`, `route`, and other older tools.

**Common Commands:**

1. **View All Interfaces:**

   ```bash
   ip link show
   ```

   - **Explanation:** Lists all network interfaces with detailed information.

2. **Bring an Interface Up:**

   ```bash
   sudo ip link set eth0 up
   ```

   - **Explanation:** Activates the `eth0` interface.

3. **Bring an Interface Down:**

   ```bash
   sudo ip link set eth0 down
   ```

   - **Explanation:** Deactivates the `eth0` interface.

4. **Assign an IP Address:**

   ```bash
   sudo ip addr add 192.168.1.100/24 dev eth0
   ```

   - **Explanation:** Assigns the IP address `192.168.1.100` with a `/24` subnet mask to `eth0`.

5. **Delete an IP Address:**

   ```bash
   sudo ip addr del 192.168.1.100/24 dev eth0
   ```

   - **Explanation:** Removes the specified IP address from `eth0`.

6. **View Routing Table:**

   ```bash
   ip route show
   ```

   - **Explanation:** Displays the system's routing table.

7. **Add a Route:**

   ```bash
   sudo ip route add default via 192.168.1.1
   ```

   - **Explanation:** Adds a default gateway via `192.168.1.1`.

8. **Delete a Route:**

   ```bash
   sudo ip route del default via 192.168.1.1
   ```

   - **Explanation:** Removes the specified default gateway.

9. **Show IP Addresses:**

   ```bash
   ip addr show
   ```

   - **Explanation:** Displays all IP addresses assigned to interfaces.

10. **Show Detailed Interface Information:**
    ```bash
    ip -s link
    ```
    - **Explanation:** Shows statistics and detailed information for all interfaces.

**Advantages:**

- Supports advanced networking features.
- More granular control over network configurations.
- Actively maintained and updated.

### NetworkManager (`nmcli` & `nmtui`)

**Overview:**

- **NetworkManager** is a daemon for simplifying network configuration and management.
- **`nmcli`:** Command-line interface for NetworkManager.
- **`nmtui`:** Text-based user interface for NetworkManager.

**Features:**

- Manages wired, wireless, VPN, and mobile broadband connections.
- Provides easy switching between networks.
- Integrates with desktop environments for GUI management.

**Common `nmcli` Commands:**

1. **Check Device Status:**

   ```bash
   nmcli device status
   ```

   - **Explanation:** Lists all network devices and their current status.

2. **List All Connections:**

   ```bash
   nmcli connection show
   ```

   - **Explanation:** Displays all saved network connections.

3. **Add a New Connection:**

   ```bash
   nmcli connection add type ethernet ifname eth0 con-name my-eth0
   ```

   - **Explanation:** Creates a new Ethernet connection named `my-eth0` on `eth0`.

4. **Modify a Connection:**

   ```bash
   nmcli connection modify my-eth0 ipv4.addresses "192.168.1.100/24"
   nmcli connection modify my-eth0 ipv4.gateway "192.168.1.1"
   nmcli connection modify my-eth0 ipv4.dns "8.8.8.8 8.8.4.4"
   nmcli connection modify my-eth0 ipv4.method manual
   ```

   - **Explanation:** Configures static IP settings for `my-eth0`.

5. **Bring a Connection Up:**

   ```bash
   nmcli connection up my-eth0
   ```

   - **Explanation:** Activates the `my-eth0` connection.

6. **Bring a Connection Down:**

   ```bash
   nmcli connection down my-eth0
   ```

   - **Explanation:** Deactivates the `my-eth0` connection.

7. **Delete a Connection:**

   ```bash
   nmcli connection delete my-eth0
   ```

   - **Explanation:** Removes the `my-eth0` connection.

8. **Show Detailed Connection Information:**
   ```bash
   nmcli connection show my-eth0
   ```
   - **Explanation:** Displays detailed settings for `my-eth0`.

**Using `nmtui`:**

- **Launch the Text-Based UI:**

  ```bash
  sudo nmtui
  ```

  - **Explanation:** Opens a user-friendly text interface for managing network connections.

- **Options in `nmtui`:**
  - **Edit a Connection:** Modify existing network connections.
  - **Activate a Connection:** Enable or disable network connections.
  - **Set Hostname:** Configure the system's hostname.

**Advantages:**

- Simplifies network management for both desktops and servers.
- Supports scripting and automation through `nmcli`.
- Handles a wide range of network configurations seamlessly.

### systemd-networkd

**Overview:**

- **systemd-networkd** is a system service that manages networks.
- Integrated with `systemd`, providing lightweight and efficient network management.
- Ideal for servers and embedded systems.

**Features:**

- Supports DHCP, static IP, VLANs, bridges, bonds, and tunnels.
- Works alongside other `systemd` services.
- Minimal overhead compared to NetworkManager.

**Common Commands:**

1. **Enable and Start systemd-networkd:**

   ```bash
   sudo systemctl enable systemd-networkd
   sudo systemctl start systemd-networkd
   ```

   - **Explanation:** Activates and starts the `systemd-networkd` service.

2. **Enable and Start systemd-resolved:**

   ```bash
   sudo systemctl enable systemd-resolved
   sudo systemctl start systemd-resolved
   ```

   - **Explanation:** Activates and starts the `systemd-resolved` service for DNS resolution.

3. **Check Status:**

   ```bash
   sudo systemctl status systemd-networkd
   sudo systemctl status systemd-resolved
   ```

   - **Explanation:** Displays the current status of the services.

4. **Restart Services:**
   ```bash
   sudo systemctl restart systemd-networkd
   sudo systemctl restart systemd-resolved
   ```
   - **Explanation:** Restarts the respective services to apply changes.

**Configuration Files:**

- Located in `/etc/systemd/network/`.
- Files typically have a `.network` extension.

**Example: Static IP Configuration (`/etc/systemd/network/20-wired.network`):**

```ini
[Match]
Name=enp3s0

[Network]
Address=192.168.1.100/24
Gateway=192.168.1.1
DNS=8.8.8.8 8.8.4.4
```

**Advantages:**

- Tight integration with `systemd`.
- Suitable for headless servers and systems requiring minimal resources.
- Clear and declarative configuration files.

### wpa_supplicant

**Overview:**

- **wpa_supplicant** is a daemon for managing wireless networks.
- Handles authentication and association with wireless networks.
- Supports WPA, WPA2, WPA3, and other security protocols.

**Common Commands:**

1. **Scan for Wi-Fi Networks:**

   ```bash
   sudo wpa_cli scan
   sudo wpa_cli scan_results
   ```

   - **Explanation:** Initiates a Wi-Fi scan and displays available networks.

2. **Connect to a Wi-Fi Network:**
   ```bash
   sudo wpa_passphrase "SSID_Name" "password" | sudo tee /etc/wpa_supplicant.conf
   sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
   sudo dhclient wlan0
   ```
   - **Explanation:** Creates a configuration for the specified network, starts `wpa_supplicant`, and obtains an IP address via DHCP.

**Configuration File (`/etc/wpa_supplicant/wpa_supplicant.conf`):**

```ini
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US

network={
    ssid="SSID_Name"
    psk="password"
}
```

**Advantages:**

- Fine-grained control over wireless connections.
- Essential for systems without NetworkManager or systemd-networkd.
- Highly configurable for various wireless scenarios.

### Other Network Management Tools

1. **ConnMan (Connection Manager):**

   - **Description:** Lightweight network manager for embedded devices.
   - **Features:** Provides command-line and DBus interfaces for managing network connections.

2. **Wicd (Wireless Interface Connection Daemon):**

   - **Description:** Alternative to NetworkManager for managing wired and wireless networks.
   - **Features:** Offers both GUI and command-line interfaces for network management.

3. **Netplan:**

   - **Description:** YAML-based network configuration abstraction for Ubuntu and other distributions.
   - **Features:** Translates configurations to backend renderers like NetworkManager or systemd-networkd.

   **Example Netplan Configuration (`/etc/netplan/01-netcfg.yaml`):**

   ```yaml
   network:
     version: 2
     renderer: networkd
     ethernets:
       enp3s0:
         dhcp4: yes
   ```

   **Apply Configuration:**

   ```bash
   sudo netplan apply
   ```

**Choosing the Right Tool:**

- **Desktop Systems:** NetworkManager is often preferred due to its seamless integration with desktop environments.
- **Servers:** systemd-networkd or Netplan (with networkd backend) is suitable for lightweight and efficient management.
- **Embedded Systems:** ConnMan or custom scripts may be more appropriate.

---

## Configuration Files

Network configurations in Linux are managed through various configuration files, depending on the network management tool in use. Understanding these files is essential for manual configurations and troubleshooting.

### /etc/network/interfaces

**Used By:** `ifupdown` system.

**Purpose:** Define network interfaces and their configurations.

**Structure:**

```ini
auto <interface>
iface <interface> <method> [options]
```

**Example: Static IP Configuration**

```ini
auto enp3s0
iface enp3s0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
    dns-nameservers 8.8.8.8 8.8.4.4
```

**Example: DHCP Configuration**

```ini
auto enp3s0
iface enp3s0 inet dhcp
```

**Notes:**

- **`auto` Directive:** Specifies that the interface should be automatically brought up at boot.
- **`iface` Directive:** Defines the interface, the address family (`inet` for IPv4, `inet6` for IPv6), and the method (`static`, `dhcp`, etc.).

**Limitations:**

- Lacks support for advanced networking features like VLANs, bonding, etc.
- Not suitable for dynamic environments managed by NetworkManager or systemd-networkd.

### /etc/NetworkManager/

**Used By:** NetworkManager.

**Purpose:** Store NetworkManager configurations and connection profiles.

**Structure:**

- Configuration files are typically located in `/etc/NetworkManager/system-connections/`.
- Files have names corresponding to connection profiles, e.g., `Wired connection 1.nmconnection`.

**Example: Wi-Fi Connection Configuration**

```ini
[connection]
id=Home WiFi
type=wifi
interface-name=wlp2s0
autoconnect=true

[wifi]
ssid=HomeNetwork
mode=infrastructure
mac-address=00:11:22:33:44:55

[wifi-security]
key-mgmt=wpa-psk
psk=your_password

[ipv4]
method=auto
dns=8.8.8.8;8.8.4.4;
dns-search=
never-default=false

[ipv6]
method=ignore
```

**Notes:**

- **Security:** Files may contain sensitive information (e.g., Wi-Fi passwords) and should have appropriate permissions (`600`).
- **Editing:** Can be edited manually or managed via `nmcli` and `nmtui`.

### /etc/systemd/network/

**Used By:** systemd-networkd.

**Purpose:** Define network configurations for systemd-networkd-managed interfaces.

**Structure:**

- Files have a `.network` extension.
- Each file defines configurations for specific interfaces or matching criteria.

**Example: Static IP Configuration (`/etc/systemd/network/20-wired.network`):**

```ini
[Match]
Name=enp3s0

[Network]
Address=192.168.1.100/24
Gateway=192.168.1.1
DNS=8.8.8.8 8.8.4.4
```

**Example: DHCP Configuration (`/etc/systemd/network/10-dhcp.network`):**

```ini
[Match]
Name=enp3s0

[Network]
DHCP=ipv4
```

**Notes:**

- **[Match] Section:** Specifies criteria to match network interfaces (e.g., name, MAC address).
- **[Network] Section:** Defines network settings (IP addresses, gateways, DNS).
- **Additional Sections:** Support for DHCP options, routes, DNS settings, etc.

### /etc/wpa_supplicant/

**Used By:** `wpa_supplicant`.

**Purpose:** Store wireless network configurations and credentials.

**Structure:**

- Primary configuration file: `/etc/wpa_supplicant/wpa_supplicant.conf`.

**Example Configuration:**

```ini
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US

network={
    ssid="HomeNetwork"
    psk="your_password"
    key_mgmt=WPA-PSK
}
```

**Notes:**

- **Security:** Store passwords securely; consider using hashed PSKs.
- **Multiple Networks:** Multiple `network` blocks can be defined for different SSIDs.

### /etc/resolv.conf

**Used By:** DNS resolver.

**Purpose:** Define DNS servers for name resolution.

**Structure:**

```ini
nameserver 8.8.8.8
nameserver 8.8.4.4
search example.com
```

**Notes:**

- **Dynamic Updates:** Managed by NetworkManager, `systemd-resolved`, or other services.
- **Symbolic Links:** Often a symlink to `/run/systemd/resolve/resolv.conf` when using `systemd-resolved`.

**Managing DNS:**

- **With NetworkManager:**

  ```bash
  nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8 8.8.4.4"
  nmcli connection up "Wired connection 1"
  ```

- **With systemd-resolved:**
  ```bash
  sudo systemd-resolve --set-dns=8.8.8.8 --interface=enp3s0
  ```

### /etc/hosts

**Used By:** Local hostname resolution.

**Purpose:** Map hostnames to IP addresses for local resolution.

**Structure:**

```ini
127.0.0.1   localhost
192.168.1.100   myserver.local myserver
```

**Notes:**

- **Order Matters:** Resolutions follow the order defined in `/etc/nsswitch.conf`.
- **Use Cases:** Overriding DNS, local development, internal network naming.

---

## Managing Network Interfaces

Effective network management involves controlling the state of network interfaces, assigning IP addresses, configuring DNS, and setting up advanced networking features.

### Bringing Interfaces Up and Down

**Using `ip` Command:**

- **Bring Up:**
  ```bash
  sudo ip link set enp3s0 up
  ```
- **Bring Down:**
  ```bash
  sudo ip link set enp3s0 down
  ```

**Using `ifconfig` (Deprecated):**

- **Bring Up:**
  ```bash
  sudo ifconfig enp3s0 up
  ```
- **Bring Down:**
  ```bash
  sudo ifconfig enp3s0 down
  ```

**Using NetworkManager (`nmcli`):**

- **Bring Up:**
  ```bash
  nmcli device connect enp3s0
  ```
- **Bring Down:**
  ```bash
  nmcli device disconnect enp3s0
  ```

**Using `systemd-networkd`:**

- Managed via configuration files; interfaces are automatically managed based on `.network` files.

### Assigning IP Addresses

IP addresses can be assigned dynamically via DHCP or statically for consistent network configurations.

#### Static IP Configuration

**Using `ip` Command:**

```bash
sudo ip addr add 192.168.1.100/24 dev enp3s0
sudo ip route add default via 192.168.1.1
```

**Persisting Configuration:**

- **NetworkManager:**

  ```bash
  nmcli connection modify "Wired connection 1" ipv4.method manual
  nmcli connection modify "Wired connection 1" ipv4.addresses "192.168.1.100/24"
  nmcli connection modify "Wired connection 1" ipv4.gateway "192.168.1.1"
  nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8 8.8.4.4"
  nmcli connection up "Wired connection 1"
  ```

- **systemd-networkd (`/etc/systemd/network/20-wired.network`):**

  ```ini
  [Match]
  Name=enp3s0

  [Network]
  Address=192.168.1.100/24
  Gateway=192.168.1.1
  DNS=8.8.8.8 8.8.4.4
  ```

- **Netplan (`/etc/netplan/01-netcfg.yaml`):**
  ```yaml
  network:
    version: 2
    renderer: networkd
    ethernets:
      enp3s0:
        addresses: [192.168.1.100/24]
        gateway4: 192.168.1.1
        nameservers:
          addresses: [8.8.8.8, 8.8.4.4]
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

#### DHCP Configuration

**Using `ip` Command:**

```bash
sudo dhclient enp3s0
```

**Persisting Configuration:**

- **NetworkManager:**

  ```bash
  nmcli connection modify "Wired connection 1" ipv4.method auto
  nmcli connection up "Wired connection 1"
  ```

- **systemd-networkd (`/etc/systemd/network/10-dhcp.network`):**

  ```ini
  [Match]
  Name=enp3s0

  [Network]
  DHCP=ipv4
  ```

- **Netplan (`/etc/netplan/01-netcfg.yaml`):**
  ```yaml
  network:
    version: 2
    renderer: networkd
    ethernets:
      enp3s0:
        dhcp4: true
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

### Virtual Interfaces

Virtual interfaces extend the capabilities of physical network interfaces, enabling functionalities like VLAN tagging, network bridging, and link aggregation.

#### VLANs (Virtual Local Area Networks)

**Purpose:** Segregate network traffic into distinct virtual networks over a single physical interface.

**Creating a VLAN:**

```bash
sudo ip link add link enp3s0 name enp3s0.10 type vlan id 10
sudo ip link set enp3s0.10 up
sudo ip addr add 192.168.10.1/24 dev enp3s0.10
```

**Persisting VLAN Configuration:**

- **systemd-networkd (`/etc/systemd/network/30-vlan.netdev`):**

  ```ini
  [NetDev]
  Name=enp3s0.10
  Kind=vlan

  [VLAN]
  Id=10
  ```

  **Network Configuration (`/etc/systemd/network/30-vlan.network`):**

  ```ini
  [Match]
  Name=enp3s0.10

  [Network]
  Address=192.168.10.1/24
  ```

- **Netplan:**
  ```yaml
  network:
    version: 2
    renderer: networkd
    ethernets:
      enp3s0:
        dhcp4: yes
    vlans:
      enp3s0.10:
        id: 10
        link: enp3s0
        addresses: [192.168.10.1/24]
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

#### Bridging

**Purpose:** Connect multiple network segments at Layer 2, allowing devices to communicate as if they were on the same physical network.

**Creating a Bridge Interface:**

```bash
sudo ip link add name br0 type bridge
sudo ip link set br0 up
sudo ip link set enp3s0 master br0
```

**Assigning IP to Bridge:**

```bash
sudo ip addr add 192.168.1.100/24 dev br0
sudo ip route add default via 192.168.1.1
```

**Persisting Bridge Configuration:**

- **systemd-networkd (`/etc/systemd/network/40-bridge.netdev`):**

  ```ini
  [NetDev]
  Name=br0
  Kind=bridge
  ```

  **Bridge Network Configuration (`/etc/systemd/network/40-bridge.network`):**

  ```ini
  [Match]
  Name=br0

  [Network]
  Address=192.168.1.100/24
  Gateway=192.168.1.1
  DNS=8.8.8.8 8.8.4.4
  ```

  **Slave Interface (`/etc/systemd/network/40-enp3s0.network`):**

  ```ini
  [Match]
  Name=enp3s0

  [Network]
  Bridge=br0
  ```

- **Netplan:**
  ```yaml
  network:
    version: 2
    renderer: networkd
    ethernets:
      enp3s0:
        dhcp4: no
    bridges:
      br0:
        interfaces: [enp3s0]
        addresses: [192.168.1.100/24]
        gateway4: 192.168.1.1
        nameservers:
          addresses: [8.8.8.8, 8.8.4.4]
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

**Notes:**

- **Use Cases:** Virtual machines, container networking.
- **Alternatives:** Use NAT with virtual network interfaces if bridging Wi-Fi is not feasible.

#### Bonding (Link Aggregation)

**Purpose:** Combine multiple network interfaces into a single bonded interface for increased bandwidth and redundancy.

**Installing Bonding Module:**

```bash
sudo modprobe bonding
```

**Creating a Bonded Interface:**

```bash
sudo ip link add bond0 type bond
sudo ip link set bond0 up
sudo ip link set enp3s0 master bond0
sudo ip link set enp3s1 master bond0
```

**Configuring Bonding Mode (e.g., LACP):**

```bash
sudo ip link set bond0 type bond mode 802.3ad miimon 100
```

**Assigning IP to Bonded Interface:**

```bash
sudo ip addr add 192.168.1.100/24 dev bond0
sudo ip route add default via 192.168.1.1
```

**Persisting Bonding Configuration:**

- **systemd-networkd (`/etc/systemd/network/50-bond0.netdev`):**

  ```ini
  [NetDev]
  Name=bond0
  Kind=bond

  [Bond]
  Mode=802.3ad
  MIIMonitorSec=100ms
  ```

  **Bond Network Configuration (`/etc/systemd/network/50-bond0.network`):**

  ```ini
  [Match]
  Name=bond0

  [Network]
  Address=192.168.1.100/24
  Gateway=192.168.1.1
  DNS=8.8.8.8 8.8.4.4
  ```

  **Slave Interfaces (`/etc/systemd/network/50-enp3s0.network` and `50-enp3s1.network`):**

  ```ini
  [Match]
  Name=enp3s0

  [Network]
  Bond=bond0
  ```

- **Netplan:**
  ```yaml
  network:
    version: 2
    renderer: networkd
    bonds:
      bond0:
        interfaces: [enp3s0, enp3s1]
        parameters:
          mode: 802.3ad
          mii-monitor-interval: 100
        addresses: [192.168.1.100/24]
        gateway4: 192.168.1.1
        nameservers:
          addresses: [8.8.8.8, 8.8.4.4]
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

**Notes:**

- **Bonding Modes:**

  - **Mode 0 (balance-rr):** Round-robin.
  - **Mode 1 (active-backup):** Active backup.
  - **Mode 4 (802.3ad):** LACP (Link Aggregation Control Protocol).

- **Switch Configuration:** Ensure the network switch supports the chosen bonding mode, especially for modes requiring switch support (e.g., LACP).

### Routing Tables

**Purpose:** Define the paths that network traffic takes to reach different network destinations.

**Viewing Routing Tables:**

```bash
ip route show
```

- **Explanation:** Displays the system's routing table, showing routes to various network destinations.

**Adding a Route:**

```bash
sudo ip route add 10.0.0.0/24 via 192.168.1.1 dev enp3s0
```

- **Explanation:** Adds a route to the `10.0.0.0/24` network via the gateway `192.168.1.1` using the `enp3s0` interface.

**Deleting a Route:**

```bash
sudo ip route del 10.0.0.0/24 via 192.168.1.1 dev enp3s0
```

- **Explanation:** Removes the specified route from the routing table.

**Persisting Routes:**

- **NetworkManager:**

  ```bash
  nmcli connection modify "Wired connection 1" +ipv4.routes "10.0.0.0/24 192.168.1.1"
  nmcli connection up "Wired connection 1"
  ```

- **systemd-networkd (`/etc/systemd/network/60-route.network`):**

  ```ini
  [Match]
  Name=enp3s0

  [Network]
  Address=192.168.1.100/24
  Gateway=192.168.1.1
  DNS=8.8.8.8

  [Route]
  Destination=10.0.0.0/24
  Gateway=192.168.1.1
  ```

- **Netplan:**
  ```yaml
  network:
    version: 2
    renderer: networkd
    ethernets:
      enp3s0:
        dhcp4: yes
        routes:
          - to: 10.0.0.0/24
            via: 192.168.1.1
  ```
  **Apply Configuration:**
  ```bash
  sudo netplan apply
  ```

### DNS Configuration

DNS (Domain Name System) translates human-readable domain names to IP addresses.

**Managing DNS with NetworkManager:**

```bash
nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8 8.8.4.4"
nmcli connection up "Wired connection 1"
```

**Managing DNS with systemd-resolved:**

- **Set DNS for Interface:**

  ```bash
  sudo systemd-resolve --interface=enp3s0 --set-dns=8.8.8.8 --set-dns=8.8.4.4
  ```

- **Verify DNS Configuration:**
  ```bash
  systemd-resolve --status enp3s0
  ```

**Editing `/etc/resolv.conf`:**

- **Direct Edit:**
  ```ini
  nameserver 8.8.8.8
  nameserver 8.8.4.4
  ```
- **Notes:**
  - **Dynamic Updates:** Often managed by `systemd-resolved` or NetworkManager.
  - **Symbolic Links:** `/etc/resolv.conf` is typically a symlink to `/run/systemd/resolve/resolv.conf` when using `systemd-resolved`.

**Managing DNS Securely:**

- **Restrict Permissions:**
  ```bash
  sudo chmod 644 /etc/resolv.conf
  ```
- **Avoid Manual Edits:** Use NetworkManager or `systemd-resolved` to manage DNS settings to prevent overwriting.

---

## Wireless Networking

Managing wireless connections involves scanning for available networks, connecting to them, handling authentication, and ensuring secure and reliable connections.

### Understanding Wireless Concepts

1. **SSID (Service Set Identifier):**

   - **Description:** The name of a wireless network.
   - **Example:** "HomeNetwork", "OfficeWiFi".

2. **BSSID (Basic Service Set Identifier):**

   - **Description:** The MAC address of the access point (AP).

3. **Security Protocols:**

   - **WEP:** Outdated and insecure.
   - **WPA/WPA2:** Secure protocols with various modes (PSK, Enterprise).
   - **WPA3:** Latest standard with enhanced security.

4. **Channels:**

   - **Description:** Frequency bands used for Wi-Fi communication.
   - **Common Bands:** 2.4 GHz (channels 1-11), 5 GHz (channels 36-165).

5. **Frequency Bands:**
   - **2.4 GHz:** Longer range, more interference.
   - **5 GHz:** Shorter range, higher speeds, less interference.

### Scanning for Wi-Fi Networks

**Using `nmcli`:**

```bash
nmcli device wifi list
```

- **Explanation:** Lists available Wi-Fi networks detected by the wireless interface.

**Using `iw` Command:**

```bash
sudo iw dev wlan0 scan | grep SSID
```

- **Explanation:** Performs a scan for Wi-Fi networks and filters the output to show SSIDs.

**Using `iwlist`:**

```bash
sudo iwlist wlan0 scan | grep ESSID
```

- **Explanation:** Scans for Wi-Fi networks and displays their ESSIDs.

**Using `wpa_cli`:**

```bash
sudo wpa_cli scan
sudo wpa_cli scan_results
```

- **Explanation:** Initiates a Wi-Fi scan and retrieves the scan results.

### Connecting to Wi-Fi Networks

**Using NetworkManager (`nmcli`):**

1. **List Available Networks:**
   ```bash
   nmcli device wifi list
   ```
2. **Connect to a Network:**
   ```bash
   nmcli device wifi connect "SSID_Name" password "your_password"
   ```
   - **Explanation:** Connects to the specified Wi-Fi network using the provided password.

**Using `wpa_supplicant`:**

1. **Create Configuration File:**

   ```bash
   sudo wpa_passphrase "SSID_Name" "your_password" | sudo tee /etc/wpa_supplicant.conf
   ```

   - **Explanation:** Generates a `wpa_supplicant` configuration with the SSID and password.

2. **Start `wpa_supplicant`:**

   ```bash
   sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
   ```

   - **Explanation:** Starts the `wpa_supplicant` daemon in the background for interface `wlan0` using the specified configuration.

3. **Obtain IP Address via DHCP:**
   ```bash
   sudo dhclient wlan0
   ```
   - **Explanation:** Acquires an IP address for `wlan0` using DHCP.

**Using `nmtui`:**

1. **Launch `nmtui`:**

   ```bash
   sudo nmtui
   ```

   - **Explanation:** Opens the NetworkManager Text User Interface for managing network connections.

2. **Navigate to "Activate a connection".**

3. **Choose the desired Wi-Fi network and enter the password if required.**

### Security Protocols

1. **WEP (Wired Equivalent Privacy):**

   - **Status:** Deprecated and insecure.
   - **Recommendation:** Avoid using WEP; switch to WPA2 or WPA3.

2. **WPA (Wi-Fi Protected Access):**

   - **Version:** WPA1
   - **Features:** Improved security over WEP but vulnerable to certain attacks.

3. **WPA2:**

   - **Version:** WPA2
   - **Features:** Strong encryption with AES; widely used and secure.
   - **Modes:**
     - **PSK (Pre-Shared Key):** Suitable for home and small office networks.
     - **Enterprise:** Uses RADIUS servers for authentication; suitable for larger organizations.

4. **WPA3:**
   - **Version:** WPA3
   - **Features:** Enhanced security with SAE (Simultaneous Authentication of Equals); better protection against brute-force attacks.
   - **Status:** Emerging standard; support varies across devices.

**Configuring Security with `wpa_supplicant`:**

```ini
network={
    ssid="SecureNetwork"
    psk="secure_password"
    key_mgmt=WPA-PSK
}
```

### Managing Wi-Fi with `wpa_supplicant`

**Steps to Connect to a Wi-Fi Network:**

1. **Create Configuration File:**

   ```bash
   sudo nano /etc/wpa_supplicant/wpa_supplicant.conf
   ```

   **Example Content:**

   ```ini
   ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
   update_config=1
   country=US

   network={
       ssid="SecureNetwork"
       psk="secure_password"
       key_mgmt=WPA-PSK
   }
   ```

2. **Start `wpa_supplicant`:**

   ```bash
   sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
   ```

   - **Options:**
     - `-B`: Run in the background.
     - `-i`: Specify the interface.
     - `-c`: Specify the configuration file.

3. **Obtain IP Address via DHCP:**

   ```bash
   sudo dhclient wlan0
   ```

4. **Verify Connection:**
   ```bash
   iwconfig wlan0
   ping -c 4 google.com
   ```

**Automating `wpa_supplicant` at Boot:**

- **Create a Systemd Service (`/etc/systemd/system/wpa_supplicant.service`):**

  ```ini
  [Unit]
  Description=WPA supplicant
  After=network.target

  [Service]
  ExecStart=/sbin/wpa_supplicant -c /etc/wpa_supplicant/wpa_supplicant.conf -i wlan0
  Restart=always

  [Install]
  WantedBy=multi-user.target
  ```

- **Enable and Start the Service:**
  ```bash
  sudo systemctl enable wpa_supplicant
  sudo systemctl start wpa_supplicant
  ```

### Managing Wi-Fi with NetworkManager (`nmcli` & `nmtui`)

**Using `nmcli`:**

1. **List Available Networks:**

   ```bash
   nmcli device wifi list
   ```

   - **Explanation:** Displays available Wi-Fi networks detected by the wireless interface.

2. **Connect to a Network:**

   ```bash
   nmcli device wifi connect "SSID_Name" password "your_password"
   ```

   - **Explanation:** Connects to the specified Wi-Fi network using the provided password.

3. **Create a New Wi-Fi Connection:**

   ```bash
   nmcli connection add type wifi ifname wlan0 con-name HomeWiFi ssid HomeNetwork
   nmcli connection modify HomeWiFi wifi-sec.key-mgmt wpa-psk
   nmcli connection modify HomeWiFi wifi-sec.psk "your_password"
   nmcli connection up HomeWiFi
   ```

   - **Explanation:** Creates and activates a new Wi-Fi connection named `HomeWiFi`.

4. **Modify Existing Connection:**
   ```bash
   nmcli connection modify HomeWiFi ipv4.method manual ipv4.addresses "192.168.1.100/24" ipv4.gateway "192.168.1.1" ipv4.dns "8.8.8.8 8.8.4.4"
   nmcli connection up HomeWiFi
   ```
   - **Explanation:** Changes the `HomeWiFi` connection to use a static IP configuration.

**Using `nmtui`:**

1. **Launch `nmtui`:**

   ```bash
   sudo nmtui
   ```

   - **Explanation:** Opens the NetworkManager Text User Interface for managing network connections.

2. **Navigate to "Activate a connection".**

3. **Select the desired Wi-Fi network and enter the password if prompted.**

4. **To edit connections, choose "Edit a connection" and modify settings as needed.**

**Advantages of Using NetworkManager:**

- Simplifies complex network configurations.
- Provides seamless switching between networks.
- Integrates with desktop environments for user-friendly management.

---

## Advanced Network Configurations

Advanced network configurations enhance network performance, security, and scalability. This section covers virtual private networks (VPNs), IPv6, Quality of Service (QoS), and firewall integration.

### Virtual Private Networks (VPN)

**Purpose:** Establish secure connections over public networks, allowing remote access to private networks.

**Common VPN Protocols:**

- **OpenVPN:** Open-source, highly configurable.
- **IPsec:** Protocol suite for securing IP communications.
- **WireGuard:** Modern, lightweight VPN protocol.
- **L2TP (Layer 2 Tunneling Protocol):** Often combined with IPsec for security.

**Setting Up OpenVPN:**

1. **Install OpenVPN:**

   ```bash
   sudo apt update
   sudo apt install openvpn
   ```

2. **Obtain Configuration Files:**

   - Typically provided by the VPN service or administrator.

3. **Start OpenVPN with Configuration:**

   ```bash
   sudo openvpn --config /path/to/config.ovpn
   ```

   - **Explanation:** Initiates an OpenVPN connection using the specified configuration file.

4. **Run as a Service:**

   - **Create a Systemd Service (`/etc/systemd/system/openvpn@.service`):**

     ```ini
     [Unit]
     Description=OpenVPN connection to %i
     After=network.target

     [Service]
     Type=simple
     ExecStart=/usr/sbin/openvpn --config /etc/openvpn/%i.conf

     [Install]
     WantedBy=multi-user.target
     ```

   - **Enable and Start the Service:**
     ```bash
     sudo systemctl enable openvpn@config
     sudo systemctl start openvpn@config
     ```

**Setting Up WireGuard:**

1. **Install WireGuard:**

   ```bash
   sudo apt update
   sudo apt install wireguard
   ```

2. **Generate Keys:**

   ```bash
   wg genkey | sudo tee /etc/wireguard/privatekey | wg pubkey | sudo tee /etc/wireguard/publickey
   ```

3. **Create Configuration File (`/etc/wireguard/wg0.conf`):**

   ```ini
   [Interface]
   PrivateKey = <your_private_key>
   Address = 10.0.0.1/24
   ListenPort = 51820

   [Peer]
   PublicKey = <peer_public_key>
   AllowedIPs = 10.0.0.2/32
   Endpoint = peer_ip:51820
   ```

4. **Start WireGuard Interface:**

   ```bash
   sudo wg-quick up wg0
   ```

5. **Enable at Boot:**
   ```bash
   sudo systemctl enable wg-quick@wg0
   ```

**Notes:**

- **Security:** Always use strong encryption and authentication methods.
- **Firewall Rules:** Adjust firewall settings to allow VPN traffic.

### IPv6 Configuration

**Overview:**

- IPv6 is the latest version of the Internet Protocol, addressing the limitations of IPv4.
- Provides a vastly larger address space and improved routing.

**Enabling IPv6:**

1. **Check if IPv6 is Enabled:**

   ```bash
   ip -6 addr show
   ```

   - **Explanation:** Displays IPv6 addresses assigned to interfaces.

2. **Enable IPv6 in NetworkManager:**

   ```bash
   nmcli connection modify "Wired connection 1" ipv6.method auto
   nmcli connection up "Wired connection 1"
   ```

3. **Enable IPv6 in systemd-networkd (`/etc/systemd/network/20-wired.network`):**

   ```ini
   [Match]
   Name=enp3s0

   [Network]
   DHCP=ipv6
   ```

4. **Enable IPv6 in Netplan (`/etc/netplan/01-netcfg.yaml`):**
   ```yaml
   network:
     version: 2
     renderer: networkd
     ethernets:
       enp3s0:
         dhcp4: yes
         dhcp6: true
   ```
   **Apply Configuration:**
   ```bash
   sudo netplan apply
   ```

**Disabling IPv6:**

- **Temporarily:**
  ```bash
  sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
  sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
  ```
- **Permanently:**
  Add the following lines to `/etc/sysctl.conf`:
  ```ini
  net.ipv6.conf.all.disable_ipv6 = 1
  net.ipv6.conf.default.disable_ipv6 = 1
  ```
  **Apply Changes:**
  ```bash
  sudo sysctl -p
  ```

**Notes:**

- **Dual Stack:** Many systems use both IPv4 and IPv6 (dual-stack) for compatibility.
- **Firewall Rules:** Ensure IPv6 firewall rules are properly configured if IPv6 is enabled.

### Quality of Service (QoS)

**Purpose:** Manage and prioritize network traffic to ensure critical services receive adequate bandwidth and low latency.

**Using `tc` (Traffic Control):**

1. **View Current QoS Rules:**

   ```bash
   sudo tc qdisc show
   ```

   - **Explanation:** Displays current queuing disciplines (qdiscs) applied to interfaces.

2. **Add Hierarchical Token Bucket (HTB) Qdisc:**

   ```bash
   sudo tc qdisc add dev enp3s0 root handle 1: htb default 12
   ```

   - **Explanation:** Adds an HTB queuing discipline to `enp3s0` with a default class ID `12`.

3. **Create a Parent Class:**

   ```bash
   sudo tc class add dev enp3s0 parent 1: classid 1:1 htb rate 1000mbit
   ```

   - **Explanation:** Creates a parent class with a maximum rate of 1000 Mbps.

4. **Create Child Classes with Different Priorities:**

   ```bash
   sudo tc class add dev enp3s0 parent 1:1 classid 1:10 htb rate 800mbit
   sudo tc class add dev enp3s0 parent 1:1 classid 1:20 htb rate 200mbit
   ```

   - **Explanation:** Defines child classes with allocated bandwidth.

5. **Attach Filters to Direct Traffic:**
   ```bash
   sudo tc filter add dev enp3s0 protocol ip parent 1:0 prio 1 u32 match ip dport 22 0xffff flowid 1:10
   sudo tc filter add dev enp3s0 protocol ip parent 1:0 prio 2 u32 match ip dport 80 0xffff flowid 1:20
   ```
   - **Explanation:** Filters traffic based on destination ports and assigns them to respective classes.

**Notes:**

- **HTB:** Hierarchical Token Bucket is a flexible queueing discipline for shaping traffic.
- **Filters:** Define rules to match specific traffic patterns and assign them to classes.
- **Persistence:** Use scripts or systemd services to apply QoS settings at boot.

**Using `tc` with Scripts:**

- Automate QoS configurations with shell scripts for consistent application across reboots.

**Example Script:**

```bash
#!/bin/bash

# setup_qos.sh: Configure QoS on enp3s0

# Clear existing qdiscs
sudo tc qdisc del dev enp3s0 root

# Add HTB qdisc
sudo tc qdisc add dev enp3s0 root handle 1: htb default 12

# Add parent class
sudo tc class add dev enp3s0 parent 1: classid 1:1 htb rate 1000mbit

# Add child classes
sudo tc class add dev enp3s0 parent 1:1 classid 1:10 htb rate 800mbit
sudo tc class add dev enp3s0 parent 1:1 classid 1:20 htb rate 200mbit

# Add filters
sudo tc filter add dev enp3s0 protocol ip parent 1:0 prio 1 u32 match ip dport 22 0xffff flowid 1:10
sudo tc filter add dev enp3s0 protocol ip parent 1:0 prio 2 u32 match ip dport 80 0xffff flowid 1:20
```

**Running the Script:**

```bash
sudo bash setup_qos.sh
```

### Firewall Integration

**Overview:**

- Firewalls control incoming and outgoing network traffic based on predefined security rules.
- Essential for protecting systems from unauthorized access and threats.

**Common Firewall Tools:**

- **iptables:** Traditional Linux firewall.
- **nftables:** Modern replacement for `iptables`.
- **ufw (Uncomplicated Firewall):** Simplified interface for managing firewall rules.
- **firewalld:** Dynamic firewall management tool with support for zones.

### iptables

**Overview:**

- **iptables** is a powerful tool for configuring the Linux kernel firewall.
- Manages rules for filtering, NAT, and more across various tables.

**Basic Structure:**

- **Tables:** `filter`, `nat`, `mangle`, `raw`, `security`.
- **Chains:** Predefined paths within each table (e.g., `INPUT`, `FORWARD`, `OUTPUT` in `filter`).

**Common Commands:**

1. **List All Rules:**

   ```bash
   sudo iptables -L -v -n
   ```

   - **Explanation:** Lists all rules in all chains with verbose output and numeric addresses.

2. **Add a Rule to Allow SSH (Port 22):**

   ```bash
   sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT
   ```

   - **Explanation:** Appends a rule to the `INPUT` chain to accept TCP traffic on port 22.

3. **Block an IP Address:**

   ```bash
   sudo iptables -A INPUT -s 203.0.113.5 -j DROP
   ```

   - **Explanation:** Drops all incoming traffic from IP `203.0.113.5`.

4. **Allow Established and Related Connections:**

   ```bash
   sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
   ```

   - **Explanation:** Accepts traffic for established connections and related packets.

5. **Set Default Policies:**

   ```bash
   sudo iptables -P INPUT DROP
   sudo iptables -P FORWARD DROP
   sudo iptables -P OUTPUT ACCEPT
   ```

   - **Explanation:** Sets default policies for the `INPUT` and `FORWARD` chains to drop, and `OUTPUT` to accept.

6. **Save iptables Rules:**

   - **On Debian/Ubuntu:**
     ```bash
     sudo iptables-save | sudo tee /etc/iptables/rules.v4
     ```
   - **On RHEL/CentOS:**
     ```bash
     sudo service iptables save
     ```
   - **Explanation:** Saves current iptables rules to persist across reboots.

7. **Restore iptables Rules:**

   ```bash
   sudo iptables-restore < /etc/iptables/rules.v4
   ```

   - **Explanation:** Restores iptables rules from a saved file.

8. **Delete a Specific Rule:**
   ```bash
   sudo iptables -D INPUT -p tcp --dport 22 -j ACCEPT
   ```
   - **Explanation:** Deletes the specified rule from the `INPUT` chain.

**Advanced Usage:**

- **NAT (Network Address Translation):**

  - **Masquerade Traffic:**
    ```bash
    sudo iptables -t nat -A POSTROUTING -o enp3s0 -j MASQUERADE
    ```
    - **Explanation:** Enables NAT for outgoing traffic on `enp3s0`.

- **Port Forwarding:**
  ```bash
  sudo iptables -t nat -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination 192.168.1.100:80
  sudo iptables -A FORWARD -p tcp -d 192.168.1.100 --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
  ```
  - **Explanation:** Forwards incoming traffic on port `8080` to `192.168.1.100:80`.

**Notes:**

- **Persistence:** Ensure iptables rules are saved and restored on system boot.
- **Ordering Matters:** Rules are evaluated in the order they are added.
- **Security:** Be cautious when setting default policies to `DROP` to avoid locking yourself out.

### nftables

**Overview:**

- **nftables** is the successor to `iptables`, providing a unified framework for packet filtering and classification.
- Simplifies complex rule management and improves performance.

**Basic Structure:**

- **Tables:** Contain chains and rules.
- **Chains:** Define the points in the packet processing where rules are applied (e.g., `input`, `forward`, `output`).
- **Rules:** Define matching criteria and actions.

**Common Commands:**

1. **List All Rules:**

   ```bash
   sudo nft list ruleset
   ```

   - **Explanation:** Displays the entire nftables ruleset.

2. **Create a Table:**

   ```bash
   sudo nft add table inet filter
   ```

   - **Explanation:** Creates a new table named `filter` in the `inet` family.

3. **Create a Chain:**

   ```bash
   sudo nft add chain inet filter input { type filter hook input priority 0 \; policy drop \; }
   ```

   - **Explanation:** Adds a chain named `input` to the `filter` table, hooks it to the `input` point with a default policy of `drop`.

4. **Add a Rule to Allow SSH (Port 22):**

   ```bash
   sudo nft add rule inet filter input tcp dport 22 accept
   ```

   - **Explanation:** Adds a rule to the `input` chain to accept TCP traffic on port 22.

5. **Block an IP Address:**

   ```bash
   sudo nft add rule inet filter input ip saddr 203.0.113.5 drop
   ```

   - **Explanation:** Drops all incoming traffic from IP `203.0.113.5`.

6. **Allow Established and Related Connections:**

   ```bash
   sudo nft add rule inet filter input ct state established,related accept
   ```

   - **Explanation:** Accepts traffic for established connections and related packets.

7. **Set Default Policy:**

   - **Already set during chain creation with `policy drop`.**

8. **Save nftables Rules:**

   ```bash
   sudo nft list ruleset > /etc/nftables.conf
   ```

   - **Explanation:** Saves current nftables rules to a configuration file.

9. **Restore nftables Rules:**

   ```bash
   sudo nft -f /etc/nftables.conf
   ```

   - **Explanation:** Loads nftables rules from a configuration file.

10. **Delete a Specific Rule:**
    ```bash
    sudo nft delete rule inet filter input handle <handle_number>
    ```
    - **Explanation:** Deletes a rule from the `input` chain based on its handle number.

**Advantages:**

- **Unified Framework:** Handles IPv4, IPv6, and Ethernet bridging.
- **Simplified Syntax:** Easier to write and manage complex rules.
- **Performance:** Improved performance over `iptables` due to a single kernel interface.

**Notes:**

- **Transition:** Familiarize yourself with nftables syntax if migrating from iptables.
- **Persistence:** Ensure nftables rules are saved and restored on system boot.

### ufw (Uncomplicated Firewall)

**Overview:**

- **ufw** is a simplified interface for managing firewall rules, built on top of iptables.
- Designed to make firewall configuration easier, especially for beginners.

**Common Commands:**

1. **Enable ufw:**

   ```bash
   sudo ufw enable
   ```

   - **Explanation:** Activates the ufw firewall.

2. **Disable ufw:**

   ```bash
   sudo ufw disable
   ```

   - **Explanation:** Deactivates the ufw firewall.

3. **Check ufw Status:**

   ```bash
   sudo ufw status verbose
   ```

   - **Explanation:** Displays the current status and rules of ufw.

4. **Allow SSH:**

   ```bash
   sudo ufw allow ssh
   ```

   - **Explanation:** Allows incoming SSH connections (port 22).

5. **Allow Specific Port (e.g., HTTP):**

   ```bash
   sudo ufw allow 80/tcp
   ```

   - **Explanation:** Allows incoming TCP traffic on port 80.

6. **Deny Specific Port (e.g., Telnet):**

   ```bash
   sudo ufw deny 23/tcp
   ```

   - **Explanation:** Denies incoming TCP traffic on port 23.

7. **Delete a Rule:**

   ```bash
   sudo ufw delete allow 80/tcp
   ```

   - **Explanation:** Removes the rule allowing TCP traffic on port 80.

8. **Allow from Specific IP:**

   ```bash
   sudo ufw allow from 192.168.1.50
   ```

   - **Explanation:** Allows all incoming traffic from IP `192.168.1.50`.

9. **Limit Connections (e.g., SSH):**

   ```bash
   sudo ufw limit ssh
   ```

   - **Explanation:** Limits the rate of SSH connections to prevent brute-force attacks.

10. **Allow Port Range:**

    ```bash
    sudo ufw allow 1000:2000/tcp
    ```

    - **Explanation:** Allows incoming TCP traffic on ports 1000 to 2000.

11. **Allow Specific IP and Port:**
    ```bash
    sudo ufw allow from 192.168.1.50 to any port 22 proto tcp
    ```
    - **Explanation:** Allows TCP traffic on port 22 from IP `192.168.1.50`.

**Advanced Commands:**

- **Reset ufw to Default:**

  ```bash
  sudo ufw reset
  ```

  - **Explanation:** Resets ufw to default settings, removing all rules.

- **Set Default Policies:**

  ```bash
  sudo ufw default deny incoming
  sudo ufw default allow outgoing
  ```

  - **Explanation:** Sets default policies to deny all incoming traffic and allow all outgoing traffic.

- **Enable Logging:**
  ```bash
  sudo ufw logging on
  ```
  - **Explanation:** Activates logging for ufw, useful for monitoring and debugging.

**Notes:**

- **Simplicity:** Ideal for users seeking a straightforward firewall management tool.
- **Compatibility:** Works well with NetworkManager and other network management tools.
- **Security:** Always set appropriate default policies and allow only necessary services.

### firewalld

**Overview:**

- **firewalld** is a dynamic firewall management tool with support for zones.
- Provides an abstraction layer over iptables and nftables, allowing for more flexible configurations.

**Common Commands:**

1. **Install firewalld:**

   ```bash
   sudo apt install firewalld
   ```

   - **Explanation:** Installs the firewalld package.

2. **Start and Enable firewalld:**

   ```bash
   sudo systemctl start firewalld
   sudo systemctl enable firewalld
   ```

   - **Explanation:** Starts firewalld and configures it to start on boot.

3. **Check firewalld Status:**

   ```bash
   sudo systemctl status firewalld
   ```

   - **Explanation:** Displays the current status of firewalld.

4. **List Active Zones:**

   ```bash
   sudo firewall-cmd --get-active-zones
   ```

   - **Explanation:** Shows zones that are currently active and their associated interfaces.

5. **List Rules in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --list-all
   ```

   - **Explanation:** Displays all rules applied to the `public` zone.

6. **Allow a Service in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --add-service=http --permanent
   ```

   - **Explanation:** Permanently allows the HTTP service in the `public` zone.

7. **Reload firewalld to Apply Changes:**

   ```bash
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Reloads firewalld configurations without interrupting existing connections.

8. **Block a Port in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --remove-port=23/tcp --permanent
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Removes the rule allowing TCP traffic on port 23 in the `public` zone.

9. **Allow an IP Address:**

   ```bash
   sudo firewall-cmd --permanent --add-rich-rule='rule family="ipv4" source address="192.168.1.50" accept'
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Permits all traffic from IP `192.168.1.50`.

10. **Set Default Zone:**
    ```bash
    sudo firewall-cmd --set-default-zone=public
    ```
    - **Explanation:** Sets the default zone to `public`.

**Advantages:**

- **Zones:** Simplifies managing rules based on network trust levels.
- **Dynamic Management:** Allows adding/removing rules without restarting the firewall.
- **Rich Rules:** Supports complex rule configurations using rich language.

**Notes:**

- **Integration:** Integrates well with NetworkManager and other network tools.
- **GUI Support:** Offers a graphical interface (`firewall-config`) for desktop environments.

### Other Networking Tools

1. **netcat (nc):**

   - **Description:** Utility for reading from and writing to network connections.
   - **Common Usage:**
     - **Open a TCP Connection:**
       ```bash
       nc example.com 80
       ```
     - **Listen on a Port:**
       ```bash
       nc -l 1234
       ```

2. **ethtool:**

   - **Description:** Utility for querying and controlling network drivers and hardware settings.
   - **Common Usage:**
     - **Check Link Status:**
       ```bash
       sudo ethtool enp3s0
       ```
     - **Change Speed and Duplex:**
       ```bash
       sudo ethtool -s enp3s0 speed 100 duplex full
       ```

3. **mtr:**

   - **Description:** Network diagnostic tool combining `ping` and `traceroute`.
   - **Common Usage:**
     ```bash
     mtr google.com
     ```
     - **Explanation:** Provides a real-time view of the path packets take to reach `google.com`.

4. **tcpdump:**

   - **Description:** Network packet analyzer.
   - **Common Usage:**
     ```bash
     sudo tcpdump -i enp3s0
     ```
     - **Explanation:** Captures and displays network packets on `enp3s0`.

5. **nmap:**
   - **Description:** Network exploration and security auditing tool.
   - **Common Usage:**
     ```bash
     nmap -sP 192.168.1.0/24
     ```
     - **Explanation:** Performs a ping scan to discover active hosts in the `192.168.1.0/24` subnet.

**Notes:**

- **Security:** Use tools like `tcpdump` and `nmap` responsibly and ethically.
- **Permissions:** Many networking tools require elevated privileges to function correctly.

---

## Command-Line Tools for Networking and Firewall Management

This section delves deeper into essential command-line tools for managing networking and firewall rules in Linux. Each tool is explained with its common commands and usage scenarios.

### iptables

**Overview:**

- **iptables** is a powerful tool for configuring the Linux kernel firewall.
- Manages rules for filtering, NAT, and more across various tables.

**Basic Structure:**

- **Tables:** `filter`, `nat`, `mangle`, `raw`, `security`.
- **Chains:** Predefined paths within each table (e.g., `INPUT`, `FORWARD`, `OUTPUT` in `filter`).

**Common Commands and Explanations:**

1. **List All Rules:**

   ```bash
   sudo iptables -L -v -n
   ```

   - **Explanation:** Lists all rules in all chains with verbose output and numeric addresses.

2. **Allow SSH (Port 22):**

   ```bash
   sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT
   ```

   - **Explanation:** Appends a rule to the `INPUT` chain to accept TCP traffic on port 22.

3. **Block an IP Address:**

   ```bash
   sudo iptables -A INPUT -s 203.0.113.5 -j DROP
   ```

   - **Explanation:** Drops all incoming traffic from IP `203.0.113.5`.

4. **Allow Established and Related Connections:**

   ```bash
   sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
   ```

   - **Explanation:** Accepts traffic for established connections and related packets.

5. **Set Default Policies:**

   ```bash
   sudo iptables -P INPUT DROP
   sudo iptables -P FORWARD DROP
   sudo iptables -P OUTPUT ACCEPT
   ```

   - **Explanation:** Sets default policies for the `INPUT` and `FORWARD` chains to drop, and `OUTPUT` to accept.

6. **Save iptables Rules:**

   - **On Debian/Ubuntu:**
     ```bash
     sudo iptables-save | sudo tee /etc/iptables/rules.v4
     ```
   - **On RHEL/CentOS:**
     ```bash
     sudo service iptables save
     ```
   - **Explanation:** Saves current iptables rules to persist across reboots.

7. **Restore iptables Rules:**

   ```bash
   sudo iptables-restore < /etc/iptables/rules.v4
   ```

   - **Explanation:** Restores iptables rules from a saved file.

8. **Delete a Specific Rule:**
   ```bash
   sudo iptables -D INPUT -p tcp --dport 22 -j ACCEPT
   ```
   - **Explanation:** Deletes the specified rule from the `INPUT` chain.

**Advanced Usage:**

- **NAT (Network Address Translation):**

  - **Masquerade Traffic:**
    ```bash
    sudo iptables -t nat -A POSTROUTING -o enp3s0 -j MASQUERADE
    ```
    - **Explanation:** Enables NAT for outgoing traffic on `enp3s0`.

- **Port Forwarding:**

  ```bash
  sudo iptables -t nat -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination 192.168.1.100:80
  sudo iptables -A FORWARD -p tcp -d 192.168.1.100 --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
  ```

  - **Explanation:** Forwards incoming traffic on port `8080` to `192.168.1.100:80`.

- **Logging Dropped Packets:**
  ```bash
  sudo iptables -A INPUT -j LOG --log-prefix "iptables-dropped: " --log-level 4
  ```
  - **Explanation:** Logs all dropped packets with the prefix `iptables-dropped:`.

**Notes:**

- **Persistence:** Ensure iptables rules are saved and restored on system boot.
- **Ordering Matters:** Rules are evaluated in the order they are added.
- **Security:** Be cautious when setting default policies to `DROP` to avoid locking yourself out.

### nftables

**Overview:**

- **nftables** is the successor to `iptables`, providing a unified framework for packet filtering and classification.
- Simplifies complex rule management and improves performance.

**Basic Structure:**

- **Tables:** Contain chains and rules.
- **Chains:** Define the points in the packet processing where rules are applied (e.g., `input`, `forward`, `output`).
- **Rules:** Define matching criteria and actions.

**Common Commands and Explanations:**

1. **List All Rules:**

   ```bash
   sudo nft list ruleset
   ```

   - **Explanation:** Displays the entire nftables ruleset.

2. **Create a Table:**

   ```bash
   sudo nft add table inet filter
   ```

   - **Explanation:** Creates a new table named `filter` in the `inet` family (supports both IPv4 and IPv6).

3. **Create a Chain:**

   ```bash
   sudo nft add chain inet filter input { type filter hook input priority 0 \; policy drop \; }
   ```

   - **Explanation:** Adds a chain named `input` to the `filter` table, hooks it to the `input` point with a default policy of `drop`.

4. **Add a Rule to Allow SSH (Port 22):**

   ```bash
   sudo nft add rule inet filter input tcp dport 22 accept
   ```

   - **Explanation:** Adds a rule to the `input` chain to accept TCP traffic on port 22.

5. **Block an IP Address:**

   ```bash
   sudo nft add rule inet filter input ip saddr 203.0.113.5 drop
   ```

   - **Explanation:** Drops all incoming traffic from IP `203.0.113.5`.

6. **Allow Established and Related Connections:**

   ```bash
   sudo nft add rule inet filter input ct state established,related accept
   ```

   - **Explanation:** Accepts traffic for established connections and related packets.

7. **Set Default Policy:**

   - **Already set during chain creation with `policy drop`.**

8. **Save nftables Rules:**

   ```bash
   sudo nft list ruleset > /etc/nftables.conf
   ```

   - **Explanation:** Saves current nftables rules to a configuration file.

9. **Restore nftables Rules:**

   ```bash
   sudo nft -f /etc/nftables.conf
   ```

   - **Explanation:** Loads nftables rules from a configuration file.

10. **Delete a Specific Rule:**
    ```bash
    sudo nft delete rule inet filter input handle <handle_number>
    ```
    - **Explanation:** Deletes a rule from the `input` chain based on its handle number.

**Advanced Usage:**

- **NAT (Network Address Translation):**

  ```bash
  sudo nft add table ip nat
  sudo nft add chain ip nat POSTROUTING { type nat hook postrouting priority 100 \; }
  sudo nft add rule ip nat POSTROUTING oif "enp3s0" masquerade
  ```

  - **Explanation:** Sets up NAT for outgoing traffic on `enp3s0`.

- **Port Forwarding:**

  ```bash
  sudo nft add table inet nat
  sudo nft add chain inet nat PREROUTING { type nat hook prerouting priority 0 \; }
  sudo nft add rule inet nat PREROUTING tcp dport 8080 dnat to 192.168.1.100:80
  sudo nft add chain inet nat POSTROUTING { type nat hook postrouting priority 100 \; }
  sudo nft add rule inet nat POSTROUTING oif "enp3s0" masquerade
  ```

  - **Explanation:** Forwards incoming traffic on port `8080` to `192.168.1.100:80` and enables masquerading for outbound traffic.

- **Logging Dropped Packets:**
  ```bash
  sudo nft add rule inet filter input log prefix "nftables-dropped: " level info
  sudo nft add rule inet filter input drop
  ```
  - **Explanation:** Logs all dropped packets with the prefix `nftables-dropped:`.

**Advantages:**

- **Unified Framework:** Handles IPv4, IPv6, and Ethernet bridging.
- **Simplified Syntax:** Easier to write and manage complex rules.
- **Performance:** Improved performance over `iptables` due to a single kernel interface.

**Notes:**

- **Transition:** Familiarize yourself with nftables syntax if migrating from iptables.
- **Persistence:** Ensure nftables rules are saved and restored on system boot.

### ufw (Uncomplicated Firewall)

**Overview:**

- **ufw** is a simplified interface for managing firewall rules, built on top of iptables.
- Designed to make firewall configuration easier, especially for beginners.

**Common Commands and Explanations:**

1. **Enable ufw:**

   ```bash
   sudo ufw enable
   ```

   - **Explanation:** Activates the ufw firewall.

2. **Disable ufw:**

   ```bash
   sudo ufw disable
   ```

   - **Explanation:** Deactivates the ufw firewall.

3. **Check ufw Status:**

   ```bash
   sudo ufw status verbose
   ```

   - **Explanation:** Displays the current status and rules of ufw.

4. **Allow SSH:**

   ```bash
   sudo ufw allow ssh
   ```

   - **Explanation:** Allows incoming SSH connections (port 22).

5. **Allow Specific Port (e.g., HTTP):**

   ```bash
   sudo ufw allow 80/tcp
   ```

   - **Explanation:** Allows incoming TCP traffic on port 80.

6. **Deny Specific Port (e.g., Telnet):**

   ```bash
   sudo ufw deny 23/tcp
   ```

   - **Explanation:** Denies incoming TCP traffic on port 23.

7. **Delete a Rule:**

   ```bash
   sudo ufw delete allow 80/tcp
   ```

   - **Explanation:** Removes the rule allowing TCP traffic on port 80.

8. **Allow from Specific IP:**

   ```bash
   sudo ufw allow from 192.168.1.50
   ```

   - **Explanation:** Allows all incoming traffic from IP `192.168.1.50`.

9. **Limit Connections (e.g., SSH):**

   ```bash
   sudo ufw limit ssh
   ```

   - **Explanation:** Limits the rate of SSH connections to prevent brute-force attacks.

10. **Allow Port Range:**

    ```bash
    sudo ufw allow 1000:2000/tcp
    ```

    - **Explanation:** Allows incoming TCP traffic on ports 1000 to 2000.

11. **Allow Specific IP and Port:**
    ```bash
    sudo ufw allow from 192.168.1.50 to any port 22 proto tcp
    ```
    - **Explanation:** Allows TCP traffic on port 22 from IP `192.168.1.50`.

**Advanced Commands and Explanations:**

- **Reset ufw to Default:**

  ```bash
  sudo ufw reset
  ```

  - **Explanation:** Resets ufw to default settings, removing all rules.

- **Set Default Policies:**

  ```bash
  sudo ufw default deny incoming
  sudo ufw default allow outgoing
  ```

  - **Explanation:** Sets default policies to deny all incoming traffic and allow all outgoing traffic.

- **Enable Logging:**

  ```bash
  sudo ufw logging on
  ```

  - **Explanation:** Activates logging for ufw, useful for monitoring and debugging.

- **Allow ICMP (Ping):**

  ```bash
  sudo ufw allow proto icmp
  ```

  - **Explanation:** Allows ICMP traffic, enabling ping responses.

- **Deny All Incoming Traffic Except Allowed Services:**
  ```bash
  sudo ufw default deny incoming
  sudo ufw default allow outgoing
  sudo ufw allow ssh
  sudo ufw allow http
  ```
  - **Explanation:** Sets strict incoming traffic policies while allowing essential services.

**Notes:**

- **Simplicity:** Ideal for users seeking a straightforward firewall management tool.
- **Compatibility:** Works well with NetworkManager and other network management tools.
- **Security:** Always set appropriate default policies and allow only necessary services.

### firewalld

**Overview:**

- **firewalld** is a dynamic firewall management tool with support for zones.
- Provides an abstraction layer over iptables and nftables, allowing for more flexible configurations.

**Common Commands and Explanations:**

1. **Install firewalld:**

   ```bash
   sudo apt install firewalld
   ```

   - **Explanation:** Installs the firewalld package.

2. **Start and Enable firewalld:**

   ```bash
   sudo systemctl start firewalld
   sudo systemctl enable firewalld
   ```

   - **Explanation:** Starts firewalld and configures it to start on boot.

3. **Check firewalld Status:**

   ```bash
   sudo systemctl status firewalld
   ```

   - **Explanation:** Displays the current status of firewalld.

4. **List Active Zones:**

   ```bash
   sudo firewall-cmd --get-active-zones
   ```

   - **Explanation:** Shows zones that are currently active and their associated interfaces.

5. **List Rules in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --list-all
   ```

   - **Explanation:** Displays all rules applied to the `public` zone.

6. **Allow a Service in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --add-service=http --permanent
   ```

   - **Explanation:** Permanently allows the HTTP service in the `public` zone.

7. **Reload firewalld to Apply Changes:**

   ```bash
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Reloads firewalld configurations without interrupting existing connections.

8. **Block a Port in a Zone:**

   ```bash
   sudo firewall-cmd --zone=public --remove-port=23/tcp --permanent
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Removes the rule allowing TCP traffic on port 23 in the `public` zone.

9. **Allow an IP Address:**

   ```bash
   sudo firewall-cmd --permanent --add-rich-rule='rule family="ipv4" source address="192.168.1.50" accept'
   sudo firewall-cmd --reload
   ```

   - **Explanation:** Permits all traffic from IP `192.168.1.50`.

10. **Set Default Zone:**
    ```bash
    sudo firewall-cmd --set-default-zone=public
    ```
    - **Explanation:** Sets the default zone to `public`.

**Advanced Commands and Explanations:**

- **Add a Port with Specific Protocol:**

  ```bash
  sudo firewall-cmd --zone=public --add-port=8080/tcp --permanent
  sudo firewall-cmd --reload
  ```

  - **Explanation:** Allows incoming TCP traffic on port `8080` in the `public` zone.

- **Add a Rich Rule for Logging:**

  ```bash
  sudo firewall-cmd --permanent --add-rich-rule='rule family="ipv4" source address="203.0.113.5" log prefix="Blocked IP: " level="info"'
  sudo firewall-cmd --reload
  ```

  - **Explanation:** Logs all traffic from IP `203.0.113.5` with the prefix `Blocked IP:`.

- **Remove a Service from a Zone:**

  ```bash
  sudo firewall-cmd --zone=public --remove-service=http --permanent
  sudo firewall-cmd --reload
  ```

  - **Explanation:** Removes the HTTP service from the `public` zone.

- **Add Masquerading:**

  ```bash
  sudo firewall-cmd --zone=public --add-masquerade --permanent
  sudo firewall-cmd --reload
  ```

  - **Explanation:** Enables masquerading (NAT) for the `public` zone.

- **Add Forwarding Rule:**
  ```bash
  sudo firewall-cmd --zone=public --add-forward-port=port=80:proto=tcp:toport=8080 --permanent
  sudo firewall-cmd --reload
  ```
  - **Explanation:** Forwards incoming TCP traffic on port `80` to port `8080`.

**Notes:**

- **Zones:** Different zones can have different rules based on trust levels.
- **Rich Rules:** Allow for more complex and granular rule definitions.

### Other Networking Tools

1. **netcat (nc):**

   - **Description:** Utility for reading from and writing to network connections.
   - **Common Usage:**

     - **Open a TCP Connection:**

       ```bash
       nc example.com 80
       ```

       - **Explanation:** Connects to `example.com` on port `80` using TCP.

     - **Listen on a Port:**

       ```bash
       nc -l 1234
       ```

       - **Explanation:** Listens for incoming connections on port `1234`.

     - **Transfer Files:**
       - **Send:**
         ```bash
         cat file.txt | nc -l 1234
         ```
       - **Receive:**
         ```bash
         nc <sender_ip> 1234 > received_file.txt
         ```
       - **Explanation:** Transfers `file.txt` from the sender to the receiver over TCP port `1234`.

2. **ethtool:**

   - **Description:** Utility for querying and controlling network drivers and hardware settings.
   - **Common Usage:**

     - **Check Link Status:**

       ```bash
       sudo ethtool enp3s0
       ```

       - **Explanation:** Displays detailed information about the `enp3s0` interface, including link status.

     - **Change Speed and Duplex:**

       ```bash
       sudo ethtool -s enp3s0 speed 100 duplex full
       ```

       - **Explanation:** Sets the speed to 100 Mbps and duplex mode to full for `enp3s0`.

     - **Enable Wake-on-LAN:**
       ```bash
       sudo ethtool -s enp3s0 wol g
       ```
       - **Explanation:** Configures `enp3s0` to wake the system on receiving a magic packet.

3. **mtr:**

   - **Description:** Network diagnostic tool combining `ping` and `traceroute`.
   - **Common Usage:**
     ```bash
     mtr google.com
     ```
     - **Explanation:** Provides a real-time view of the path packets take to reach `google.com`, including latency and packet loss at each hop.

4. **tcpdump:**

   - **Description:** Network packet analyzer.
   - **Common Usage:**

     ```bash
     sudo tcpdump -i enp3s0
     ```

     - **Explanation:** Captures and displays network packets on the `enp3s0` interface.

   - **Capture Specific Traffic:**
     ```bash
     sudo tcpdump -i enp3s0 tcp port 22
     ```
     - **Explanation:** Captures TCP traffic on port `22` (SSH) on `enp3s0`.

5. **nmap:**

   - **Description:** Network exploration and security auditing tool.
   - **Common Usage:**

     ```bash
     nmap -sP 192.168.1.0/24
     ```

     - **Explanation:** Performs a ping scan to discover active hosts in the `192.168.1.0/24` subnet.

   - **Scan Open Ports:**
     ```bash
     nmap -sV example.com
     ```
     - **Explanation:** Scans `example.com` for open ports and attempts to determine service versions.

**Notes:**

- **Security:** Use tools like `tcpdump` and `nmap` responsibly and ethically.
- **Permissions:** Many networking tools require elevated privileges to function correctly.

---

## Troubleshooting

Network issues can arise from misconfigurations, hardware failures, software bugs, or external factors. Effective troubleshooting involves systematic diagnosis using various tools and techniques.

### Diagnosing Connectivity Issues

1. **Check Physical Connections:**

   - Ensure cables are connected.
   - Verify link lights on network interfaces and switches.

2. **Verify Interface Status:**

   ```bash
   ip link show
   ```

   - **Explanation:** Ensures interfaces are `UP`.

3. **Check IP Configuration:**

   ```bash
   ip addr show
   ```

   - **Explanation:** Confirms correct IP addresses and subnet masks.

4. **Check Routing Table:**

   ```bash
   ip route show
   ```

   - **Explanation:** Ensures default gateway is set correctly.

5. **Test Connectivity:**
   - **Ping Local Interface:**
     ```bash
     ping -c 4 127.0.0.1
     ```
   - **Ping Gateway:**
     ```bash
     ping -c 4 192.168.1.1
     ```
   - **Ping External Host:**
     ```bash
     ping -c 4 google.com
     ```
   - **Explanation:** Tests various levels of network connectivity.

### Analyzing Logs

1. **System Logs:**

   ```bash
   sudo journalctl -u NetworkManager
   sudo journalctl -u systemd-networkd
   sudo journalctl -u wpa_supplicant
   ```

   - **Explanation:** Displays logs related to network services.

2. **Kernel Logs:**

   ```bash
   dmesg | grep -i network
   dmesg | grep -i wlan
   ```

   - **Explanation:** Shows kernel messages related to networking and wireless interfaces.

3. **Application Logs:**
   - Check specific application logs if services like VPNs are involved.

### Common Network Issues and Solutions

1. **No Network Interface Detected:**

   - **Check Hardware:** Ensure network card is present and recognized.
   - **Driver Issues:** Verify appropriate drivers are loaded.
     ```bash
     lspci -k | grep -A 3 -i network
     ```
   - **Module Loading:**
     ```bash
     sudo modprobe <driver_name>
     ```
   - **Explanation:** Ensures network hardware is properly recognized and drivers are loaded.

2. **Cannot Obtain IP Address via DHCP:**

   - **Restart DHCP Client:**
     ```bash
     sudo systemctl restart NetworkManager
     sudo dhclient -r
     sudo dhclient enp3s0
     ```
   - **Check DHCP Server:** Ensure DHCP server is operational.
   - **Explanation:** Resolves issues related to DHCP client or server.

3. **DNS Resolution Fails:**

   - **Check `/etc/resolv.conf`:** Ensure correct DNS servers are listed.
   - **Test DNS Servers:**
     ```bash
     dig @8.8.8.8 google.com
     ```
   - **Restart Resolver Service:**
     ```bash
     sudo systemctl restart systemd-resolved
     ```
   - **Explanation:** Addresses DNS configuration and resolver issues.

4. **Wireless Connection Drops:**

   - **Signal Strength:** Ensure strong Wi-Fi signal.
   - **Interference:** Reduce interference from other devices.
   - **Driver Updates:** Update wireless drivers.
   - **Explanation:** Improves wireless stability and reliability.

5. **Firewall Blocking Traffic:**
   - **Check Firewall Rules:**
     ```bash
     sudo ufw status verbose
     sudo firewall-cmd --list-all
     sudo iptables -L -v -n
     sudo nft list ruleset
     ```
   - **Adjust Rules:** Modify firewall settings to allow necessary traffic.
   - **Explanation:** Ensures firewall rules are not inadvertently blocking legitimate traffic.

### Useful Diagnostic Tools

1. **ping:** Test network connectivity.

   ```bash
   ping -c 4 <host>
   ```

   - **Explanation:** Sends ICMP echo requests to a host to check connectivity.

2. **traceroute:** Trace the path packets take to a host.

   ```bash
   traceroute google.com
   ```

   - **Explanation:** Shows each hop along the route to the destination, useful for identifying where delays occur.

3. **dig/nslookup:** DNS query tools.

   ```bash
   dig google.com
   nslookup google.com
   ```

   - **Explanation:** Queries DNS servers to resolve domain names to IP addresses.

4. **netstat/ss:** Display network connections, routing tables, interface statistics.

   ```bash
   sudo netstat -tulnp
   ss -tulnp
   ```

   - **Explanation:** Lists active network connections and listening ports.

5. **tcpdump:** Network packet analyzer.

   ```bash
   sudo tcpdump -i enp3s0
   ```

   - **Explanation:** Captures and displays network packets on the specified interface.

6. **nmap:** Network exploration and security auditing.

   ```bash
   nmap -sP 192.168.1.0/24
   ```

   - **Explanation:** Performs a ping scan to discover active hosts in the subnet.

7. **iwconfig/iw:** Wireless interface configuration and management.

   ```bash
   iwconfig
   sudo iw dev wlan0 link
   ```

   - **Explanation:** Displays wireless interface settings and connection status.

8. **ethtool:** Query and control network driver and hardware settings.

   ```bash
   sudo ethtool enp3s0
   ```

   - **Explanation:** Shows detailed information about the network interface.

9. **mtr:** Network diagnostic tool combining `ping` and `traceroute`.
   ```bash
   mtr google.com
   ```
   - **Explanation:** Provides a real-time view of the path packets take to reach a host, including latency and packet loss at each hop.

**Notes:**

- **Permissions:** Many diagnostic tools require elevated privileges (e.g., `sudo`).
- **Interpretation:** Understanding the output of these tools is crucial for effective troubleshooting.

---

## Practical Examples

This section provides step-by-step configurations for common networking tasks, demonstrating the use of various tools and methods.

### Example 1: Configuring a Static IP Address

**Objective:** Assign a static IP address to the Ethernet interface `enp3s0` using NetworkManager (`nmcli`).

**Steps:**

1. **Identify the Connection Name:**

   ```bash
   nmcli connection show
   ```

   _Assume the connection name is "Wired connection 1"._

2. **Set Static IP Configuration:**

   ```bash
   nmcli connection modify "Wired connection 1" ipv4.method manual
   nmcli connection modify "Wired connection 1" ipv4.addresses "192.168.1.100/24"
   nmcli connection modify "Wired connection 1" ipv4.gateway "192.168.1.1"
   nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8 8.8.4.4"
   ```

3. **Bring the Connection Up:**

   ```bash
   nmcli connection up "Wired connection 1"
   ```

4. **Verify Configuration:**
   ```bash
   ip addr show enp3s0
   ip route show
   cat /etc/resolv.conf
   ```

**Alternative Method Using Netplan:**

1. **Edit Netplan Configuration (`/etc/netplan/01-netcfg.yaml`):**

   ```yaml
   network:
     version: 2
     renderer: networkd
     ethernets:
       enp3s0:
         addresses: [192.168.1.100/24]
         gateway4: 192.168.1.1
         nameservers:
           addresses: [8.8.8.8, 8.8.4.4]
   ```

2. **Apply Configuration:**
   ```bash
   sudo netplan apply
   ```

**Notes:**

- Ensure no DHCP client is conflicting with static IP assignments.
- Restart NetworkManager if changes do not apply:
  ```bash
  sudo systemctl restart NetworkManager
  ```

### Example 2: Setting Up DHCP

**Objective:** Configure the Ethernet interface `enp3s0` to obtain an IP address via DHCP using systemd-networkd.

**Steps:**

1. **Create Network Configuration File (`/etc/systemd/network/10-dhcp.network`):**

   ```ini
   [Match]
   Name=enp3s0

   [Network]
   DHCP=ipv4
   ```

2. **Enable and Start systemd-networkd:**

   ```bash
   sudo systemctl enable systemd-networkd
   sudo systemctl start systemd-networkd
   ```

3. **Restart the Network Interface:**

   ```bash
   sudo ip link set enp3s0 down
   sudo ip link set enp3s0 up
   ```

4. **Verify IP Address:**
   ```bash
   ip addr show enp3s0
   ```

**Notes:**

- Ensure that the DHCP server on the network is operational.
- Check logs if DHCP fails:
  ```bash
  sudo journalctl -u systemd-networkd
  ```

### Example 3: Connecting to a Wi-Fi Network

**Objective:** Connect to the Wi-Fi network "HomeWiFi" with password "securepassword" using `nmcli`.

**Steps:**

1. **List Available Wi-Fi Networks:**

   ```bash
   nmcli device wifi list
   ```

   _Sample Output:_

   ```
   IN-USE  SSID           MODE   CHAN  RATE        SIGNAL  BARS  SECURITY
   *       HomeNetwork    Infra  6     54 Mbit/s   100     ▂▄▆█  WPA2
           GuestNetwork   Infra  11    54 Mbit/s   75      ▂▄▆_  WPA2
           OpenNetwork    Infra  1     54 Mbit/s   50      ▂▄__  --
   ```

2. **Connect to "HomeNetwork":**

   ```bash
   nmcli device wifi connect "HomeNetwork" password "securepassword"
   ```

3. **Verify Connection:**
   ```bash
   nmcli device status
   ping -c 4 google.com
   ```

**Alternative Method Using `wpa_supplicant`:**

1. **Create `wpa_supplicant` Configuration:**

   ```bash
   sudo wpa_passphrase "HomeWiFi" "securepassword" | sudo tee /etc/wpa_supplicant/wpa_supplicant.conf
   ```

2. **Start `wpa_supplicant`:**

   ```bash
   sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
   ```

3. **Obtain IP Address via DHCP:**

   ```bash
   sudo dhclient wlan0
   ```

4. **Verify Connection:**
   ```bash
   iwconfig wlan0
   ping -c 4 google.com
   ```

**Notes:**

- Ensure the wireless interface `wlan0` is managed by NetworkManager or not managed if using `wpa_supplicant`.
- Check wireless driver and firmware if connection fails.

### Example 4: Creating a Wi-Fi Hotspot

**Objective:** Create a Wi-Fi hotspot named "MyHotspot" with password "hotspotpass" using NetworkManager (`nmcli`).

**Steps:**

1. **Bring Up the Wi-Fi Interface:**

   ```bash
   nmcli device set wlan0 managed yes
   nmcli device connect wlan0
   ```

2. **Create and Activate Hotspot:**

   ```bash
   nmcli device wifi hotspot ifname wlan0 ssid MyHotspot password "hotspotpass"
   ```

3. **Verify Hotspot Status:**
   - Other devices should detect "MyHotspot" and connect using the provided password.
   - Use `nmcli` to check the hotspot status:
     ```bash
     nmcli connection show --active
     ```

**Notes:**

- **Internet Sharing:** Ensure that the host system has an active internet connection and proper routing/NAT is configured if sharing internet.
- **Firewall Rules:** Adjust firewall settings to allow traffic through the hotspot.

### Example 5: Configuring Network Bonding

**Objective:** Create a bonded interface `bond0` combining `enp3s0` and `enp3s1` for increased bandwidth and redundancy using `systemd-networkd`.

**Steps:**

1. **Load Bonding Module:**

   ```bash
   sudo modprobe bonding
   ```

2. **Create Bond Netdev Configuration (`/etc/systemd/network/50-bond0.netdev`):**

   ```ini
   [NetDev]
   Name=bond0
   Kind=bond

   [Bond]
   Mode=802.3ad
   MIIMonitorSec=100ms
   ```

3. **Create Bond Network Configuration (`/etc/systemd/network/50-bond0.network`):**

   ```ini
   [Match]
   Name=bond0

   [Network]
   Address=192.168.1.100/24
   Gateway=192.168.1.1
   DNS=8.8.8.8 8.8.4.4
   ```

4. **Create Slave Interface Configuration for `enp3s0` (`/etc/systemd/network/50-enp3s0.network`):**

   ```ini
   [Match]
   Name=enp3s0

   [Network]
   Bond=bond0
   ```

5. **Create Slave Interface Configuration for `enp3s1` (`/etc/systemd/network/50-enp3s1.network`):**

   ```ini
   [Match]
   Name=enp3s1

   [Network]
   Bond=bond0
   ```

6. **Enable and Start systemd-networkd:**

   ```bash
   sudo systemctl enable systemd-networkd
   sudo systemctl start systemd-networkd
   ```

7. **Verify Bonding Configuration:**

   ```bash
   cat /proc/net/bonding/bond0
   ```

   _Sample Output:_

   ```
   Bonding Mode: IEEE 802.3ad Dynamic link aggregation
   MII Status: up
   MII Polling Interval (ms): 100
   Up Delay (ms): 0
   Down Delay (ms): 0

   Slave Interface: enp3s0
   MII Status: up
   ...

   Slave Interface: enp3s1
   MII Status: up
   ...
   ```

**Notes:**

- **Switch Configuration:** Ensure the network switch supports LACP (if using mode 802.3ad).
- **Monitoring:** Use `/proc/net/bonding/bond0` to monitor bond status and link states.

### Example 6: Setting Up a Network Bridge

**Objective:** Create a network bridge `br0` connecting `enp3s0` for virtual machine networking using NetworkManager.

**Steps:**

1. **Create Bridge Connection:**

   ```bash
   nmcli connection add type bridge ifname br0 con-name br0
   ```

   - **Explanation:** Creates a new bridge named `br0`.

2. **Add Ethernet Interface to Bridge:**

   ```bash
   nmcli connection add type bridge-slave ifname enp3s0 master br0
   ```

   - **Explanation:** Adds `enp3s0` as a slave to the `br0` bridge.

3. **Assign IP to Bridge:**

   ```bash
   nmcli connection modify br0 ipv4.method manual ipv4.addresses "192.168.1.100/24" ipv4.gateway "192.168.1.1" ipv4.dns "8.8.8.8 8.8.4.4"
   nmcli connection up br0
   ```

   - **Explanation:** Sets a static IP for the bridge and activates it.

4. **Verify Bridge Configuration:**
   ```bash
   bridge link
   nmcli connection show br0
   ```
   - **Explanation:** Confirms that `br0` is active and correctly configured.

**Notes:**

- **Use Cases:** Virtual machines, container networking.
- **Alternatives:** Use NAT with virtual network interfaces if bridging Wi-Fi is not feasible.

### Example 7: Setting Up a VPN Connection

**Objective:** Configure an OpenVPN connection named "MyVPN" using NetworkManager (`nmcli`).

**Steps:**

1. **Install OpenVPN Plugin for NetworkManager:**

   ```bash
   sudo apt install network-manager-openvpn network-manager-openvpn-gnome
   ```

   - **Explanation:** Installs OpenVPN support for NetworkManager.

2. **Obtain OpenVPN Configuration File (`myvpn.ovpn`).**

3. **Import OpenVPN Configuration:**

   ```bash
   nmcli connection import type openvpn file /path/to/myvpn.ovpn
   ```

   - **Explanation:** Imports the OpenVPN configuration into NetworkManager.

4. **List Connections to Confirm Import:**

   ```bash
   nmcli connection show
   ```

   _Sample Output:_

   ```
   NAME                UUID                                  TYPE      DEVICE
   MyVPN               123e4567-e89b-12d3-a456-426614174001  vpn       --
   ```

5. **Activate the VPN Connection:**

   ```bash
   nmcli connection up "MyVPN"
   ```

   - **Explanation:** Starts the OpenVPN connection named `MyVPN`.

6. **Verify VPN Connection:**
   ```bash
   nmcli connection show --active
   ip addr show tun0
   ping -c 4 google.com
   ```
   - **Explanation:** Confirms that the VPN is active and routing traffic correctly.

**Alternative Method Using GUI:**

- **NetworkManager GUI:** Use the network settings interface in your desktop environment to import and manage VPN connections.

**Notes:**

- **Authentication:** May require additional credentials or certificates.
- **DNS Leak Prevention:** Ensure DNS queries are routed through the VPN.
- **Firewall Rules:** Adjust firewall settings to allow VPN traffic.

---

## Demos

This section provides detailed demonstrations of configuring various network scenarios in Linux, showcasing practical applications of the concepts discussed.

### Demo 1: Configuring a Static IP

**Objective:** Assign a static IP address to the Ethernet interface `enp3s0` using `nmcli`.

**Steps:**

1. **Identify the Connection Name:**

   ```bash
   nmcli connection show
   ```

   _Output:_

   ```
   NAME                UUID                                  TYPE      DEVICE
   Wired connection 1  123e4567-e89b-12d3-a456-426614174000  ethernet  enp3s0
   ```

2. **Set Static IP Configuration:**

   ```bash
   nmcli connection modify "Wired connection 1" ipv4.method manual
   nmcli connection modify "Wired connection 1" ipv4.addresses "192.168.1.100/24"
   nmcli connection modify "Wired connection 1" ipv4.gateway "192.168.1.1"
   nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8 8.8.4.4"
   ```

3. **Bring the Connection Up:**

   ```bash
   nmcli connection up "Wired connection 1"
   ```

4. **Verify Configuration:**
   ```bash
   ip addr show enp3s0
   ip route show
   cat /etc/resolv.conf
   ```
   _Expected Output:_
   - **`ip addr show enp3s0`:** Displays `192.168.1.100/24` assigned to `enp3s0`.
   - **`ip route show`:** Shows default route via `192.168.1.1`.
   - **`cat /etc/resolv.conf`:** Lists DNS servers `8.8.8.8` and `8.8.4.4`.

**Notes:**

- Ensure no DHCP client is conflicting with static IP assignments.
- Restart NetworkManager if changes do not apply:
  ```bash
  sudo systemctl restart NetworkManager
  ```

### Demo 2: Connecting to a Wi-Fi Network

**Objective:** Connect to the Wi-Fi network "HomeNetwork" with password "securepassword" using `nmcli`.

**Steps:**

1. **List Available Wi-Fi Networks:**

   ```bash
   nmcli device wifi list
   ```

   _Sample Output:_

   ```
   IN-USE  SSID           MODE   CHAN  RATE        SIGNAL  BARS  SECURITY
   *       HomeNetwork    Infra  6     54 Mbit/s   100     ▂▄▆█  WPA2
           GuestNetwork   Infra  11    54 Mbit/s   75      ▂▄▆_  WPA2
           OpenNetwork    Infra  1     54 Mbit/s   50      ▂▄__  --
   ```

2. **Connect to "HomeNetwork":**

   ```bash
   nmcli device wifi connect "HomeNetwork" password "securepassword"
   ```

3. **Verify Connection:**
   ```bash
   nmcli device status
   ping -c 4 google.com
   ```
   _Expected Output:_
   - **`nmcli device status`:** Shows `wlan0` as `connected`.
   - **`ping -c 4 google.com`:** Successful ping responses.

**Notes:**

- **Security:** Ensure correct password to avoid failed connection attempts.
- **Troubleshooting:** If connection fails, check Wi-Fi adapter status and logs.

### Demo 3: Creating a Wi-Fi Hotspot

**Objective:** Create a Wi-Fi hotspot named "MyHotspot" with password "hotspotpass" using `nmcli`.

**Steps:**

1. **Ensure Wi-Fi Interface is Managed by NetworkManager:**

   ```bash
   nmcli device set wlan0 managed yes
   nmcli device connect wlan0
   ```

2. **Create and Activate Hotspot:**

   ```bash
   nmcli device wifi hotspot ifname wlan0 ssid MyHotspot password "hotspotpass"
   ```

3. **Verify Hotspot Status:**

   - Other devices should detect "MyHotspot" and connect using the provided password.
   - Use `nmcli` to check the hotspot status:
     ```bash
     nmcli connection show --active
     ```
     _Sample Output:_
     ```
     NAME        UUID                                  TYPE      DEVICE
     MyHotspot   abcdef12-3456-7890-abcd-ef1234567890  wifi      wlan0
     ```

4. **Connect a Device to the Hotspot:**

   - Use another device (e.g., smartphone) to search for "MyHotspot" and connect using the password "hotspotpass".

5. **Test Connectivity from Hotspot Device:**
   ```bash
   ping -c 4 google.com
   ```
   - **Explanation:** Ensures that the hotspot device has internet access through the host.

**Notes:**

- **Internet Sharing:** Ensure that the host system has an active internet connection and proper routing/NAT is configured if sharing internet.
- **Firewall Rules:** Adjust firewall settings to allow traffic through the hotspot.

### Demo 4: Configuring Network Bonding

**Objective:** Create a bonded interface `bond0` combining `enp3s0` and `enp3s1` for increased bandwidth and redundancy using `systemd-networkd`.

**Steps:**

1. **Load Bonding Module:**

   ```bash
   sudo modprobe bonding
   ```

2. **Create Bond Netdev Configuration (`/etc/systemd/network/50-bond0.netdev`):**

   ```ini
   [NetDev]
   Name=bond0
   Kind=bond

   [Bond]
   Mode=802.3ad
   MIIMonitorSec=100ms
   ```

3. **Create Bond Network Configuration (`/etc/systemd/network/50-bond0.network`):**

   ```ini
   [Match]
   Name=bond0

   [Network]
   Address=192.168.1.100/24
   Gateway=192.168.1.1
   DNS=8.8.8.8 8.8.4.4
   ```

4. **Create Slave Interface Configuration for `enp3s0` (`/etc/systemd/network/50-enp3s0.network`):**

   ```ini
   [Match]
   Name=enp3s0

   [Network]
   Bond=bond0
   ```

5. **Create Slave Interface Configuration for `enp3s1` (`/etc/systemd/network/50-enp3s1.network`):**

   ```ini
   [Match]
   Name=enp3s1

   [Network]
   Bond=bond0
   ```

6. **Enable and Start systemd-networkd:**

   ```bash
   sudo systemctl enable systemd-networkd
   sudo systemctl start systemd-networkd
   ```

7. **Verify Bonding Configuration:**

   ```bash
   cat /proc/net/bonding/bond0
   ```

   _Sample Output:_

   ```
   Bonding Mode: IEEE 802.3ad Dynamic link aggregation
   MII Status: up
   MII Polling Interval (ms): 100
   Up Delay (ms): 0
   Down Delay (ms): 0

   Slave Interface: enp3s0
   MII Status: up
   ...

   Slave Interface: enp3s1
   MII Status: up
   ...
   ```

**Notes:**

- **Switch Configuration:** Ensure the network switch supports LACP (if using mode 802.3ad).
- **Monitoring:** Use `/proc/net/bonding/bond0` to monitor bond status and link states.

### Demo 5: Setting Up a VPN Connection

**Objective:** Configure an OpenVPN connection named "MyVPN" using NetworkManager (`nmcli`).

**Steps:**

1. **Install OpenVPN and NetworkManager Plugin:**

   ```bash
   sudo apt update
   sudo apt install openvpn network-manager-openvpn network-manager-openvpn-gnome
   ```

   - **Explanation:** Installs OpenVPN and its NetworkManager plugin.

2. **Obtain OpenVPN Configuration File (`myvpn.ovpn`).**

3. **Import OpenVPN Configuration:**

   ```bash
   nmcli connection import type openvpn file /path/to/myvpn.ovpn
   ```

   - **Explanation:** Imports the OpenVPN configuration into NetworkManager.

4. **List Connections to Confirm Import:**

   ```bash
   nmcli connection show
   ```

   _Sample Output:_

   ```
   NAME                UUID                                  TYPE      DEVICE
   MyVPN               123e4567-e89b-12d3-a456-426614174001  vpn       --
   ```

5. **Activate the VPN Connection:**

   ```bash
   nmcli connection up "MyVPN"
   ```

   - **Explanation:** Starts the OpenVPN connection named `MyVPN`.

6. **Verify VPN Connection:**
   ```bash
   nmcli connection show --active
   ip addr show tun0
   ping -c 4 google.com
   ```
   _Expected Output:_
   - **`nmcli connection show --active`:** Shows `MyVPN` as active.
   - **`ip addr show tun0`:** Displays the VPN interface with an assigned IP.
   - **`ping -c 4 google.com`:** Successful ping responses routed through the VPN.

**Alternative Method Using GUI:**

- **NetworkManager GUI:** Use the network settings interface in your desktop environment to import and manage VPN connections.

**Notes:**

- **Authentication:** May require additional credentials or certificates.
- **DNS Leak Prevention:** Ensure DNS queries are routed through the VPN.
- **Firewall Rules:** Adjust firewall settings to allow VPN traffic.

---

## Best Practices

Adhering to best practices in network management ensures secure, efficient, and reliable network operations.

### Security Considerations

1. **Use Strong Authentication:**

   - Utilize strong passwords and encryption methods (WPA2/WPA3 for Wi-Fi, robust VPN protocols).

2. **Restrict Network Access:**

   - Implement firewalls to control incoming and outgoing traffic.
   - Use VLANs and network segmentation to limit access to sensitive areas.

3. **Regular Updates:**

   - Keep network management tools and firmware updated to patch vulnerabilities.

4. **Monitor Network Activity:**

   - Use monitoring tools (e.g., `tcpdump`, `wireshark`, `netstat`) to detect suspicious activities.

5. **Secure Configuration Files:**
   - Protect configuration files containing sensitive information (e.g., passwords) with appropriate permissions.

### Managing Multiple Network Connections

1. **Consistent Naming:**

   - Use predictable interface names to avoid confusion.

2. **Profiles Management:**

   - Utilize NetworkManager’s connection profiles to manage different network setups.

3. **Automated Switching:**

   - Configure NetworkManager to automatically switch to the best available connection.

4. **Documentation:**
   - Maintain clear documentation of network configurations and connections.

### Performance Optimizations

1. **Bandwidth Management:**

   - Implement QoS to prioritize critical traffic.
   - Monitor network usage to identify bottlenecks.

2. **Reduce Latency:**

   - Optimize routing tables for efficient packet delivery.
   - Use lower-latency protocols where appropriate.

3. **Load Balancing:**

   - Utilize bonding or multiple connections to distribute network traffic.

4. **Caching:**
   - Implement DNS caching to reduce resolution times.

### Documentation and Change Management

1. **Maintain Configuration Files:**

   - Keep backups of network configuration files.
   - Use version control systems (e.g., Git) for tracking changes.

2. **Change Logs:**

   - Document changes made to network settings, including reasons and dates.

3. **Standardization:**

   - Establish standard procedures and configurations across systems.

4. **Training:**
   - Ensure team members are knowledgeable about network management tools and practices.

---

## Conclusion

Network management in Linux is a multifaceted discipline encompassing a wide range of tools, configurations, and best practices. From basic interface management to advanced configurations like bonding and VPNs, mastering these concepts ensures robust and secure network operations.

This comprehensive guide has provided in-depth insights, practical examples, and demonstrations to equip instructors and learners with the knowledge necessary to navigate and manage Linux networks effectively. Continuous learning and staying updated with evolving networking technologies will further enhance your network management capabilities.

---

## Further Resources

1. **Official Documentation:**

   - [NetworkManager Documentation](https://developer.gnome.org/NetworkManager/stable/)
   - [systemd-networkd Manual](https://www.freedesktop.org/software/systemd/man/systemd.network.html)
   - [Netplan Documentation](https://netplan.io/)
   - [wpa_supplicant Documentation](https://w1.fi/wpa_supplicant/)
   - [iptables Documentation](https://netfilter.org/documentation/)
   - [nftables Documentation](https://wiki.nftables.org/wiki-nftables/index.php/Main_Page)

2. **Books:**

   - _Linux Networking Cookbook_ by Carla Schroder.
   - _UNIX and Linux System Administration Handbook_ by Evi Nemeth et al.

3. **Online Guides and Tutorials:**

   - [Arch Linux Network Configuration](https://wiki.archlinux.org/title/Network_configuration)
   - [Ubuntu Networking Guide](https://help.ubuntu.com/community/NetworkConfigurationCommandLine)
   - [DigitalOcean Networking Tutorials](https://www.digitalocean.com/community/tags/networking)

4. **Community Forums and Q&A:**

   - [Stack Overflow](https://stackoverflow.com/questions/tagged/linux-networking)
   - [Ask Ubuntu](https://askubuntu.com/questions/tagged/network)
   - [LinuxQuestions.org](https://www.linuxquestions.org/questions/linux-networking-3/)

5. **Tools Documentation:**

   - [iptables](https://netfilter.org/documentation/)
   - [nftables](https://wiki.nftables.org/wiki-nftables/index.php/Main_Page)
   - [tc (Traffic Control)](https://www.kernel.org/doc/Documentation/networking/tc.txt)

6. **Security Best Practices:**

   - [CIS Benchmarks for Linux](https://www.cisecurity.org/cis-benchmarks/)
   - [OWASP Network Security Resources](https://owasp.org/www-project-cheat-sheets/cheatsheets/Network_Security_Cheat_Sheet.html)

7. **Blogs and Articles:**

   - [Red Hat Networking Articles](https://www.redhat.com/en/topics/networking)
   - [Linux Journal Networking Section](https://www.linuxjournal.com/category/networking)

8. **Videos and Webinars:**
   - [Linux Foundation Training](https://training.linuxfoundation.org/)
   - [YouTube Channels: LearnLinuxTV, NetworkChuck](https://www.youtube.com/)

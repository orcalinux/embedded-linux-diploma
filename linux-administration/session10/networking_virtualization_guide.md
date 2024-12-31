# Networking, Virtualization, and Routing Guide with QEMU, TAP/TUN, and Bridge Configurations

## Overview

This guide covers the essential aspects of networking, including different topologies, networking layers, IP addressing, virtual networking devices, and practical demonstrations using various scripts and tools. It is designed to provide a thorough understanding of these concepts, making it suitable for both beginners and advanced users.

## Table of Contents

- [Networking, Virtualization, and Routing Guide with QEMU, TAP/TUN, and Bridge Configurations](#networking-virtualization-and-routing-guide-with-qemu-taptun-and-bridge-configurations)
  - [Overview](#overview)
  - [Table of Contents](#table-of-contents)
  - [Networking Topologies](#networking-topologies)
    - [Bus Topology](#bus-topology)
    - [Star Topology](#star-topology)
    - [Mesh Topology](#mesh-topology)
    - [Wireless Topology](#wireless-topology)
  - [Networking Layers](#networking-layers)
    - [OSI Model Layers](#osi-model-layers)
    - [Detailed Explanation of the Start Script](#detailed-explanation-of-the-start-script)
      - [1. Application Layer](#1-application-layer)
      - [2. Presentation Layer](#2-presentation-layer)
      - [3. Session Layer](#3-session-layer)
      - [4. Transport Layer](#4-transport-layer)
      - [5. Network Layer](#5-network-layer)
      - [6. Data Link Layer](#6-data-link-layer)
      - [7. Physical Layer](#7-physical-layer)
  - [MAC and IP Address Resolution](#mac-and-ip-address-resolution)
    - [MAC Address](#mac-address)
    - [IP Address](#ip-address)
    - [ARP Process in Detail](#arp-process-in-detail)
    - [Communicating with a Device on a Different Network](#communicating-with-a-device-on-a-different-network)
    - [Default Router in Linux](#default-router-in-linux)
  - [Ethernet Packets and Ethernet Explanation](#ethernet-packets-and-ethernet-explanation)
    - [What is Ethernet?](#what-is-ethernet)
    - [Ethernet Frame Structure](#ethernet-frame-structure)
    - [Ethernet Frame Format](#ethernet-frame-format)
    - [Ethernet Operation](#ethernet-operation)
    - [Example Ethernet Frame](#example-ethernet-frame)
    - [Ethernet Transmission Process](#ethernet-transmission-process)
    - [Advantages and Disadvantages of Ethernet](#advantages-and-disadvantages-of-ethernet)
    - [Practical Commands for Ethernet](#practical-commands-for-ethernet)
  - [IP Addressing and Subnetting](#ip-addressing-and-subnetting)
    - [IPv4 Addressing](#ipv4-addressing)
      - [IP Address Format](#ip-address-format)
      - [IPv4 Classes](#ipv4-classes)
    - [Subnetting and Netmask](#subnetting-and-netmask)
      - [Subnet Mask](#subnet-mask)
      - [CIDR Notation](#cidr-notation)
      - [Numerical Example for Subnetting](#numerical-example-for-subnetting)
    - [IPv4 Header Format](#ipv4-header-format)
    - [Practical Commands for IPv4](#practical-commands-for-ipv4)
    - [Routing and Default Gateway](#routing-and-default-gateway)
    - [ARP and ICMP](#arp-and-icmp)
    - [ARP (Address Resolution Protocol) Overview](#arp-address-resolution-protocol-overview)
      - [Types of Casts (for ARP and ICMP)](#types-of-casts-for-arp-and-icmp)
    - [ARP Packet](#arp-packet)
    - [ICMP (Internet Control Message Protocol) Overview](#icmp-internet-control-message-protocol-overview)
    - [ICMP Packet](#icmp-packet)
    - [ARP vs ICMP – Key Differences](#arp-vs-icmp--key-differences)
  - [IPv6 Addressing](#ipv6-addressing)
    - [IPv6 Address Format](#ipv6-address-format)
    - [IPv6 Features](#ipv6-features)
    - [Example Address](#example-address)
    - [Subnetting in IPv6](#subnetting-in-ipv6)
    - [Transition from IPv4 to IPv6](#transition-from-ipv4-to-ipv6)
    - [Practical Usage](#practical-usage)
    - [Address Types](#address-types)
  - [ICMP Packets](#icmp-packets)
    - [ICMP (Internet Control Message Protocol)](#icmp-internet-control-message-protocol)
    - [ICMP Packet Structure](#icmp-packet-structure)
    - [Example](#example)
  - [ARP Packets](#arp-packets)
    - [ARP (Address Resolution Protocol)](#arp-address-resolution-protocol)
    - [ARP Process](#arp-process)
    - [Packet Structure](#packet-structure)
    - [Example of ARP Communication](#example-of-arp-communication)
  - [Virtual Network Devices](#virtual-network-devices)
    - [TUN and TAP Devices](#tun-and-tap-devices)
    - [Creating and Managing TAP/TUN Devices](#creating-and-managing-taptun-devices)
      - [Create a TAP Device](#create-a-tap-device)
      - [Create a TUN Device](#create-a-tun-device)
    - [Practical Commands for Managing TUN/TAP Devices](#practical-commands-for-managing-tuntap-devices)
      - [View TUN/TAP Devices](#view-tuntap-devices)
      - [Set IP Address for TAP Device](#set-ip-address-for-tap-device)
      - [Set IP Address for TUN Device](#set-ip-address-for-tun-device)
      - [Bring Down a TAP/TUN Device](#bring-down-a-taptun-device)
      - [Delete a TAP/TUN Device](#delete-a-taptun-device)
      - [Create a TAP Device with Specific MAC Address](#create-a-tap-device-with-specific-mac-address)
      - [Create a TUN Device with Specific MTU](#create-a-tun-device-with-specific-mtu)
      - [Create a TAP Device with User Ownership](#create-a-tap-device-with-user-ownership)
    - [Example Usage Scenarios](#example-usage-scenarios)
      - [Bridging TAP Devices](#bridging-tap-devices)
      - [Configuring TUN Device for VPN](#configuring-tun-device-for-vpn)
      - [Configuring TAP Device for Virtual Machine Networking](#configuring-tap-device-for-virtual-machine-networking)
    - [Additional Commands and Configurations](#additional-commands-and-configurations)
      - [Change the Name of a TUN/TAP Device](#change-the-name-of-a-tuntap-device)
      - [Set a Description for a TUN/TAP Device](#set-a-description-for-a-tuntap-device)
      - [Monitor TUN/TAP Device Traffic](#monitor-tuntap-device-traffic)
      - [Adjusting MTU](#adjusting-mtu)
  - [VirtIO and Virtual Machines](#virtio-and-virtual-machines)
    - [Virtual Machines](#virtual-machines)
    - [KVM (Kernel-based Virtual Machine)](#kvm-kernel-based-virtual-machine)
    - [QEMU (Quick Emulator)](#qemu-quick-emulator)
    - [Relationship between KVM and QEMU](#relationship-between-kvm-and-qemu)
    - [How They Work Together](#how-they-work-together)
    - [Example Workflow](#example-workflow)
    - [Example Command to Run a VM with QEMU and KVM](#example-command-to-run-a-vm-with-qemu-and-kvm)
    - [VirtIO](#virtio)
      - [Advantages of VirtIO](#advantages-of-virtio)
    - [VirtIO Network Device (virtio-net)](#virtio-network-device-virtio-net)
      - [How VirtIO Emulates the Network Interface Card (NIC)](#how-virtio-emulates-the-network-interface-card-nic)
      - [Key Components of VirtIO-net](#key-components-of-virtio-net)
    - [Virtual Machines and their Relationships](#virtual-machines-and-their-relationships)
    - [Running Virtual Machines with QEMU](#running-virtual-machines-with-qemu)
      - [Example Command to Run a VM with QEMU and VirtIO](#example-command-to-run-a-vm-with-qemu-and-virtio)
      - [Explanation of the Command](#explanation-of-the-command)
    - [Detailed Steps to Set Up VirtIO Network with QEMU](#detailed-steps-to-set-up-virtio-network-with-qemu)
    - [Monitoring and Managing VirtIO Devices](#monitoring-and-managing-virtio-devices)
      - [Check VirtIO Devices in the Guest](#check-virtio-devices-in-the-guest)
    - [Advanced Configuration and Optimization](#advanced-configuration-and-optimization)
      - [Enable Multiqueue for VirtIO-net](#enable-multiqueue-for-virtio-net)
      - [Enable Offloading Features](#enable-offloading-features)
      - [Configure NUMA for Better Performance](#configure-numa-for-better-performance)
    - [Relationships Between Virtual Machines](#relationships-between-virtual-machines)
  - [Static Routing and Bridging](#static-routing-and-bridging)
    - [Static Routing](#static-routing)
      - [How Static Routing Works](#how-static-routing-works)
      - [Adding a Static Route](#adding-a-static-route)
      - [Viewing the Routing Table](#viewing-the-routing-table)
      - [Deleting a Static Route](#deleting-a-static-route)
    - [Bridging](#bridging)
      - [How Bridging Works](#how-bridging-works)
      - [Creating a Network Bridge](#creating-a-network-bridge)
      - [Adding Interfaces to the Bridge](#adding-interfaces-to-the-bridge)
      - [Practical Examples](#practical-examples)
        - [Adding a Static Route Example](#adding-a-static-route-example)
        - [Creating a Bridge](#creating-a-bridge)
        - [Adding Interfaces to the Bridge (Example 1)](#adding-interfaces-to-the-bridge-example-1)
      - [Additional Commands and Configurations for TUN/TAP Devices](#additional-commands-and-configurations-for-tuntap-devices)
        - [View Bridge Details](#view-bridge-details)
        - [Remove Interface from Bridge](#remove-interface-from-bridge)
        - [Delete a Bridge](#delete-a-bridge)
        - [Persisting Static Routes and Bridge Configurations](#persisting-static-routes-and-bridge-configurations)
        - [Example for Debian-based Systems](#example-for-debian-based-systems)
  - [Practical Implementation](#practical-implementation)
    - [1. Important Notes](#1-important-notes)
    - [2. Machine Configurations](#2-machine-configurations)
      - [In Case of Two Machines](#in-case-of-two-machines)
      - [In Case of Three Machines](#in-case-of-three-machines)
    - [3. About the `/etc/network/interfaces` File](#3-about-the-etcnetworkinterfaces-file)
    - [4. Manual vs. `iproute2` or `net-tools`](#4-manual-vs-iproute2-or-net-tools)
      - [Manual Configuration](#manual-configuration)
      - [Using `iproute2`](#using-iproute2)
      - [Using `net-tools`](#using-net-tools)
    - [5. Start Script for Two Machines](#5-start-script-for-two-machines)
      - [Start Script](#start-script)
      - [Explanation of the Start Script Command](#explanation-of-the-start-script-command)
    - [6. Cleanup Script for Two Machines](#6-cleanup-script-for-two-machines)
      - [Cleanup Script](#cleanup-script)
      - [Explanation of the Cleanup Script](#explanation-of-the-cleanup-script)
    - [7. Start Script for Three Machines](#7-start-script-for-three-machines)
      - [Start Script](#start-script-1)
      - [Explanation](#explanation)
    - [8. Cleanup Script for Three Machines](#8-cleanup-script-for-three-machines)
      - [Script](#script)
      - [Explanation](#explanation-1)
    - [Enabling IP Forwarding on the Router (rt2)](#enabling-ip-forwarding-on-the-router-rt2)
      - [Enabling IP Forwarding on the Router](#enabling-ip-forwarding-on-the-router)
  - [Resources](#resources)

---

## Networking Topologies

### Bus Topology

-   A single central cable (the bus) to which all network devices are connected.
-   **Advantages**: Simple, easy to implement.
-   **Disadvantages**: Limited cable length, difficult to troubleshoot.

### Star Topology

-   All network devices are connected to a central hub or switch.
-   **Advantages**: Easy to manage, scalable.
-   **Disadvantages**: Single point of failure (the hub/switch).

### Mesh Topology

-   Devices are interconnected, allowing for multiple paths for data to travel.
-   **Advantages**: High redundancy, reliable.
-   **Disadvantages**: Expensive, complex setup.

### Wireless Topology

-   Devices are connected using wireless signals.
-   **Advantages**: Mobility, easy to set up.
-   **Disadvantages**: Limited range, potential interference.

---

## Networking Layers

### OSI Model Layers

1. **Application Layer**
2. **Presentation Layer**
3. **Session Layer**
4. **Transport Layer**
5. **Network Layer**
6. **Data Link Layer**
7. **Physical Layer**

### Detailed Explanation of the Start Script

#### 1. Application Layer

-   **Function**: Interfaces directly with end-user applications, providing network services.
-   **Protocols**: HTTP, FTP, SMTP, DNS, Telnet, SSH
-   **Examples**:
    -   **HTTP**: Used by web browsers to fetch web pages from web servers.
    -   **FTP**: Used to transfer files between computers on a network.
    -   **SMTP**: Used for sending emails.
-   **Types**:
    -   **Web Protocols**: HTTP, HTTPS
    -   **File Transfer Protocols**: FTP, TFTP
    -   **Email Protocols**: SMTP, IMAP, POP3
    -   **Directory Services**: LDAP
    -   **Remote Access Protocols**: Telnet, SSH

#### 2. Presentation Layer

-   **Function**: Responsible for data translation, encryption, and compression.
-   **Examples**:
    -   **Data Translation**: Converts data formats like EBCDIC to ASCII.
    -   **Encryption**: SSL/TLS protocols used to secure data transmission over the internet.
    -   **Compression**: Reduces the number of bits that need to be transmitted on the network.
-   **Types**:
    -   **Data Formats**: JPEG, GIF, TIFF
    -   **Encryption**: SSL/TLS, Kerberos
    -   **Compression**: MPEG, GIF

#### 3. Session Layer

-   **Function**: Manages sessions between applications. It establishes, manages, and terminates connections between applications.
-   **Examples**:
    -   **Session Management**: In web conferencing, it manages the session to ensure all participants can communicate in real-time.
    -   **Synchronization**: In a file transfer, it ensures the file transfer can be resumed from the same point if the connection drops.
-   **Types**:
    -   **Session Management**: NetBIOS
    -   **Dialog Control**: RPC (Remote Procedure Call)
    -   **Synchronization**: PPTP (Point-to-Point Tunneling Protocol)

#### 4. Transport Layer

-   **Function**: Ensures reliable data transfer with error correction and flow control. It segments and reassembles data into a data stream.
-   **Protocols**: TCP, UDP
-   **Examples**:
    -   **TCP**: Ensures reliable, ordered, and error-checked delivery of a stream of data between applications.
    -   **UDP**: Provides a simpler, connectionless communication model with minimal protocol mechanism.
-   **Types**:
    -   **Connection-Oriented**: TCP (Transmission Control Protocol)
    -   **Connectionless**: UDP (User Datagram Protocol)
    -   **Message-Oriented**: SCTP (Stream Control Transmission Protocol)

#### 5. Network Layer

-   **Function**: Handles logical addressing and routing. It determines the best path to move data from source to destination.
-   **Protocols**: IP, ICMP, IGMP
-   **Examples**:
    -   **IP**: Responsible for addressing and routing packets of data so they can travel across networks and arrive at the correct destination.
    -   **ICMP**: Used for diagnostic purposes like the ping command to test connectivity between hosts.
-   **Types**:
    -   **Routing Protocols**: OSPF (Open Shortest Path First), BGP (Border Gateway Protocol)
    -   **Addressing Protocols**: IPv4, IPv6
    -   **Messaging Protocols**: ICMP (Internet Control Message Protocol)
    -   **Multicast Protocols**: IGMP (Internet Group Management Protocol)

#### 6. Data Link Layer

-   **Function**: Manages physical addressing and error detection. It ensures that data transferred is free from errors.
-   **Protocols**: Ethernet, PPP, Switches, Bridges
-   **Examples**:
    -   **Ethernet**: Defines wiring and signaling standards for the physical layer, as well as data packet formats and protocols for the data link layer.
    -   **MAC Addressing**: Provides unique identifiers assigned to network interfaces for communications on the physical network segment.
-   **Types**:
    -   **LLC (Logical Link Control)**: Manages frames to identify network layer protocols.
    -   **MAC (Media Access Control)**: Manages protocols for accessing the physical medium.
    -   **Error Detection**: CRC (Cyclic Redundancy Check)

#### 7. Physical Layer

-   **Function**: Deals with the physical connection between devices. It transmits raw bitstreams over a physical medium.
-   **Components**: Cables, switches, hubs, network adapters
-   **Examples**:
    -   **Cables**: Coaxial, optical fiber, and twisted pair cables.
    -   **Physical Transmission**: The actual hardware that transmits the raw data bits over the network medium, such as Ethernet cables or fiber optics.
-   **Types**:
    -   **Transmission Media**: Copper cables, fiber optic cables, wireless
    -   **Hardware Devices**: Hubs, repeaters, network adapters
    -   **Signaling**: Electrical signals, light signals

---

## MAC and IP Address Resolution

### MAC Address

-   A unique identifier assigned to network interfaces for communications at the data link layer.
-   Format: 48-bit address, usually written as six groups of two hexadecimal digits separated by colons.

### IP Address

-   A numerical label assigned to each device connected to a computer network that uses the Internet Protocol for communication.

### ARP Process in Detail

1. **Device A wants to communicate with Device B** within the same network.
2. **Device A broadcasts an ARP request** to all devices on the local network: "Who has IP address 192.168.1.2? Tell 192.168.1.1."
3. **Device B receives the ARP request** and replies with its MAC address: "192.168.1.2 is at MAC address 00:14:22:01:23:45."
4. **Device A stores the MAC address** in its ARP cache and uses it to send packets directly to Device B.

### Communicating with a Device on a Different Network

1. **Device A wants to communicate with Device B** on a different network.
2. **Device A checks its routing table** and finds the route to the default gateway (router).
3. **Device A sends packets to the router's MAC address**.
4. **The router forwards the packets** to Device B's network, using its routing table to determine the next hop.
5. **Device B receives the packets** and sends responses back to Device A through the router.

### Default Router in Linux

-   A default router (or gateway) is the device that routes traffic from a local network to other networks or the internet.
-   **Configuring the Default Gateway**:

    ```sh
    sudo ip route add default via <router-ip>
    ```

-   **Example**:

    ```sh
    sudo ip route add default via 192.168.1.1
    ```

---

## Ethernet Packets and Ethernet Explanation

### What is Ethernet?

Ethernet is a family of wired networking technologies commonly used in local area networks (LANs), metropolitan area networks (MANs), and wide area networks (WANs). It defines wiring and signaling standards for the physical layer and data packet formats and protocols for the data link layer of the OSI model.

### Ethernet Frame Structure

An Ethernet frame is a data packet that includes information needed for data link layer transmission. The Ethernet frame format is standardized and consists of several fields:

1. **Preamble**: 7 bytes used to synchronize receiver clock.
2. **Start Frame Delimiter (SFD)**: 1 byte indicating the start of the frame.
3. **Destination MAC Address**: 6 bytes indicating the recipient's MAC address.
4. **Source MAC Address**: 6 bytes indicating the sender's MAC address.
5. **Type/Length**: 2 bytes indicating the type of protocol (e.g., IPv4, IPv6) or the length of the payload.
6. **Payload**: Variable length data (up to 1500 bytes) containing the encapsulated data from higher layers.
7. **Frame Check Sequence (FCS)**: 4 bytes used for error checking.

### Ethernet Frame Format

| Field                 | Size (Bytes) |
| --------------------- | ------------ |
| Preamble              | 7            |
| Start Frame Delimiter | 1            |
| Destination MAC       | 6            |
| Source MAC            | 6            |
| Type/Length           | 2            |
| Payload               | 46-1500      |
| Frame Check Sequence  | 4            |

### Ethernet Operation

Ethernet operates by transmitting data in packets called frames between devices connected via cables. Each device on an Ethernet network has a unique MAC address, which it uses to communicate with other devices.

### Example Ethernet Frame

-   **Preamble**: `10101010 10101010 10101010 10101010 10101010 10101010 10101010`
-   **SFD**: `10101011`
-   **Destination MAC**: `00:14:22:01:23:45`
-   **Source MAC**: `00:14:22:01:23:46`
-   **Type**: `0800` (IPv4)
-   **Payload**: Data from higher layer protocols.
-   **FCS**: CRC value for error checking.

### Ethernet Transmission Process

1. **Frame Creation**: The sending device creates an Ethernet frame encapsulating the data to be sent.
2. **Frame Transmission**: The frame is transmitted over the Ethernet cable to the destination device.
3. **Frame Reception**: The receiving device captures the frame and checks the destination MAC address.
4. **Error Checking**: The receiving device uses the FCS to check for errors.
5. **Frame Processing**: If no errors are found, the receiving device processes the payload.

### Advantages and Disadvantages of Ethernet

-   **Advantages**:
    -   High speed and reliability.
    -   Widely used and standardized.
    -   Cost-effective for LANs.
-   **Disadvantages**:
    -   Limited range without repeaters or switches.
    -   Susceptible to physical damage and interference.

### Practical Commands for Ethernet

-   **View Ethernet Interfaces**:

    ```sh
    ip link show
    ```

-   **Bring Up an Ethernet Interface**:

    ```sh
    sudo ip link set dev eth0 up
    ```

-   **Assign an IP Address to an Ethernet Interface**:

    ```sh
    sudo ip addr add 192.168.1.10/24 dev eth0
    ```

-   **View MAC Address of an Interface**:

    ```sh
    ip link show eth0
    ```

-   **Bring Down an Ethernet Interface**:

    ```sh
    sudo ip link set dev eth0 down
    ```

-   **Delete an IP Address from an Ethernet Interface**:

    ```sh
    sudo ip addr del 192.168.1.10/24 dev eth0
    ```

-   **Set a Static MAC Address**:

    ```sh
    sudo ip link set dev eth0 address 00:14:22:01:23:45
    ```

-   **Add a Static ARP Entry**:

    ```sh
    sudo ip neigh add 192.168.1.20 lladdr 00:14:22:01:23:46 dev eth0
    ```

-   **Delete a Static ARP Entry**:

    ```sh
    sudo ip neigh del 192.168.1.20 dev eth0
    ```

-   **View ARP Table**:

    ```sh
    ip neigh show
    ```

---

## IP Addressing and Subnetting

### IPv4 Addressing

#### IP Address Format

-   **IPv4**: 32-bit address, divided into four 8-bit octets.
-   **Netmask**: Defines the network portion of the IP address.
-   **CIDR Notation**: The `/` notation following an IP address indicates the number of bits used for the network portion (e.g., `192.168.1.0/24`).

#### IPv4 Classes

IPv4 addresses are divided into five classes, based on the leading bits:

-   **Class A**

    -   **Range**: `1.0.0.0` to `126.0.0.0`
    -   **Default Subnet Mask**: `255.0.0.0`
    -   **Number of Networks**: 128 (2^7)
    -   **Number of Hosts per Network**: 16,777,214 (2^24 - 2)
    -   **Example**: `10.0.0.0` (Private Range)

-   **Class B**

    -   **Range**: `128.0.0.0` to `191.255.0.0`
    -   **Default Subnet Mask**: `255.255.0.0`
    -   **Number of Networks**: 16,384 (2^14)
    -   **Number of Hosts per Network**: 65,534 (2^16 - 2)
    -   **Example**: `172.16.0.0` (Private Range)

-   **Class C**

    -   **Range**: `192.0.0.0` to `223.255.255.0`
    -   **Default Subnet Mask**: `255.255.255.0`
    -   **Number of Networks**: 2,097,152 (2^21)
    -   **Number of Hosts per Network**: 254 (2^8 - 2)
    -   **Example**: `192.168.0.0` (Private Range)

-   **Class D**

    -   **Range**: `224.0.0.0` to `239.255.255.255`
    -   **Used for**: Multicast.

-   **Class E**
    -   **Range**: `240.0.0.0` to `255.255.255.255`
    -   **Reserved for**: Future use and research.

### Subnetting and Netmask

Subnetting allows dividing a larger network into smaller sub-networks, which helps in efficient IP management and security.

#### Subnet Mask

-   **Purpose**: Determines which portion of an IP address is the network and which part is the host.
-   **Example**: `255.255.255.0` (binary: `11111111.11111111.11111111.00000000`)

#### CIDR Notation

-   **Purpose**: CIDR (Classless Inter-Domain Routing) notation provides a shorthand method for defining the subnet mask.
-   **Example**: `192.168.1.0/24` means the first 24 bits are the network portion, and the remaining 8 bits are for host addresses.
-   **Shortcut**: Instead of writing the full subnet mask (`255.255.255.0`), the `/24` notation is used, which represents the number of bits used for the network portion.

#### Numerical Example for Subnetting

Let's take an IP address `192.168.1.0/24` and subnet it into smaller networks.

1. **Original Network**: `192.168.1.0/24`

    - **Subnet Mask**: `255.255.255.0`
    - **Number of Subnets**: 1
    - **Number of Hosts**: 256 - 2 = 254
    - **Binary Subnet Mask**: `11111111.11111111.11111111.00000000`

2. **Subnet into Two**: `192.168.1.0/25` and `192.168.1.128/25`

    - **Subnet Mask**: `255.255.255.128`
    - **Number of Subnets**: 2
    - **Number of Hosts**: 128 - 2 = 126
    - **Binary Subnet Mask**: `11111111.11111111.11111111.10000000`

    **Explanation**:

    - **192.168.1.0/25**:

        - Binary: `11000000.10101000.00000001.0XXXXXXX`
        - First Address: `192.168.1.0`
        - Last Address: `192.168.1.127`
        - **First Address (Binary)**: `11000000.10101000.00000001.00000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.01111111`

    - **192.168.1.128/25**:
        - Binary: `11000000.10101000.00000001.1XXXXXXX`
        - First Address: `192.168.1.128`
        - Last Address: `192.168.1.255`
        - **First Address (Binary)**: `11000000.10101000.00000001.10000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.11111111`

3. **Subnet into Four**: `192.168.1.0/26`, `192.168.1.64/26`, `192.168.1.128/26`, and `192.168.1.192/26`

    - **Subnet Mask**: `255.255.255.192`
    - **Number of Subnets**: 4
    - **Number of Hosts**: 64 - 2 = 62
    - **Binary Subnet Mask**: `11111111.11111111.11111111.11000000`

    **Explanation**:

    - **192.168.1.0/26**:

        - Binary: `11000000.10101000.00000001.00XXXXXX`
        - First Address: `192.168.1.0`
        - Last Address: `192.168.1.63`
        - **First Address (Binary)**: `11000000.10101000.00000001.00000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.00111111`

    - **192.168.1.64/26**:

        - Binary: `11000000.10101000.00000001.01XXXXXX`
        - First Address: `192.168.1.64`
        - Last Address: `192.168.1.127`
        - **First Address (Binary)**: `11000000.10101000.00000001.01000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.01111111`

    - **192.168.1.128/26**:

        - Binary: `11000000.10101000.00000001.10XXXXXX`
        - First Address: `192.168.1.128`
        - Last Address: `192.168.1.191`
        - **First Address (Binary)**: `11000000.10101000.00000001.10000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.10111111`

    - **192.168.1.192/26**:
        - Binary: `11000000.10101000.00000001.11XXXXXX`
        - First Address: `192.168.1.192`
        - Last Address: `192.168.1.255`
        - **First Address (Binary)**: `11000000.10101000.00000001.11000000`
        - **Last Address (Binary)**: `11000000.10101000.00000001.11111111`

**Note**: The number after the slash (`/`) in CIDR notation represents the number of bits used for the network portion of the address. This is a shorthand for writing out the subnet mask. For example, `/24` is equivalent to `255.255.255.0`, indicating that the first 24 bits are used for the network address, leaving the remaining bits for host addresses.

### IPv4 Header Format

The IPv4 header is a crucial part of the Internet Protocol, containing essential information for routing and delivering packets. Here is the structure of the IPv4 header:

1. **Version (4 bits)**: Indicates the IP version (e.g., 4 for IPv4).
2. **Header Length (4 bits)**: Specifies the length of the IP header in 32-bit words.
3. **Type of Service (8 bits)**: Used for quality of service features.
4. **Total Length (16 bits)**: The total length of the IP packet, including header and data.
5. **Identification (16 bits)**: Used for uniquely identifying fragments of an original IP packet.
6. **Flags (3 bits)**: Controls or identifies fragments.
    - **Bit 0**: Reserved, must be zero.
    - **Bit 1**: Don't Fragment (DF).
    - **Bit 2**: More Fragments (MF).
7. **Fragment Offset (13 bits)**: Indicates the position of the fragment in the original IP packet.
8. **Time to Live (TTL) (8 bits)**: Limits the packet's lifetime to prevent it from circulating indefinitely.
9. **Protocol (8 bits)**: Indicates the protocol used in the data portion of the IP datagram (e.g., TCP, UDP).
10. **Header Checksum (16 bits)**: Used for error-checking of the header.
11. **Source Address (32 bits)**: The IP address of the sender.
12. **Destination Address (32 bits)**: The IP address of the receiver.
13. **Options (variable)**: Optional fields used for various network functions.

Here is an example of how the IPv4 header is structured in C:

```c
typedef struct {
    uint8_t  ipHeaderLength   : 4;
    uint8_t  version          : 4;
    uint8_t  typeOfService;
    uint16_t length;
    uint16_t identification;
    uint16_t fragmentation;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    IP4_t    sourceIP;
    IP4_t    destIP;
} __attribute__((packed)) ipv4Packet_t;
```

This structure shows the fields of the IPv4 header, defining how each piece of data is stored within the packet.

### Practical Commands for IPv4

-   **View IP Address**:

    ```sh
    ip addr show
    ```

    Equivalent `net-tools` command:

    ```sh
    ifconfig
    ```

-   **Assign IP Address**:

    ```sh
    sudo ip addr add 192.168.1.10/24 dev eth0
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 192.168.1.10 netmask 255.255.255.0
    ```

-   **Delete IP Address**:

    ```sh
    sudo ip addr del 192.168.1.10/24 dev eth0
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 del 192.168.1.10
    ```

-   **Add Default Gateway**:

    ```sh
    sudo ip route add default via 192.168.1.1
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo route add default gw 192.168.1.1
    ```

-   **Delete Default Gateway**:

    ```sh
    sudo ip route del default
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo route del default
    ```

-   **View Routing Table**:

    ```sh
    ip route show
    ```

    Equivalent `net-tools` command:

    ```sh
    route -n
    ```

-   **Flush All IP Addresses on an Interface**:

    ```sh
    sudo ip addr flush dev eth0
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 0.0.0.0
    ```

-   **Bring Up an Interface**:

    ```sh
    sudo ip link set dev eth0 up
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 up
    ```

-   **Bring Down an Interface**:

    ```sh
    sudo ip link set dev eth0 down
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 down
    ```

-   **Enable/Disable Multicast on an Interface**:

    ```sh
    sudo ip link set dev eth0 multicast on
    sudo ip link set dev eth0 multicast off
    ```

    Equivalent `net-tools` command:

    ```sh
    sudo ifconfig eth0 multicast
    sudo ifconfig eth0 -multicast
    ```

-   **Show Network Statistics**:

    ```sh
    ip -s link
    ```

    Equivalent `net-tools` command:

    ```sh
    netstat -i
    ```

### Routing and Default Gateway

A router forwards data packets between computer networks. A default gateway routes traffic from a local network to other networks or the internet.

-   **Setting a Default Gateway:**

    -   Using `iproute2`:

        ```sh
        sudo ip route add default via 192.168.1.1
        ```

    -   Equivalent `net-tools` command:

        ```sh
        sudo route add default gw 192.168.1.1
        ```

-   **Viewing the Routing Table:**

    -   Using `iproute2`:

        ```sh
        ip route show
        ```

    -   Equivalent `net-tools` command:

        ```sh
        route -n
        ```

### ARP and ICMP

**ARP (Address Resolution Protocol)** and **ICMP (Internet Control Message Protocol)** are two essential protocols used in network communication.

-   **ARP** resolves IP addresses to MAC (hardware) addresses within a local network, enabling devices to communicate at the data link layer.
-   **ICMP** is used for error reporting and diagnostics, facilitating network troubleshooting and status monitoring (e.g., `ping` and `traceroute` commands).

---

### ARP (Address Resolution Protocol) Overview

**Purpose**:  
ARP maps an IP address to a MAC address within a local network. This is crucial for devices to communicate over Ethernet or Wi-Fi networks.

**Example of ARP in Communication**:

1. **Local Network Communication**:

    - **Sender**: Sends an ARP request to resolve the MAC address of a device with a known IP address.
    - **Recipient**: If present on the same network, it responds with its MAC address.
    - **Data Transmission**: Once the MAC address is known, the sender communicates directly with the recipient.

2. **Different Network Communication**:
    - **Sender**: Sends data to the default gateway (router).
    - **Router**: Uses ARP to resolve the MAC address of the next-hop router or device.
    - **Routing Process**: The process continues at each hop until the packet reaches the destination.

---

#### Types of Casts (for ARP and ICMP)

-   **Unicast**: Communication between a single sender and a single receiver.
-   **Broadcast**: One sender sends data to all devices in the network (used by ARP requests).
-   **Multicast**: Communication from one sender to a select group of devices.

---

### ARP Packet

**Purpose**:  
Determine the MAC address corresponding to an IP address.

**Process**:

-   **Sender**: Broadcasts an ARP request to all devices on the local network, asking "Who has IP address X?"
-   **Recipient**: The device with IP address X responds directly with its MAC address.
-   **Caching**: The sender stores this MAC address in its ARP cache to avoid repeated requests.

**Example Command**:

```sh
arp -a
```

-   Displays the current ARP cache on the system.

---

### ICMP (Internet Control Message Protocol) Overview

**Purpose**:  
ICMP is primarily used for network diagnostics and error reporting. It helps identify network issues and confirm device connectivity.

**Example of ICMP in Communication**:

1. **Host Reachability (Ping)**:

    - **Sender**: Sends an ICMP Echo Request to the destination.
    - **Recipient**: Responds with an ICMP Echo Reply if the destination is reachable.

2. **Path Discovery (Traceroute)**:
    - ICMP is used to map the route packets take to reach a destination.
    - Each router along the path sends back an ICMP Time Exceeded message when the packet’s TTL (Time to Live) expires.

---

### ICMP Packet

**Purpose**:  
Communicate network issues and provide feedback about network performance.

**Process**:

-   **Sender**: Sends an ICMP Echo Request (ping) to test connectivity.
-   **Recipient**: Responds with an ICMP Echo Reply.
-   **Error Reporting**: If a packet cannot reach its destination, ICMP sends an error message (e.g., Destination Unreachable).

**Common ICMP Message Types**:

-   **Echo Request (Type 8)** – Check if the destination is reachable.
-   **Echo Reply (Type 0)** – Confirms that the destination is reachable.
-   **Destination Unreachable (Type 3)** – Reports that the destination cannot be reached.
-   **Time Exceeded (Type 11)** – Indicates that the packet's TTL expired.
-   **Redirect (Type 5)** – Informs the sender of a better route.

**Example Command**:

```sh
ping 8.8.8.8
```

-   Sends ICMP Echo Requests to Google’s DNS server to check internet connectivity.

---

### ARP vs ICMP – Key Differences

| Feature                | ARP                            | ICMP                                               |
| ---------------------- | ------------------------------ | -------------------------------------------------- |
| **Purpose**            | Resolve IP to MAC addresses    | Report errors and test connectivity                |
| **Layer**              | Data Link Layer (Layer 2)      | Network Layer (Layer 3)                            |
| **Communication Type** | Broadcast within local network | Unicast between devices                            |
| **Message Example**    | "Who has IP X? Tell MAC Y"     | "Ping request to IP X"                             |
| **Response Example**   | "IP X is at MAC Y"             | "Echo Reply from IP X"                             |
| **Common Commands**    | `arp -a` (View ARP cache)      | `ping`, `traceroute`                               |
| **Error Reporting**    | No error reporting             | Reports unreachable destinations or TTL expiration |

---

## IPv6 Addressing

### IPv6 Address Format

-   **IPv6**: 128-bit address, written as eight groups of four hexadecimal digits (e.g., `2001:0db8:85a3:0000:0000:8a2e:0370:7334`).

### IPv6 Features

-   **Larger Address Space**: Provides a virtually unlimited number of IP addresses.
-   **Simplified Header**: Improves routing efficiency and performance.
-   **Auto-Configuration**: Devices can automatically configure their own IP addresses.
-   **Integrated Security**: IPsec is mandatory in IPv6.
-   **No Broadcasts**: Uses multicast and anycast instead of broadcast.

### Example Address

-   `2001:0db8:85a3:0000:0000:8a2e:0370:7334`

### Subnetting in IPv6

IPv6 uses prefix length to denote subnetting (similar to CIDR in IPv4).

-   **Example**:
    -   Global Unicast Address: `2001:0db8::/32`
    -   Subnet ID: `2001:0db8:abcd::/48`
    -   Interface ID: `2001:0db8:abcd:0012:0000:0000:0000:0001/64`

### Transition from IPv4 to IPv6

-   **Dual Stack**: Devices run both IPv4 and IPv6.
-   **Tunneling**: Encapsulating IPv6 traffic within IPv4 packets.
-   **Translation**: Converting IPv6 packets to IPv4 packets and vice versa.

### Practical Usage

-   Configure IPv6 on a network interface:

    ```sh
    sudo ip -6 addr add 2001:db8::1/64 dev eth0
    ```

-   Add an IPv6 route:

    ```sh
    sudo ip -6 route add 2001:db8:abcd::/64 via 2001:db8::1
    ```

### Address Types

-   **Unicast**: Identifies a single network interface.
-   **Multicast**: Identifies multiple network interfaces.
-   **Anycast**: Identifies the nearest of multiple network interfaces.

---

## ICMP Packets

### ICMP (Internet Control Message Protocol)

-   Used for error messages and operational information.
-   Common messages: Echo Request (ping), Echo Reply (pong), Destination Unreachable.

### ICMP Packet Structure

1. **Type**: 8 bits, indicates the type of message.
2. **Code**: 8 bits, provides further information about the type.
3. **Checksum**: 16 bits, for error-checking.
4. **Rest of the Header**: Varies based on the type and code.

### Example

-   **Ping**:
    -   Type: 8 (Echo Request)
    -   Code: 0

---

## ARP Packets

### ARP (Address Resolution Protocol)

-   Used to map an IP address to a MAC address within a local network.

### ARP Process

1. **ARP Request**: Broadcasted by a device to find the MAC address associated with an IP address.
2. **ARP Reply**: Sent by the device with the requested IP address, containing its MAC address.

### Packet Structure

1. **Hardware Type**: 16 bits, indicates the network type (e.g., Ethernet).
2. **Protocol Type**: 16 bits, indicates the protocol (e.g., IP).
3. **Hardware Address Length**: 8 bits.
4. **Protocol Address Length**: 8 bits.
5. **Operation**: 16 bits, indicates request (1) or reply (2).
6. **Sender Hardware Address**: 48 bits.
7. **Sender Protocol Address**: 32 bits.
8. **Target Hardware Address**: 48 bits.
9. **Target Protocol Address**: 32 bits.

### Example of ARP Communication

-   Device A wants to communicate with Device B.
-   Device A sends an ARP request: "Who has IP address 192.168.1.2? Tell 192.168.1.1."
-   Device B responds: "192.168.1.2 is at MAC address 00:14:22:01:23:45."

---

## Virtual Network Devices

### TUN and TAP Devices

TUN and TAP are virtual network kernel devices. They provide network interfaces that can be used by user-space programs to interact with the network stack.

-   **TAP Device**: Emulates an Ethernet device and operates with layer 2 packets such as Ethernet frames. It is used to create a network bridge, where multiple virtual machines or containers can communicate as if they are on the same physical network.
-   **TUN Device**: Emulates a network layer device and operates with layer 3 packets such as IP packets. It is commonly used for routing purposes and can be used to create VPNs.

### Creating and Managing TAP/TUN Devices

#### Create a TAP Device

To create a TAP device, use the following commands:

```sh
sudo ip tuntap add dev tap0 mode tap
sudo ip link set dev tap0 up
```

#### Create a TUN Device

To create a TUN device, use the following commands:

```sh
sudo ip tuntap add dev tun0 mode tun
sudo ip link set dev tun0 up
```

### Practical Commands for Managing TUN/TAP Devices

#### View TUN/TAP Devices

To list all TUN/TAP devices, use the following command:

```sh
ip link show type tuntap
```

#### Set IP Address for TAP Device

To assign an IP address to a TAP device:

```sh
sudo ip addr add 192.168.1.100/24 dev tap0
```

#### Set IP Address for TUN Device

To assign an IP address to a TUN device:

```sh
sudo ip addr add 10.0.0.1/24 dev tun0
```

#### Bring Down a TAP/TUN Device

To bring down (disable) a TAP or TUN device:

```sh
sudo ip link set dev tap0 down
sudo ip link set dev tun0 down
```

#### Delete a TAP/TUN Device

To delete a TAP or TUN device:

```sh
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tun0 mode tun
```

#### Create a TAP Device with Specific MAC Address

To create a TAP device with a specific MAC address:

```sh
sudo ip tuntap add dev tap0 mode tap
sudo ip link set dev tap0 address 02:01:02:03:04:08
sudo ip link set dev tap0 up
```

#### Create a TUN Device with Specific MTU

To create a TUN device with a specific Maximum Transmission Unit (MTU):

```sh
sudo ip tuntap add dev tun0 mode tun
sudo ip link set dev tun0 mtu 1400
sudo ip link set dev tun0 up
```

#### Create a TAP Device with User Ownership

To create a TAP device and set the user ownership:

```sh
sudo ip tuntap add dev tap0 mode tap user <username>
sudo ip link set dev tap0 up
```

### Example Usage Scenarios

#### Bridging TAP Devices

To create a network bridge and add a TAP device to it:

1. **Create a bridge device**:

    ```sh
    sudo ip link add name br0 type bridge
    sudo ip link set dev br0 up
    ```

2. **Add TAP device to the bridge**:

    ```sh
    sudo ip link set dev tap0 master br0
    sudo ip link set dev tap0 up
    ```

3. **Add Ethernet device to the bridge**:

    ```sh
    sudo ip link set dev eth0 master br0
    sudo ip link set dev eth0 up
    ```

#### Configuring TUN Device for VPN

To configure a TUN device for VPN use:

1. **Create a TUN device**:

    ```sh
    sudo ip tuntap add dev tun0 mode tun
    sudo ip link set dev tun0 up
    ```

2. **Assign IP addresses**:

    ```sh
    sudo ip addr add 10.0.0.1/24 dev tun0
    ```

3. **Enable IP forwarding**:

    ```sh
    sudo sysctl -w net.ipv4.ip_forward=1
    ```

4. **Add IP routes**:

    ```sh
    sudo ip route add 10.0.0.0/24 dev tun0
    ```

#### Configuring TAP Device for Virtual Machine Networking

To configure a TAP device for use with a virtual machine:

1. **Create a TAP device**:

    ```sh
    sudo ip tuntap add dev tap0 mode tap
    sudo ip link set dev tap0 up
    ```

2. **Assign an IP address**:

    ```sh
    sudo ip addr add 192.168.100.1/24 dev tap0
    ```

3. **Configure the virtual machine to use the TAP device**:

    In the virtual machine configuration, specify the TAP device `tap0` as the network interface.

4. **Enable packet forwarding** (if needed):

    ```sh
    sudo sysctl -w net.ipv4.ip_forward=1
    ```

### Additional Commands and Configurations

#### Change the Name of a TUN/TAP Device

To rename a TUN/TAP device:

```sh
sudo ip link set dev tap0 name mytap0
sudo ip link set dev tun0 name mytun0
```

#### Set a Description for a TUN/TAP Device

To set a description for a TUN/TAP device:

```sh
sudo ip link set dev tap0 alias "My TAP Device"
sudo ip link set dev tun0 alias "My TUN Device"
```

#### Monitor TUN/TAP Device Traffic

To monitor the traffic on a TUN/TAP device, you can use tools like `tcpdump`:

```sh
sudo tcpdump -i tap0
sudo tcpdump -i tun0
```

#### Adjusting MTU

To adjust the MTU (Maximum Transmission Unit) for a TAP/TUN device:

```sh
sudo ip link set dev tap0 mtu 1400
sudo ip link set dev tun0 mtu 1400
```

---

## VirtIO and Virtual Machines

### Virtual Machines

Virtual machines (VMs) are software-based emulations of physical computers. They run an operating system and applications just like a physical computer. VMs are managed by a hypervisor, which allocates resources from the physical host to each VM. The hypervisor provides isolation, ensuring that each VM operates independently of the others.

**Key Benefits of Virtual Machines:**

-   **Resource Efficiency**: Multiple VMs can run on a single physical host, maximizing resource utilization.
-   **Isolation**: VMs are isolated from each other, providing security and stability.
-   **Flexibility**: VMs can run different operating systems and configurations on the same host.
-   **Scalability**: Resources can be dynamically allocated to VMs based on demand.
-   **Snapshot and Backup**: VMs can be easily backed up, cloned, and restored.

### KVM (Kernel-based Virtual Machine)

-   **Type**: Hypervisor
-   **Function**: KVM is a Linux kernel module that turns the Linux kernel into a bare-metal hypervisor.
-   **Features**:
    -   Provides hardware-assisted virtualization.
    -   Supports running multiple virtual machines (VMs) on a single physical machine.
    -   Uses hardware extensions like Intel VT-x or AMD-V for performance improvements.
    -   Allows VMs to run unmodified guest operating systems (e.g., Linux, Windows).
-   **Integration**: KVM is integrated into the Linux kernel, providing native support for virtualization.

### QEMU (Quick Emulator)

-   **Type**: Emulator and Virtualizer
-   **Function**: QEMU is a user-space emulator that can emulate various hardware platforms and provide virtualization capabilities.
-   **Features**:
    -   Can run in two modes: full emulation mode (emulates all hardware) and virtualization mode (uses hardware acceleration).
    -   When used with KVM, QEMU leverages KVM's kernel-based virtualization to improve performance.
    -   Supports a wide range of CPU architectures and device emulation.
-   **Integration**: QEMU can use KVM as an accelerator to provide near-native performance for virtual machines by offloading CPU and memory management to KVM.

### Relationship between KVM and QEMU

-   **KVM**: Provides the underlying virtualization support by enabling the hardware-assisted virtualization features of the CPU.
-   **QEMU**: Acts as the front-end that emulates hardware devices and provides the interface for creating and managing virtual machines. When combined with KVM, QEMU uses KVM to handle low-level CPU and memory virtualization, which significantly enhances performance.

### How They Work Together

1. **QEMU without KVM**: QEMU performs full software emulation of all hardware devices and the CPU, which can be slow but allows running virtual machines on any host hardware.
2. **QEMU with KVM**: QEMU uses KVM for CPU and memory virtualization, providing near-native performance. QEMU handles device emulation and provides the management interface, while KVM takes care of the low-level virtualization tasks.

### Example Workflow

1. **QEMU creates and manages VMs**:

    - Defines the virtual machine configuration (e.g., CPU, memory, storage, network devices).
    - Provides device emulation for various hardware components.

2. **KVM accelerates virtualization**:
    - Uses hardware-assisted virtualization features to execute guest code directly on the host CPU.
    - Manages low-level tasks like context switching between VMs and the host.

### Example Command to Run a VM with QEMU and KVM

```sh
qemu-system-x86_64 -enable-kvm -kernel bzImage -m 1G \
  -drive file=rootfs.img,if=virtio \
  -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
  -device virtio-net-pci,netdev=net0 \
  -append "root=/dev/vda rw" -daemonize
```

-   **-enable-kvm**: Enables KVM acceleration.
-   **qemu-system-x86_64**: QEMU command to start an x86_64 virtual machine.
-   **-kernel bzImage**: Specifies the kernel image for the VM.
-   **-m 1G**: Allocates 1 GB of RAM to the VM.
-   **-drive "file=rootfs.img,if=virtio,format=raw"**: Specifies the disk image for the VM, using the VirtIO interface.
-   **-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B'**: Adds a VirtIO network device with the specified MAC address.
-   **-netdev tap,id=net0,ifname=tap0,script=no,downscript=no**: Specifies the network backend using the TAP device `tap0`.
-   **-name h1**: Sets the name of the VM to `h1`.
-   **-daemonize**: Runs QEMU in the background.
-   **--append "root=/dev/vda rw"**: Specifies the kernel parameters to mount the root filesystem as read-write.

### VirtIO

VirtIO is a virtualization standard for network and disk device drivers. It provides a generic interface between the guest virtual machine (VM) and the hypervisor, allowing for efficient data exchange. VirtIO drivers are designed to offer near-native performance by reducing the overhead typically associated with emulating hardware.

#### Advantages of VirtIO

-   **Efficiency**: Reduces the overhead of emulating hardware devices, resulting in improved performance.
-   **Standardization**: Provides a consistent and standardized interface for various types of devices.
-   **Compatibility**: Supported by major hypervisors, including KVM (Kernel-based Virtual Machine) and QEMU (Quick Emulator).
-   **Scalability**: Suitable for high-performance and scalable virtualized environments.

### VirtIO Network Device (virtio-net)

VirtIO network device (virtio-net) is a paravirtualized network driver that allows VMs to communicate with the host system's network stack. It provides a more efficient interface compared to traditional network emulation, resulting in improved network performance.

#### How VirtIO Emulates the Network Interface Card (NIC)

1. **Initialization**: When a VM starts, the hypervisor initializes the virtio-net device and assigns it to the VM.
2. **Device Discovery**: The guest kernel detects the virtio-net device during boot and loads the appropriate virtio-net driver.
3. **Queue Pairs**: Virtio-net uses a pair of virtqueues (one for transmitting and one for receiving) to handle network packets. Each queue consists of a descriptor ring, available ring, and used ring.
4. **Data Transmission**:
    - **Guest to Host**: The guest places network packets into the transmit virtqueue. The hypervisor processes these packets and forwards them to the host network stack.
    - **Host to Guest**: The hypervisor places incoming packets into the receive virtqueue. The guest kernel processes these packets and forwards them to the appropriate application.
5. **Efficient I/O**: Virtio-net reduces the need for costly device emulation by directly sharing memory pages between the guest and host. This allows for efficient data transfer and reduces CPU overhead.

#### Key Components of VirtIO-net

-   **Virtqueues**: Circular buffer structures used for efficient communication between the guest and host.
-   **Descriptor Ring**: Holds descriptors that describe the location and size of network packets in memory.
-   **Available Ring**: Indicates which descriptors are available for processing.
-   **Used Ring**: Indicates which descriptors have been processed and are ready to be reused.

### Virtual Machines and their Relationships

In a virtualized environment, multiple virtual machines (VMs) run on a single physical host. These VMs are isolated from each other but can communicate over virtual networks configured on the host. The following sections detail how VirtIO integrates with virtual machines and how to set up and manage VMs using QEMU and KVM.

### Running Virtual Machines with QEMU

QEMU (Quick Emulator) is a popular open-source emulator and virtualization tool that supports VirtIO. QEMU can run VMs with various configurations, including using VirtIO for network and disk devices.

#### Example Command to Run a VM with QEMU and VirtIO

```sh
qemu-system-x86_64 -kernel bzImage -m 1G \
  -drive file=rootfs.img,if=virtio \
  -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
  -device virtio-net-pci,netdev=net0 \
  -append "root=/dev/vda rw" -daemonize
```

#### Explanation of the Command

-   **qemu-system-x86_64**: Invokes the QEMU emulator for x86_64 architecture.
-   **-kernel bzImage**: Specifies the kernel image to boot.
-   **-m 1G**: Allocates 1 GB of memory to the VM.
-   **-drive "file=rootfs.img,if=virtio,format=raw"**: Attaches a disk image (`rootfs.img`) as a VirtIO block device.
-   **-netdev tap,id=net0,ifname=tap0,script=no,downscript=no**: Configures a TAP network backend for the VM. The TAP device `tap0` is used for network connectivity.
-   **-device virtio-net-pci,netdev=net0**: Attaches a VirtIO network device (`virtio-net-pci`) to the VM and links it to the `net0` network backend.
-   **-append "root=/dev/vda rw"**: Passes kernel parameters to specify the root filesystem and mount it as read-write.
-   **-daemonize**: Runs QEMU as a background process.

### Detailed Steps to Set Up VirtIO Network with QEMU

1. **Install QEMU and KVM**:

    ```sh
    sudo apt-get install qemu-kvm qemu-utils
    ```

2. **Create a TAP Device**:

    ```sh
    sudo ip tuntap add dev tap0 mode tap
    sudo ip link set dev tap0 up
    sudo ip addr add 192.168.1.1/24 dev tap0
    ```

3. **Create a Bridge Device (Optional)**:

    ```sh
    sudo ip link add name br0 type bridge
    sudo ip link set dev br0 up
    sudo ip link set dev tap0 master br0
    sudo ip addr add 192.168.1.1/24 dev br0
    ```

4. **Prepare the Disk Image**:

    ```sh
    qemu-img create -f qcow2 rootfs.img 10G
    ```

5. **Run the VM with QEMU**:

    ```sh
    qemu-system-x86_64 -kernel bzImage -m 1G \
    -drive file=rootfs.img,if=virtio \
    -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
    -device virtio-net-pci,netdev=net0 \
    -append "root=/dev/vda rw" -daemonize
    ```

### Monitoring and Managing VirtIO Devices

#### Check VirtIO Devices in the Guest

To check the VirtIO devices in the guest VM, use the following commands inside the VM:

-   **List all network interfaces**:

    ```sh
    ip link show
    ```

-   **Check VirtIO block devices**:

    ```sh
    lsblk
    ```

-   **Check loaded VirtIO drivers**:

    ```sh
    lsmod | grep virtio
    ```

### Advanced Configuration and Optimization

#### Enable Multiqueue for VirtIO-net

Multiqueue improves network performance by allowing multiple CPU cores to process network packets simultaneously. To enable multiqueue, use the following QEMU command options:

```sh
qemu-system-x86_64 -kernel bzImage -m 1G \
  -drive file=rootfs.img,if=virtio \
  -netdev tap,id=net0,ifname=tap0,script=no,downscript=no,queues=4 \
  -device virtio-net-pci,netdev=net0,mq=on,vectors=10 \
  -append "root=/dev/vda rw" -daemonize
```

#### Enable Offloading Features

To further optimize network performance, enable offloading features such as checksum offloading and TCP segmentation offloading (TSO):

```sh
ethtool -K eth0 tx off
ethtool -K eth0 tso off
```

#### Configure NUMA for Better Performance

Non-Uniform Memory Access (NUMA) configuration can improve performance for VMs with high memory and CPU usage:

```sh
qemu-system-x86_64 -kernel bzImage -m 4G \
  -numa node,memdev=mem0 \
  -object memory-backend-ram,size=4G,id=mem0 \
  -drive file=rootfs.img,if=virtio \
  -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
  -device virtio-net-pci,netdev=net0 \
  -append "root=/dev/vda rw" -daemonize
```

### Relationships Between Virtual Machines

In a virtualized environment, virtual machines (VMs) can be configured to communicate with each other and the host system. This can be achieved through various networking configurations:

1. **Host-Only Networking**: VMs can communicate with each other and the host but not with external networks.
2. **NAT (Network Address Translation)**: VMs can access external networks, but external devices cannot initiate connections to the VMs.
3. **Bridged Networking**: VMs are connected to the host's physical network and can interact with external devices as if they were physical machines on the same network.
4. **Internal Networking**: VMs can communicate with each other on an isolated network, separate from the host and external networks.

By understanding and configuring these relationships, you can create complex virtual network topologies that simulate real-world scenarios, providing a powerful tool for testing, development, and training.

---

## Static Routing and Bridging

### Static Routing

Static routing is a type of network routing technique in which routes are manually configured and managed by the network administrator. Unlike dynamic routing, where routes are automatically adjusted by network protocols, static routing requires manual updates whenever the network topology changes. Static routes are useful for small networks or networks with a predictable and stable topology.

#### How Static Routing Works

Static routing involves manually adding routes to the routing table of a router or host. The routing table is a data structure that contains information about the paths that data packets take to reach their destinations. Each entry in the routing table specifies:

-   **Destination Network**: The network that the route leads to.
-   **Subnet Mask**: Defines the range of IP addresses within the destination network.
-   **Next-hop IP Address (Gateway)**: The IP address of the next router that packets should be sent to.

#### Adding a Static Route

To add a static route, you use the `ip route add` command followed by the destination network and the gateway IP address.

-   **Command**:

    ```sh
    sudo ip route add <network> via <gateway-ip>
    ```

    **Explanation**:

    -   `sudo`: Runs the command with superuser privileges.
    -   `ip route add`: Adds a new route to the routing table.
    -   `<network>`: Specifies the destination network in CIDR notation (e.g., `192.168.2.0/24`).
    -   `via <gateway-ip>`: Specifies the IP address of the next-hop router.

-   **Example**:

    To add a route to the network `192.168.2.0/24` via the gateway `192.168.1.1`, you would use the following command:

    ```sh
    sudo ip route add 192.168.2.0/24 via 192.168.1.1
    ```

    This command tells the system that any traffic destined for the `192.168.2.0/24` network should be sent through the gateway `192.168.1.1`.

#### Viewing the Routing Table

To view the current routing table and verify the added routes:

```sh
ip route show
```

**Explanation**:

-   `ip route show`: Displays the current routing table, listing all active routes.

#### Deleting a Static Route

To remove a static route from the routing table:

```sh
sudo ip route del <network> via <gateway-ip>
```

**Explanation**:

-   `sudo`: Runs the command with superuser privileges.
-   `ip route del`: Deletes a route from the routing table.
-   `<network> via <gateway-ip>`: Specifies the route to be deleted.

### Bridging

Bridging is a technique used to connect two or more network segments, making them function as a single network. A network bridge forwards traffic between these segments based on MAC addresses, effectively making the separate segments behave as one. This can help extend the network and improve performance without adding routers.

#### How Bridging Works

A bridge operates at the Data Link layer (Layer 2) of the OSI model and connects different network segments by filtering and forwarding traffic based on MAC addresses. By doing so, it reduces the collision domain but maintains the broadcast domain. This is useful in scenarios where you want to extend the network without adding routers.

#### Creating a Network Bridge

To create a bridge, you use the `ip link add` command to create a bridge interface, and the `ip link set` command to bring the bridge interface up.

-   **Commands**:

    ```sh
    sudo ip link add name br0 type bridge
    sudo ip link set dev br0 up
    ```

    **Explanation**:

    -   `sudo`: Runs the command with superuser privileges.
    -   `ip link add name br0 type bridge`: Creates a new bridge device named `br0`.
    -   `ip link set dev br0 up`: Activates the bridge device `br0`.

#### Adding Interfaces to the Bridge

Once the bridge is created, you can add network interfaces to it. This is done by using the `ip link set` command to set the network interfaces as members of the bridge.

-   **Commands**:

    ```sh
    sudo ip link set dev eth0 master br0
    sudo ip link set dev tap0 master br0
    ```

    **Explanation**:

    -   `sudo`: Runs the command with superuser privileges.
    -   `ip link set dev eth0 master br0`: Adds the Ethernet interface `eth0` to the bridge `br0`.
    -   `ip link set dev tap0 master br0`: Adds the TAP interface `tap0` to the bridge `br0`.

#### Practical Examples

##### Adding a Static Route Example

```sh
sudo ip route add 192.168.2.0/24 via 192.168.1.1
```

**Explanation**:

-   Adds a static route to the network `192.168.2.0/24`.
-   Specifies `192.168.1.1` as the gateway for this route.

##### Creating a Bridge

```sh
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
```

**Explanation**:

-   Creates a bridge interface named `br0`.
-   Activates the bridge interface.

##### Adding Interfaces to the Bridge (Example 1)

```sh
sudo ip link set dev eth0 master br0
sudo ip link set dev tap0 master br0
```

**Explanation**:

-   Adds the Ethernet interface `eth0` to the bridge `br0`.
-   Adds the TAP interface `tap0` to the bridge `br0`.

#### Additional Commands and Configurations for TUN/TAP Devices

##### View Bridge Details

To view the details of the bridge and its interfaces:

```sh
brctl show
```

**Explanation**:

-   `brctl show`: Displays the current bridge configuration and the interfaces attached to each bridge.

##### Remove Interface from Bridge

To remove an interface from a bridge:

```sh
sudo ip link set dev eth0 nomaster
```

**Explanation**:

-   `sudo`: Runs the command with superuser privileges.
-   `ip link set dev eth0 nomaster`: Removes the Ethernet interface `eth0` from any bridge it is part of.

##### Delete a Bridge

To delete a bridge interface:

```sh
sudo ip link delete br0
```

**Explanation**:

-   `sudo`: Runs the command with superuser privileges.
-   `ip link delete br0`: Deletes the bridge interface `br0`.

##### Persisting Static Routes and Bridge Configurations

To make static routes and bridge configurations persistent across reboots, you can add them to your network configuration files (e.g., `/etc/network/interfaces` for Debian-based systems, `/etc/sysconfig/network-scripts/ifcfg-br0` for Red Hat-based systems) or use a network management tool like `NetworkManager`.

##### Example for Debian-based Systems

Add the following lines to `/etc/network/interfaces`:

```sh
auto br0
iface br0 inet static
    address 192.168.1.2
    netmask 255.255.255.0
    bridge_ports eth0 tap0

post-up ip route add 192.168.2.0/24 via 192.168.1.1
```

By understanding and utilizing static routing and bridging, network administrators can effectively manage and optimize network traffic, ensuring efficient and reliable communication within and across networks.

---

## Practical Implementation

This section encompasses all the scripts and code examples necessary for the practical implementation of the networking and virtualization concepts discussed in this guide. These scripts automate tasks such as setting up network bridges, configuring TAP/TUN devices, launching virtual machines, and managing network routes. Follow the instructions below to configure your environment and launch your virtual machines seamlessly.

### 1. Important Notes

**Docker Bridge Conflict**: Having an active Docker bridge (`docker0`) can cause network conflicts with the custom bridge networks used in these scripts. It is recommended to remove the Docker bridge before running the scripts. For detailed instructions on how to remove and recreate the Docker bridge, please refer to the [Docker Bridge Network Management README](https://github.com/Mahmoud-Abdelraouf/STmicro-System-Programming-under-Linux/blob/main/05.Advanced/Practical/Session04/README-Docker-Network-Management.md). For resolving network connectivity issues with Docker and KVM/QEMU on Ubuntu, refer to the [Resolving Network Connectivity Issues with Docker and KVM/QEMU on Ubuntu README](https://github.com/Mahmoud-Abdelraouf/STmicro-System-Programming-under-Linux/blob/main/05.Advanced/Practical/Session04/README-Docker-KVM-QEMU-Network-Issues.md).

**Firewall Considerations**: Sometimes, the firewall settings can interfere with network connectivity between VMs. If you suspect this might be the case, you can disable the firewall using the following command:

```sh
sudo ufw disable
```

This command will disable the Uncomplicated Firewall (UFW) on your Ubuntu system. To re-enable it, use:

```sh
sudo ufw enable
```

To check the current status of UFW, use:

```sh
sudo ufw status
```

**Note**: Disabling the firewall can expose your system to potential security risks. Ensure that you only disable it for troubleshooting purposes and re-enable it once you have identified and resolved any network connectivity issues. If UFW is causing issues, consider adding specific rules to allow the necessary traffic rather than completely disabling the firewall.

**VM Network Interfaces**: If the VMs cannot ping each other even when the network interfaces appear to be up, you can manually bring up the network interfaces. Use the following command inside each VM:

```sh
sudo ip link set ethX up
```

Replace `ethX` with the appropriate interface name (e.g., `eth0`, `eth1`). Sometimes the interfaces need to be manually brought up even if they show as working in `ifconfig`.

**Note**: All images used in these scripts were built using Yocto releases of Kirkstone. For more details on how the images were created, please refer to [Session 03: Working with Yocto - System Programming under Linux](https://github.com/Mahmoud-Abdelraouf/STmicro-System-Programming-under-Linux/blob/main/05.Advanced/Practical/Session03/README.md).

---

### 2. Machine Configurations

**Note**: The following configurations must be added to the `/etc/network/interfaces` file on each machine to ensure they can see each other.

#### In Case of Two Machines

**Machine 1:**

```sh
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.2
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.10.1 dev eth0
```

**Machine 2:**

```sh
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.1
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.60.1 dev eth0
```

#### In Case of Three Machines

**Machine 1 (Host 1):**

```sh
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.1
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.10.2 dev eth0
```

**Machine 2 (Router):**

```sh
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.20.2
    netmask 255.255.255.0
    broadcast 10.20.20.255
    network 10.20.20.0

iface eth1 inet static
    address 10.20.10.2
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0
```

**Machine 3 (Host 2):**

```sh
auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.20.1
    netmask 255.255.255.0
    broadcast 10.20.20.255
    network 10.20.20.0

up route add default gw 10.20.20.2 dev eth0
```

**Explanation**: This configuration assigns static IP addresses to each machine and sets up default gateway routes to enable communication between them on the same subnet.

---

### 3. About the `/etc/network/interfaces` File

The `/etc/network/interfaces` file is used in Debian-based Linux distributions (such as Debian, Ubuntu, etc.) to configure network interfaces. This file allows you to define static IP addresses, DHCP settings, and other network parameters for each interface on your system.

**Key Sections of the File**:

1. **auto**: Specifies which interfaces should be automatically brought up when the system boots.

    - `auto lo eth0` means both `lo` (loopback) and `eth0` (Ethernet) interfaces will be brought up automatically.

2. **iface**: Defines the configuration for a specific interface.

    - `iface lo inet loopback` configures the loopback interface.
    - `iface eth0 inet static` configures the `eth0` interface with a static IP address.

3. **Static IP Configuration**:

    - `address`: The IP address assigned to the interface.
    - `netmask`: The subnet mask for the network.
    - `broadcast`: The broadcast address for the network.
    - `network`: The network address.

4. **up route add default gw**: Adds a default gateway route when the interface is brought up.

---

### 4. Manual vs. `iproute2` or `net-tools`

You can configure network interfaces either manually by editing the `/etc/network/interfaces` file or dynamically using command-line tools like `iproute2` or `net-tools`.

#### Manual Configuration

Editing the `/etc/network/interfaces` file is a manual method that requires you to specify all the network settings in the file. This method is persistent across reboots because the configurations are saved in the file and applied every time the system boots.

#### Using `iproute2`

`iproute2` is a collection of utilities for networking and traffic control. The `ip` command is part of this collection and is used to configure network interfaces, routes, and tunnels dynamically.

**Example commands:**

```sh
sudo ip addr add 10.20.10.2/24 dev eth0
sudo ip link set dev eth0 up
sudo ip route add default via 10.20.10.1
```

These commands add an IP address, bring up the interface, and set the default route.

#### Using `net-tools`

`net-tools` is an older suite of networking utilities, including `ifconfig`, `route`, and others. While still in use, it is gradually being replaced by `iproute2`.

**Example commands:**

```sh
sudo ifconfig eth0 10.20.10.2 netmask 255.255.255.0 up
sudo route add default gw 10.20.10.1
```

These commands perform similar actions as the `iproute2` commands but use the older tools.

**Conclusion**: Using the `/etc/network/interfaces` file is best for persistent configurations. For temporary changes or testing, using `iproute2` or `net-tools` commands is more flexible and does not require a system reboot.

---

### 5. Start Script for Two Machines

#### Start Script

```sh
#!/bin/bash

# Create a bridge device named br1
sudo ip link add name br1 type bridge
# Set the bridge device br1 up
sudo ip link set br1 up

# Create a tap device named vport11
sudo ip tuntap add mode tap vport11
# Set the tap device vport11 up
sudo ip link set vport11 up
# Add the tap device vport11 to the bridge br1
sudo ip link set vport11 master br1

# Create a tap device named vport12
sudo ip tuntap add mode tap vport12
# Set the tap device vport12 up
sudo ip link set vport12 up
# Add the tap device vport12 to the bridge br1
sudo ip link set vport12 master br1

# Start the first virtual machine h1 using QEMU
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh1.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

# Start the second virtual machine h2 using QEMU
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh2.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

#### Explanation of the Start Script Command

1. **Create a bridge device named br1**:

    ```sh
    sudo ip link add name br1 type bridge
    ```

    - Adds a new network bridge device named `br1`.

2. **Set the bridge device br1 up**:

    ```sh
    sudo ip link set br1 up
    ```

    - Brings the bridge device `br1` up (activates it).

3. **Create a tap device named vport11**:

    ```sh
    sudo ip tuntap add mode tap vport11
    ```

    - Creates a new TAP device named `vport11`.

4. **Set the tap device vport11 up**:

    ```sh
    sudo ip link set vport11 up
    ```

    - Brings the TAP device `vport11` up (activates it).

5. **Add the tap device vport11 to the bridge br1**:

    ```sh
    sudo ip link set vport11 master br1
    ```

    - Adds the TAP device `vport11` to the bridge `br1`.

6. **Create a tap device named vport12**:

    ```sh
    sudo ip tuntap add mode tap vport12
    ```

    - Creates a new TAP device named `vport12`.

7. **Set the tap device vport12 up**:

    ```sh
    sudo ip link set vport12 up
    ```

    - Brings the TAP device `vport12` up (activates it).

8. **Add the tap device vport12 to the bridge br1**:

    ```sh
    sudo ip link set vport12 master br1
    ```

    - Adds the TAP device `vport12` to the bridge `br1`.

9. **Start the first virtual machine h1 using QEMU**:

    ```sh
    sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh1.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h1.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
        -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
        -name h1 -daemonize --append "root=/dev/vda rw"
    ```

    - **qemu-system-x86_64**: Runs the QEMU emulator for x86_64 architecture.
    - **-kernel bzImageh1.bin**: Specifies the kernel image for the VM.
    - **-m 1G**: Allocates 1 GB of RAM to the VM.
    - **-drive "file=...,if=virtio,format=raw"**: Specifies the disk image using VirtIO for better performance.
    - **-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B'**: Adds a VirtIO network device with the specified MAC address.
    - **-netdev tap,id=net0,ifname=vport11,script=no,downscript=no**: Configures the network backend using the TAP device `vport11`.
    - **-name h1**: Names the VM as `h1`.
    - **-daemonize**: Runs QEMU in the background.
    - **--append "root=/dev/vda rw"**: Passes kernel parameters to mount the root filesystem as read-write.

10. **Start the second virtual machine h2 using QEMU**:

    ```sh
    sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh2.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h2.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
        -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
        -name h2 -daemonize --append "root=/dev/vda rw"
    ```

    - Similar to the previous QEMU command, but for the second VM (`h2`) using the TAP device `vport12`.

---

### 6. Cleanup Script for Two Machines

#### Cleanup Script

```sh
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
```

#### Explanation of the Cleanup Script

1. **Detach the tap device vport11 from its bridge**:

    ```sh
    sudo ip link set dev vport11 nomaster
    ```

    - `ip link set dev vport11 nomaster`: Detaches the TAP device `vport11` from its bridge.

2. **Delete the tap device vport11**:

    ```sh
    sudo ip tuntap del mode tap vport11
    ```

    - `ip tuntap del mode tap vport11`: Deletes the TAP device `vport11`.

3. **Detach the tap device vport12 from its bridge**:

    ```sh
    sudo ip link set dev vport12 nomaster
    ```

    - `ip link set dev vport12 nomaster`: Detaches the TAP device `vport12` from its bridge.

4. **Delete the tap device vport12**:

    ```sh
    sudo ip tuntap del mode tap vport12
    ```

    - `ip tuntap del mode tap vport12`: Deletes the TAP device `vport12`.

5. **Delete the bridge device br1**:

    ```sh
    sudo ip link delete dev br1
    ```

    - `ip link delete dev br1`: Deletes the bridge device `br1`.

---

### 7. Start Script for Three Machines

#### Start Script

```sh
#!/bin/bash

# Create bridge devices br1 and br2
sudo ip link add name br1 type bridge
sudo ip link set br1 up

sudo ip link add name br2 type bridge
sudo ip link set br2 up

# Create and attach TAP devices to br1
sudo ip tuntap add mode tap vport11
sudo ip link set vport11 up
sudo ip link set vport11 master br1

sudo ip tuntap add mode tap vport12
sudo ip link set vport12 up
sudo ip link set vport12 master br1

# Create and attach TAP devices to br2
sudo ip tuntap add mode tap vport21
sudo ip link set vport21 up
sudo ip link set vport21 master br2

sudo ip tuntap add mode tap vport22
sudo ip link set vport22 up
sudo ip link set vport22 master br2

# Start virtual machine h1
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImageh1.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

# Start virtual machine rt2 (Router)
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImagert2.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/rt2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' \
    -netdev tap,id=net1,ifname=vport22,script=no,downscript=no \
    -name rt2 -daemonize --append "root=/dev/vda rw"

# Start virtual machine h2
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImageh2.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport21,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

#### Explanation

1. **Create bridge devices br1 and br2**:

    ```sh
    sudo ip link add name br1 type bridge
    sudo ip link set br1 up

    sudo ip link add name br2 type bridge
    sudo ip link set br2 up
    ```

    - Adds and activates two network bridge devices named `br1` and `br2`.

2. **Create and attach TAP devices to br1**:

    ```sh
    sudo ip tuntap add mode tap vport11
    sudo ip link set vport11 up
    sudo ip link set vport11 master br1

    sudo ip tuntap add mode tap vport12
    sudo ip link set vport12 up
    sudo ip link set vport12 master br1
    ```

    - Creates two TAP devices (`vport11` and `vport12`), brings them up, and attaches them to bridge `br1`.

3. **Create and attach TAP devices to br2**:

    ```sh
    sudo ip tuntap add mode tap vport21
    sudo ip link set vport21 up
    sudo ip link set vport21 master br2

    sudo ip tuntap add mode tap vport22
    sudo ip link set vport22 up
    sudo ip link set vport22 master br2
    ```

    - Creates two TAP devices (`vport21` and `vport22`), brings them up, and attaches them to bridge `br2`.

4. **Start virtual machine h1**:

    ```sh
    sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImageh1.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/h1.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
        -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
        -name h1 -daemonize --append "root=/dev/vda rw"
    ```

    - Launches VM `h1` connected via TAP device `vport11`.

5. **Start virtual machine rt2 (Router)**:

    ```sh
    sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImagert2.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/rt2.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' \
        -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
        -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' \
        -netdev tap,id=net1,ifname=vport22,script=no,downscript=no \
        -name rt2 -daemonize --append "root=/dev/vda rw"
    ```

    - Launches VM `rt2` acting as a router, connected via TAP devices `vport12` and `vport22`.

6. **Start virtual machine h2**:

    ```sh
    sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms3/bzImageh2.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms3/h2.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
        -netdev tap,id=net0,ifname=vport21,script=no,downscript=no \
        -name h2 -daemonize --append "root=/dev/vda rw"
    ```

    - Launches VM `h2` connected via TAP device `vport21`.

---

### 8. Cleanup Script for Three Machines

#### Script

```sh
#!/bin/bash

# Detach and delete TAP devices from br1
sudo ip link set dev vport11 nomaster
sudo ip tuntap del mode tap vport11

sudo ip link set dev vport12 nomaster
sudo ip tuntap del mode tap vport12

# Detach and delete TAP devices from br2
sudo ip link set dev vport21 nomaster
sudo ip tuntap del mode tap vport21

sudo ip link set dev vport22 nomaster
sudo ip tuntap del mode tap vport22

# Delete bridge devices br1 and br2
sudo ip link delete dev br1
sudo ip link delete dev br2
```

#### Explanation

1. **Detach and delete TAP devices from br1**:

    ```sh
    sudo ip link set dev vport11 nomaster
    sudo ip tuntap del mode tap vport11

    sudo ip link set dev vport12 nomaster
    sudo ip tuntap del mode tap vport12
    ```

    - Detaches and deletes TAP devices `vport11` and `vport12` from bridge `br1`.

2. **Detach and delete TAP devices from br2**:

    ```sh
    sudo ip link set dev vport21 nomaster
    sudo ip tuntap del mode tap vport21

    sudo ip link set dev vport22 nomaster
    sudo ip tuntap del mode tap vport22
    ```

    - Detaches and deletes TAP devices `vport21` and `vport22` from bridge `br2`.

3. **Delete bridge devices br1 and br2**:

    ```sh
    sudo ip link delete dev br1
    sudo ip link delete dev br2
    ```

    - Deletes the bridge devices `br1` and `br2`.

### Enabling IP Forwarding on the Router (rt2)

In the case of three devices, one of the virtual machines (`rt2`) acts as a router to route traffic between the other two devices (`h1` and `h2`). This setup is essential for testing and simulating static routing configurations. The router (`rt2`) ensures that packets are properly forwarded between the isolated networks of `h1` and `h2`.

To enable IP forwarding on the router (`rt2`), you need to modify the kernel parameter in the `/proc/sys/net/ipv4/ip_forward` file. This can be done by writing `1` to this file to enable routing or `0` to disable it.

#### Enabling IP Forwarding on the Router

To enable routing, execute the following command on the router (`rt2`):

```sh
echo 1 > /proc/sys/net/ipv4/ip_forward
```

To disable routing, execute the following command:

```sh
echo 0 > /proc/sys/net/ipv4/ip_forward
```

**Note**: These commands are crucial for ensuring that the router can forward packets between the connected networks, facilitating the simulation of static routing in a virtualized environment.

To make IP forwarding persistent across reboots, add the following line to `/etc/sysctl.conf`:

```sh
net.ipv4.ip_forward = 1
```

Then apply the changes with:

```sh
sudo sysctl -p
```

---

## Resources

-   [IPv4 Classes and Private IP Ranges](https://www.meridianoutpost.com/resources/articles/IP-classes.php)
-   [Linux `ip` Command Examples](https://www.tecmint.com/ip-command-examples/)
-   [QEMU Documentation](https://www.qemu.org/documentation/)
-   [TUN/TAP Interface Configuration](https://www.kernel.org/doc/Documentation/networking/tuntap.txt)
-   [Virtualization Host Configuration and Guest Installation Guide](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/6/html/virtualization_host_configuration_and_guest_installation_guide/index#idm140270648332048)
-   [Virtio: An I/O virtualization framework for Linux](https://developer.ibm.com/articles/l-virtio/)

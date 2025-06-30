# Bootloader Serial Protocol (BSP)

> **Purpose:** Reliable, scriptable firmware delivery from PC to embedded target over UART  
> **Version:** v0.9 · *Last updated: YYYY-MM-DD*

---

<details>
<summary><strong>Contents</strong></summary>

- [Bootloader Serial Protocol (BSP)](#bootloader-serial-protocol-bsp)
  - [1 · Scope](#1--scope)
  - [2 · Architecture](#2--architecture)
    - [2.1 Layered View](#21-layered-view)
    - [2.2 Command Frame (CRA Header)](#22-command-frame-cra-header)
    - [2.3 Response Frame](#23-response-frame)
  - [3 · Data Transfer Layer (DTL)](#3--data-transfer-layer-dtl)
  - [4 · Physical Layer](#4--physical-layer)
  - [5 · Timing \& Retries](#5--timing--retries)
  - [6 · Interaction Sequences](#6--interaction-sequences)
    - [6.1 Full Flash Flow](#61-full-flash-flow)
    - [6.2 Error \& Retry](#62-error--retry)
  - [7 · Reference Tables](#7--reference-tables)
    - [7.1 Command IDs](#71-command-ids)
    - [7.2 Status Codes](#72-status-codes)
    - [7.3 CRC-16 Parameters](#73-crc-16-parameters)
    - [7.4 SLIP Special Bytes](#74-slip-special-bytes)
  - [8 · Next Steps](#8--next-steps)

</details>

---

## 1 · Scope

Enable a host CLI (Python) to:

- **Erase**, **program**, **verify**, and **run** flash on a remote MCU
- **Query** transfer progress or **abort** safely
- Operate over a simple **3-wire UART** (TX, RX, GND) with optional RTS/CTS

A single CRA transaction follows:

```

Host → Command → Target
Host ← Response ← Target
Host → ACK → Target

```

---

## 2 · Architecture

### 2.1 Layered View

![Client/Server Layered Architecture](image/client_server_layered_architecture.png)

- **Application Layer**: Bootloader state machine & CLI
- **Command Layer**: CRA framing, priorities & ACK
- **Data Transfer Layer**: Fragmentation, CRC-16, SLIP
- **Physical Layer**: UART byte stream

---

### 2.2 Command Frame (CRA Header)

| Byte(s) | Field            | Description                      |
| :-----: | :--------------- | :------------------------------- |
|    0    | **Session ID**   | 8-bit handle, echoed in response |
|    1    | **Flags**        | b3 = ACK flag, b2–b0 = priority  |
|    2    | **Command Code** | See [§7.1](#71-command-ids)      |
|   3–4   | **Payload Len**  | Little-endian, 0–60 bytes        |
|    …    | **Payload**      | Command-specific parameters      |

> **TODO:** Insert PlantUML bit-level map.

---

### 2.3 Response Frame

| Byte(s) | Field          | Description                  |
| :-----: | :------------- | :--------------------------- |
|    0    | **Session ID** | Mirrors request              |
|    1    | **Status**     | See [§7.2](#72-status-codes) |
|   2–3   | **Resp Len**   | Little-endian                |
|    …    | **Payload**    | Optional data                |

> **TODO:** Insert PlantUML byte-layout.

---

## 3 · Data Transfer Layer (DTL)

| Field  | Size    | Description                       |
| :----: | :------ | :-------------------------------- |
|  Seq#  | 2 B     | 0–65 535, wraps                   |
|  Len   | 2 B     | Data length                       |
|  Data  | 0–256 B | Aligned to flash line width       |
| CRC-16 | 2 B     | CCITT-False over (Seq, Len, Data) |
|  SLIP  | —       | 0xC0/0xDB framing & escaping      |

> **Note:** Next chunk is sent only after ACK(0×00) is confirmed.

---

## 4 · Physical Layer

| Parameter    | Value                           |
| :----------- | :------------------------------ |
| Baud Rate    | **115 200 bps**                 |
| Word Format  | 8 data bits, no parity, 1 stop  |
| Flow Control | RTS/CTS (preferred) or XON/XOFF |
| Idle Timeout | 2 × max frame transmission time |

---

## 5 · Timing & Retries

|     Phase     | Host Timeout | Target Timeout | Retries |
| :-----------: | :----------: | :------------: | :-----: |
| Response wait |    200 ms    |       —        |    5    |
|   ACK wait    |      —       |     200 ms     |    5    |
| Chunk verify  |    300 ms    |       —        |    3    |

---

## 6 · Interaction Sequences

### 6.1 Full Flash Flow

> **TODO:** Add PlantUML sequence for:
> ERASE_FLASH → WRITE_CHUNK × N → VERIFY_CHUNK × N → RESET_AND_RUN

### 6.2 Error & Retry

> **TODO:** Add PlantUML sequence illustrating CRC failure & auto-retry.

---

## 7 · Reference Tables

### 7.1 Command IDs

| Code | Mnemonic       | Direction | Comments            |
| :--: | :------------- | :-------: | :------------------ |
| 0x10 | ERASE_FLASH    | Host→MCU  | Full or partial     |
| 0x11 | WRITE_CHUNK    | Host→MCU  | Up to 256 bytes     |
| 0x12 | VERIFY_CHUNK   | Host→MCU  | CRC check           |
| 0x13 | RESET_AND_RUN  | Host→MCU  | Jump to application |
| 0x14 | ABORT          | Host→MCU  | Cancel session      |
| 0x20 | PROGRESS_QUERY | Host→MCU  | % complete          |

---

### 7.2 Status Codes

| Value | Description   |
| :---: | :------------ |
| 0×00  | OK            |
| 0×01  | Generic error |
| 0×02  | Flash failure |
| 0×03  | Bad CRC       |
| 0×04  | Timeout       |

---

### 7.3 CRC-16 Parameters

- **Polynomial:** 0x1021
- **Initial Value:** 0xFFFF
- **Reflect In/Out:** No
- **XOR Out:** 0x0000

---

### 7.4 SLIP Special Bytes

| Name      | Value | Purpose                      |
| :-------- | :---- | :--------------------------- |
| `END`     | 0xC0  | Frame delimiter              |
| `ESC`     | 0xDB  | Escape indicator             |
| `ESC_END` | 0xDC  | Encodes literal 0xC0 in data |
| `ESC_ESC` | 0xDD  | Encodes literal 0xDB in data |

---

## 8 · Next Steps

1. Replace every **TODO** with final PlantUML diagrams.
2. Implement host CLI (`serial_bsp_cli.py`) with argparse & pyserial.
3. Develop STM32 bootloader modules (`bsp_command.c`, `bsp_dtl.c`, …).

---

# Writing and Running ARM Assembly on x86_64 Ubuntu

A comprehensive guide to setting up a cross-toolchain, writing ARM assembly programs, running them under QEMU, and debugging. Designed for educators and students working on x86_64 Ubuntu systems.

---

## Table of Contents

-   [Writing and Running ARM Assembly on x86_64 Ubuntu](#writing-and-running-arm-assembly-on-x86_64-ubuntu)
    -   [Table of Contents](#table-of-contents)
    -   [Introduction](#introduction)
    -   [Prerequisites](#prerequisites)
    -   [Install Cross-Toolchain \& QEMU](#install-cross-toolchain--qemu)
    -   [Writing Your First ARM Assembly Program](#writing-your-first-arm-assembly-program)
        -   [32-bit ARM (ARMv7) Example](#32-bit-arm-armv7-example)
        -   [64-bit ARM (AArch64) Example](#64-bit-arm-aarch64-example)
    -   [Assemble, Link \& Run](#assemble-link--run)
        -   [32-bit Workflow](#32-bit-workflow)
        -   [64-bit Workflow](#64-bit-workflow)
    -   [Inspect \& Debug](#inspect--debug)
        -   [Disassemble with `objdump`](#disassemble-with-objdump)
        -   [Debug with GDB](#debug-with-gdb)
    -   [System Calls in ARM](#system-calls-in-arm)
        -   [Common 32-bit Syscalls](#common-32-bit-syscalls)
        -   [Common 64-bit Syscalls](#common-64-bit-syscalls)
    -   [More Assembly Examples](#more-assembly-examples)
        -   [Adding Two Numbers (ARMv7)](#adding-two-numbers-armv7)
        -   [Loop and Conditionals (AArch64)](#loop-and-conditionals-aarch64)
    -   [C Program Compilation for ARM](#c-program-compilation-for-arm)
        -   [Simple C Example](#simple-c-example)
        -   [Compiling \& Inspecting](#compiling--inspecting)
            -   [Compile for ARMv7](#compile-for-armv7)
            -   [Run with QEMU](#run-with-qemu)
            -   [Disassemble with objdump](#disassemble-with-objdump-1)
            -   [Compile for AArch64](#compile-for-aarch64)
            -   [Run with QEMU](#run-with-qemu-1)
            -   [Disassemble](#disassemble)
    -   [Alternative Approaches](#alternative-approaches)
    -   [Next Steps \& Resources](#next-steps--resources)

---

## Introduction

ARM is one of the most popular RISC architectures, powering embedded systems, smartphones, and single-board computers like the Raspberry Pi. This guide allows you to develop and test ARM assembly from a standard x86_64 Ubuntu PC.

## Prerequisites

-   Ubuntu (x86_64)
-   sudo/root access
-   Basic Linux terminal usage
-   Assembly fundamentals (registers, memory, syscalls)

## Install Cross-Toolchain & QEMU

```bash
sudo apt update

# For 32-bit ARM
sudo apt install -y gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi qemu-user

# For 64-bit ARM
sudo apt install -y gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu qemu-user
```

| Target           | Assembler / Linker            | GCC Compiler            | Emulator       |
| ---------------- | ----------------------------- | ----------------------- | -------------- |
| 32-bit (ARMv7)   | `arm-linux-gnueabi-as` / `ld` | `arm-linux-gnueabi-gcc` | `qemu-arm`     |
| 64-bit (AArch64) | `aarch64-linux-gnu-as` / `ld` | `aarch64-linux-gnu-gcc` | `qemu-aarch64` |

## Writing Your First ARM Assembly Program

### 32-bit ARM (ARMv7) Example

File: `hello32.s`

```asm
.global _start
.text
_start:
    MOV     r7, #4
    MOV     r0, #1
    LDR     r1, =msg
    MOV     r2, #13
    SWI     0

    MOV     r7, #1
    MOV     r0, #0
    SWI     0

.data
msg:
    .ascii "Hello, ARM32!\n"
```

### 64-bit ARM (AArch64) Example

File: `hello64.s`

```asm
.global _start
.text
_start:
    MOV     x8, #64
    MOV     x0, #1
    ADRP    x1, msg@PAGE
    ADD     x1, x1, msg@PAGEOFF
    MOV     x2, #13
    SVC     #0

    MOV     x8, #93
    MOV     x0, #0
    SVC     #0

.data
msg:
    .ascii "Hello, ARM64!\n"
```

## Assemble, Link & Run

### 32-bit Workflow

```bash
arm-linux-gnueabi-as -o hello32.o hello32.s
arm-linux-gnueabi-ld -o hello32.elf hello32.o
qemu-arm ./hello32.elf
```

### 64-bit Workflow

```bash
aarch64-linux-gnu-as -o hello64.o hello64.s
aarch64-linux-gnu-ld -o hello64.elf hello64.o
qemu-aarch64 ./hello64.elf
```

## Inspect & Debug

### Disassemble with `objdump`

```bash
arm-linux-gnueabi-objdump -d hello32.elf
aarch64-linux-gnu-objdump -d hello64.elf
```

### Debug with GDB

```bash
sudo apt install gdb-multiarch

# Start QEMU in one terminal:
qemu-arm -g 1234 ./hello32.elf

# In another terminal:
gdb-multiarch hello32.elf
(gdb) set architecture arm
(gdb) target remote :1234
```

## System Calls in ARM

### Common 32-bit Syscalls

| Name  | r7 (ID) | Args in    |
| ----- | ------- | ---------- |
| write | 4       | r0, r1, r2 |
| read  | 3       | r0, r1, r2 |
| exit  | 1       | r0         |

### Common 64-bit Syscalls

| Name  | x8 (ID) | Args in    |
| ----- | ------- | ---------- |
| write | 64      | x0, x1, x2 |
| read  | 63      | x0, x1, x2 |
| exit  | 93      | x0         |

## More Assembly Examples

### Adding Two Numbers (ARMv7)

```asm
.global _start
.text
_start:
    MOV r0, #10
    MOV r1, #20
    ADD r2, r0, r1

    MOV r7, #1
    MOV r0, #0
    SWI 0
```

### Loop and Conditionals (AArch64)

```asm
.global _start
.text
_start:
    MOV x0, #5
loop:
    SUBS x0, x0, #1
    BGT loop

    MOV x8, #93
    MOV x0, #0
    SVC #0
```

## C Program Compilation for ARM

### Simple C Example

File: `sum.c`

```c
#include <stdio.h>

int main() {
    int a = 5, b = 7;
    int sum = a + b;
    printf("Sum: %d\n", sum);
    return 0;
}
```

### Compiling & Inspecting

#### Compile for ARMv7

```bash
arm-linux-gnueabi-gcc -o sum32.elf sum.c
```

#### Run with QEMU

```bash
qemu-arm ./sum32.elf
```

#### Disassemble with objdump

```bash
arm-linux-gnueabi-objdump -d sum32.elf | less
```

#### Compile for AArch64

```bash
aarch64-linux-gnu-gcc -static -o sum64.elf sum.c
```

#### Run with QEMU

```bash
qemu-aarch64 ./sum64.elf
```

#### Disassemble

```bash
aarch64-linux-gnu-objdump -d sum64.elf | less
```

## Alternative Approaches

-   `qemu-system-arm` + rootfs for full emulated OS
-   Docker with `--platform=linux/arm64` and `qemu-user-static`
-   Native development on Raspberry Pi or STM32 boards

## Next Steps & Resources

-   [ARM Cortex-M Assembly Programming Book](https://www.amazon.com/ARM-Assembly-Language-Programming-Cortex-M/dp/1469998745)
-   [Godbolt Compiler Explorer](https://godbolt.org)
-   [ARM Linux Syscall Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)
-   Use `strace`, `objdump`, and `gdb` frequently to master low-level behavior

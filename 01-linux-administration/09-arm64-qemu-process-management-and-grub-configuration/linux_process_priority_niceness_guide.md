# Priority and Niceness in Linux

## Table of Contents

1. [Introduction](#introduction)
2. [Understanding Process Priority and Niceness](#understanding-process-priority-and-niceness)
   - [What is Process Priority?](#what-is-process-priority)
   - [What is Niceness?](#what-is-niceness)
   - [Relationship Between Priority and Niceness](#relationship-between-priority-and-niceness)
3. [Managing Priority and Niceness](#managing-priority-and-niceness)
   - [Viewing Process Priority and Niceness](#viewing-process-priority-and-niceness)
   - [Changing Niceness with `nice` and `renice`](#changing-niceness-with-nice-and-renice)
   - [Changing Priority with `chrt`](#changing-priority-with-chrt)
4. [Impact of Priority and Niceness](#impact-of-priority-and-niceness)
   - [CPU Scheduling](#cpu-scheduling)
   - [Process Behavior](#process-behavior)
5. [Best Practices](#best-practices)
6. [Examples](#examples)
   - [Starting a Process with a Specific Niceness](#starting-a-process-with-a-specific-niceness)
   - [Changing the Niceness of an Existing Process](#changing-the-niceness-of-an-existing-process)
   - [Using `renice` in Scripts](#using-renice-in-scripts)
   - [Adjusting Real-Time Priority with `chrt`](#adjusting-real-time-priority-with-chrt)
7. [Commands and Tools](#commands-and-tools)
   - [`nice`](#nice)
   - [`renice`](#renice)
   - [`top` and `htop`](#top-and-htop)
   - [`chrt`](#chrt)
8. [Troubleshooting](#troubleshooting)
9. [References](#references)

---

## Introduction

In Linux, **process scheduling** determines the order and amount of CPU time allocated to various processes. Two key concepts influencing this scheduling are **priority** and **niceness**. Understanding and managing these parameters allows system administrators and users to optimize system performance, ensure critical tasks receive necessary resources, and maintain overall system responsiveness.

This guide delves into the intricacies of process priority and niceness, providing insights into how they function, how to manage them effectively, and best practices for their application.

---

## Understanding Process Priority and Niceness

### What is Process Priority?

**Process Priority** is a numerical value that influences the scheduling of processes by the Linux kernel. It determines the order in which processes are given access to CPU resources. Higher-priority processes are scheduled to run before lower-priority ones.

**Key Points:**

- **Range:** In Linux, real-time priorities range from `1` (lowest real-time priority) to `99` (highest real-time priority). Normal (non-real-time) processes have priorities typically ranging from `-20` (highest priority) to `19` (lowest priority).
- **Scheduling Classes:** Linux categorizes processes into different scheduling classes. The two primary classes influenced by priority are:
  - **Real-Time Scheduling (`SCHED_FIFO`, `SCHED_RR`):** Processes with real-time priorities.
  - **Normal Scheduling (`SCHED_OTHER`):** Standard processes with niceness values.

### What is Niceness?

**Niceness** is a user-space concept that adjusts the priority of a process in the normal scheduling class (`SCHED_OTHER`). It allows users to influence the scheduler's decisions without directly setting real-time priorities.

**Key Points:**

- **Range:** Niceness values range from `-20` (most favorable to the process, highest priority) to `19` (least favorable, lowest priority).

- **Default Niceness:** By default, processes start with a niceness of `0`.

- **Adjusting Niceness:** Users can adjust niceness to make a process more "nice" (less CPU time) or less "nice" (more CPU time) relative to other processes.

### Relationship Between Priority and Niceness

While **priority** directly affects the scheduling order, **niceness** provides a more flexible and user-friendly way to influence a process's priority within its scheduling class. Adjusting niceness changes the dynamic priority of a process, allowing the scheduler to balance CPU time among various processes based on their niceness values.

**Illustrative Summary:**

| **Concept** | **Scope**          | **Range** | **Effect**                                        |
| ----------- | ------------------ | --------- | ------------------------------------------------- |
| Priority    | Direct scheduling  | -20 to 19 | Higher priority processes are scheduled first.    |
| Niceness    | Indirect influence | -20 to 19 | Adjusts the dynamic priority within normal class. |

---

## Managing Priority and Niceness

Effectively managing process priority and niceness is crucial for optimizing system performance and ensuring critical tasks receive adequate resources.

### Viewing Process Priority and Niceness

You can view the priority and niceness of running processes using various tools:

1. **`ps` Command:**

   ```bash
   ps -eo pid,ppid,cmd,ni,pri
   ```

   - **`pid`:** Process ID
   - **`ppid`:** Parent Process ID
   - **`cmd`:** Command name
   - **`ni`:** Niceness value
   - **`pri`:** Priority

2. **`top` Command:**

   - Launch `top`:

     ```bash
     top
     ```

   - Within `top`, you can see the `NI` (niceness) and `PR` (priority) columns.

3. **`htop` Command:**

   - If `htop` is installed, it provides a more user-friendly interface:

     ```bash
     htop
     ```

   - Displays niceness and priority alongside other process information.

### Changing Niceness with `nice` and `renice`

**1. Using `nice` to Start a Process with a Specific Niceness:**

The `nice` command launches a new process with a specified niceness value.

**Syntax:**

```bash
nice -n <niceness_value> <command>
```

- **`<niceness_value>`:** Desired niceness (`-20` to `19`)
- **`<command>`:** The command to execute

**Example:**

Start a script with a niceness of `10` (less favorable):

```bash
nice -n 10 ./my_script.sh
```

**2. Using `renice` to Change Niceness of an Existing Process:**

The `renice` command modifies the niceness of running processes.

**Syntax:**

```bash
renice <niceness_value> -p <pid>
```

- **`<niceness_value>`:** New niceness (`-20` to `19`)
- **`<pid>`:** Process ID

**Example:**

Change the niceness of process `1234` to `5`:

```bash
renice 5 -p 1234
```

**Bulk Renicing:**

You can also renice multiple processes simultaneously:

```bash
renice 10 -p 1234 5678 91011
```

**Renice by User:**

To renice all processes owned by a specific user:

```bash
renice 15 -u username
```

### Changing Priority with `chrt`

The `chrt` command sets or retrieves the real-time scheduling attributes of a process.

**Syntax:**

```bash
chrt [options] <priority> <command>
```

- **`[options]`:** Scheduling policy options (`-f` for `SCHED_FIFO`, `-r` for `SCHED_RR`, `-o` for `SCHED_OTHER`)
- **`<priority>`:** Priority value based on the scheduling policy
- **`<command>`:** The command to execute

**Example:**

Start a process with `SCHED_RR` (Round Robin) scheduling policy and priority `50`:

```bash
sudo chrt -r 50 ./my_realtime_task.sh
```

**Changing Priority of an Existing Process:**

```bash
sudo chrt -r -p 60 1234
```

- Sets process `1234` to `SCHED_RR` with priority `60`.

**Note:** Adjusting real-time priorities typically requires superuser privileges.

---

## Impact of Priority and Niceness

Understanding how priority and niceness affect system behavior is essential for effective process management.

### CPU Scheduling

- **Higher Priority:** Processes with higher priority values are scheduled to run before those with lower priorities. In real-time scheduling classes, priority has a more pronounced effect.
- **Lower Priority:** Processes with lower priority (higher niceness values) receive less CPU time, allowing more critical tasks to utilize CPU resources efficiently.

**Impact:**

- **High Priority Processes:** Can lead to better performance for critical applications but may starve lower-priority processes if overused.
- **Low Priority Processes:** Ensure that background tasks do not interfere with the responsiveness of interactive or critical applications.

### Process Behavior

- **Niceness Adjustment:** By increasing niceness, you make a process "nicer," meaning it yields more CPU time to other processes. Decreasing niceness makes a process less "nice," allowing it to consume more CPU time.

- **Real-Time Scheduling:** Processes in real-time scheduling classes (`SCHED_FIFO`, `SCHED_RR`) have stricter priority enforcement, suitable for tasks requiring immediate and consistent CPU access.

**Impact:**

- **Balanced System Performance:** Properly adjusted niceness values help maintain system balance, ensuring that no single process monopolizes CPU resources.

- **Responsiveness:** Interactive applications benefit from higher priority, enhancing user experience by making the system more responsive.

---

## Best Practices

1. **Avoid Negative Niceness Values as a Regular User:**

   - Lower niceness (higher priority) values require superuser privileges. Grant such privileges only when necessary to prevent potential system instability.

2. **Use Positive Niceness for Background Tasks:**

   - Assign higher niceness values to non-critical or background tasks to ensure they do not interfere with essential processes.

3. **Monitor System Performance:**

   - Regularly use tools like `top`, `htop`, or `ps` to monitor process priorities and resource usage, adjusting niceness values as needed.

4. **Limit Real-Time Processes:**

   - Real-time processes can monopolize CPU resources. Use them sparingly and only for tasks that genuinely require immediate execution.

5. **Automate Niceness Adjustments:**

   - Incorporate niceness adjustments in scripts or service configurations to maintain consistent behavior across system reboots or deployments.

6. **Document Changes:**

   - Keep records of any priority or niceness adjustments made to processes for future reference and troubleshooting.

7. **Use `systemd` for Managing Service Priorities:**

   - When using `systemd` to manage services, utilize its built-in mechanisms (`Nice=`, `IOSchedulingClass=`, etc.) to set priorities and niceness values.

8. **Ensure Minimal Impact on System Stability:**
   - Avoid setting extremely high or low niceness values that could adversely affect system performance or lead to resource starvation.

---

## Examples

### Starting a Process with a Specific Niceness

Use the `nice` command to start a process with a designated niceness.

**Example:**

Start a Python script with a niceness of `10`:

```bash
nice -n 10 python3 long_running_task.py
```

### Changing the Niceness of an Existing Process

Use the `renice` command to adjust the niceness of a running process.

**Example:**

Increase the niceness (lower priority) of process `5678` to `15`:

```bash
renice 15 -p 5678
```

### Using `renice` in Scripts

Incorporate `renice` within shell scripts to manage process priorities dynamically.

**Example Script:**

```bash
#!/bin/bash

# Start a background process with default niceness
./background_task.sh &

# Capture the PID of the background process
BG_PID=$!

# Wait for a few seconds
sleep 5

# Increase niceness to reduce CPU usage
renice 10 -p $BG_PID

echo "Adjusted niceness of process $BG_PID to 10."
```

### Adjusting Real-Time Priority with `chrt`

Use `chrt` to set real-time scheduling policies and priorities.

**Example:**

Start a C++ program with `SCHED_FIFO` policy and priority `30`:

```bash
sudo chrt -f 30 ./realtime_program
```

**Changing Priority of an Existing Real-Time Process:**

```bash
sudo chrt -f -p 35 2345
```

- Sets process `2345` to `SCHED_FIFO` with priority `35`.

---

## Commands and Tools

### `nice`

**Purpose:** Launch a new process with a specified niceness value.

**Syntax:**

```bash
nice -n <niceness_value> <command>
```

**Example:**

Start a backup script with a niceness of `5`:

```bash
nice -n 5 ./backup.sh
```

### `renice`

**Purpose:** Change the niceness of existing running processes.

**Syntax:**

```bash
renice <niceness_value> -p <pid>
renice <niceness_value> -u <username>
renice <niceness_value> -g <pgid>
```

**Examples:**

- **Single Process:**

  ```bash
  renice 10 -p 1234
  ```

- **All Processes of a User:**

  ```bash
  renice 15 -u johndoe
  ```

- **All Processes in a Process Group:**

  ```bash
  renice 20 -g 5678
  ```

### `top` and `htop`

**Purpose:** Monitor system processes and resource usage in real-time.

**Usage:**

- **`top`:**

  ```bash
  top
  ```

- **`htop` (more user-friendly, may require installation):**

  ```bash
  htop
  ```

**Features:**

- View process priorities (`PR`) and niceness (`NI`).
- Sort processes based on various criteria.
- Interactively change niceness values within `htop`.

### `chrt`

**Purpose:** Manipulate real-time scheduling attributes of a process.

**Syntax:**

```bash
chrt [options] <priority> <command>
chrt [options] -p <priority> <pid>
```

**Options:**

- `-f`: Use `SCHED_FIFO` (First In, First Out) scheduling policy.
- `-r`: Use `SCHED_RR` (Round Robin) scheduling policy.
- `-o`: Use `SCHED_OTHER` (default normal scheduling).

**Examples:**

- **Start a Process with `SCHED_RR` Policy:**

  ```bash
  sudo chrt -r 30 ./realtime_task.sh
  ```

- **Change the Scheduling Policy and Priority of an Existing Process:**

  ```bash
  sudo chrt -f -p 40 1234
  ```

### `ps`

**Purpose:** Report a snapshot of the current processes.

**Syntax:**

```bash
ps -eo pid,ppid,cmd,ni,pri
```

- **`pid`**: Process ID
- **`ppid`**: Parent Process ID
- **`cmd`**: Command name
- **`ni`**: Niceness value
- **`pri`**: Priority

**Example:**

```bash
ps -eo pid,ppid,cmd,ni,pri --sort=pri
```

### `pgrep` and `pkill`

**Purpose:** Search for or signal processes based on name and other attributes.

**Usage:**

- **`pgrep`:** Find process IDs.

  ```bash
  pgrep firefox
  ```

- **`pkill`:** Send signals to processes.

  ```bash
  pkill -SIGTERM firefox
  ```

---

## Troubleshooting

### Issue 1: Unable to Change Niceness of a Process

**Symptom:**

- Attempting to set a negative niceness value as a non-root user fails.

**Solution:**

- Only the superuser can set negative niceness values (increase process priority). To adjust niceness to a lower priority (positive values), regular users can do so.

**Example:**

Attempting to set niceness to `-5` as a regular user:

```bash
renice -5 -p 1234
```

**Error:**

```
renice: failed to set niceness for pid 1234: Operation not permitted
```

**Fix:**

Use `sudo` for privileged operations:

```bash
sudo renice -5 -p 1234
```

### Issue 2: Real-Time Process Starving Other Processes

**Symptom:**

- A real-time process consumes excessive CPU, making the system unresponsive.

**Solution:**

- Adjust the priority of the real-time process to a lower value.
- Limit the number of real-time processes running simultaneously.
- Implement proper scheduling within the real-time process to yield CPU time when appropriate.

**Example:**

Change the real-time priority of process `5678` from `50` to `30`:

```bash
sudo chrt -r -p 30 5678
```

### Issue 3: Changes to Niceness Not Taking Effect

**Symptom:**

- After adjusting niceness, the expected change in CPU usage is not observed.

**Solution:**

- Ensure that no other high-priority processes are dominating CPU usage.
- Verify that the niceness value was correctly applied using `ps` or `top`.
- Remember that niceness affects CPU scheduling but does not guarantee exact CPU allocation.

**Example:**

Check the niceness and priority:

```bash
ps -eo pid,cmd,ni,pri | grep my_process
```

### Issue 4: Daemon Processes Becoming Zombies

**Symptom:**

- Daemon processes appear as `<defunct>` in process listings.

**Solution:**

- Ensure that the daemon properly reaps child processes by handling `SIGCHLD` signals and calling `wait()` or `waitpid()`.
- Modify the daemon code to include a signal handler for `SIGCHLD`.

**Example:**

Add a `SIGCHLD` handler in the daemon:

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// Signal handler for SIGCHLD
void sigchld_handler(int signum) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    // Setup SIGCHLD handler
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    // Daemon code...
}
```

---

## References

- [Linux `nice` Command](https://man7.org/linux/man-pages/man1/nice.1.html)
- [Linux `renice` Command](https://man7.org/linux/man-pages/man1/renice.1.html)
- [Linux `chrt` Command](https://man7.org/linux/man-pages/man1/chrt.1.html)
- [Understanding Linux Process Priority](https://www.geeksforgeeks.org/understanding-linux-process-priority/)
- [Real-Time Scheduling in Linux](https://www.ibm.com/docs/en/linux-on-systems?topic=threads-real-time-scheduling)
- [Process Scheduling in Linux](https://www.tldp.org/LDP/tlk/kernel/process-scheduling.html)
- [Linux `ps` Command](https://man7.org/linux/man-pages/man1/ps.1.html)
- [Linux `top` Command](https://man7.org/linux/man-pages/man1/top.1.html)
- [Linux `htop` Command](https://hisham.hm/htop/)
- [System Administrators Handbook](https://www.amazon.com/System-Administrators-Handbook-Third-Microsoft/dp/0130300002)
- [Advanced Programming in the UNIX Environment](https://www.amazon.com/Advanced-Programming-UNIX-Environment-3rd/dp/0321637739) by W. Richard Stevens
- [Understanding the `nice` Value](https://www.gnu.org/software/coreutils/manual/html_node/nice-invocation.html)
- [Linux Kernel Documentation on Scheduling](https://www.kernel.org/doc/html/latest/scheduler/index.html)

# Custom Syscalls in xv6 (MIT RISC-V)

This repository contains the implementation of **5 custom system calls** added to the MIT xv6 (RISC-V) operating system to extend its process management and diagnostic capabilities.

---

## Implemented Syscalls

### 1. `schedtest` — Scheduler Statistics

Reports the total number of context switches that have occurred since the operating system was booted.

* **Usage:**
    ```sh
    schedtest
    ```
* **Example Output:**
    ```
    Total context switches since boot: 46
    ```
* **Key Files Changed:** `kernel/sysproc.c`, `user/schedtest.c`, `kernel/syscall.h`, `kernel/syscall.c`, `user/user.h`, `user/usys.pl`, `Makefile`

---

### 2. `psinfo` — Process Information

Displays a list of all active processes, including their **Process ID (PID)**, **current state**, and **name**.

* **Usage:**
    ```sh
    psinfo
    ```
* **Example Output:**
    ```
    PID   STATE   NAME
    1     SLEEP   init
    2     SLEEP   sh
    3     RUN     psinfo
    ```
* **Key Files Changed:** `kernel/sysproc.c`, `user/psinfo.c`, `kernel/syscall.h`, `kernel/syscall.c`, `user/user.h`, `user/usys.pl`, `Makefile`

---

### 3. `getmeminfo` — Memory Usage Information

Returns comprehensive memory usage statistics for the calling process, including **code size**, **heap size**, **stack size**, **pages allocated**, and **page faults**.

* **Usage:**
    ```sh
    memtest
    ```
* **Key Files Changed:** `kernel/sysproc.c`, `kernel/proc.c`, `kernel/proc.h`, `kernel/memstat.h`, `user/memtest.c`, `kernel/syscall.h`, `kernel/syscall.c`, `user/user.h`, `user/usys.pl`, `Makefile`

---

### 4. `setpriority` — Priority-Based Scheduling

Modifies the execution priority of a specific process. The scheduler is modified to pick processes with the **lowest priority number first** (lower number = higher priority).

* **Usage:**
    ```sh
    setpriority <pid> <priority>
    ```
* **Examples:**
    ```sh
    setpriority 2 1    # Highest priority
    setpriority 2 10   # Default priority
    setpriority 2 20   # Lowest priority
    ```
* **Test Programs:** `testpriority`, `prioritytest`
* **Key Files Changed:** `kernel/sysproc.c`, `kernel/proc.c` (scheduler modification, priority in `allocproc` and `fork`), `kernel/proc.h`, `user/setpriority.c`, `user/testpriority.c`, `user/prioritytest.c`, `kernel/syscall.h`, `kernel/syscall.c`, `user/user.h`, `user/usys.pl`, `Makefile`

---

### 5. `getprocstatetest` — Process State Statistics

Reports the count of processes currently in key states, specifically **RUNNING**, **RUNNABLE**, and **SLEEPING**. Used to confirm correct real-time tracking of process state transitions.

* **Usage:**
    ```sh
    getprocstatetest
    ```
* **Example Output:**
    ```
    Process State Statistics:
    RUNNING:   1
    RUNNABLE:  0
    SLEEPING:  3
    ```
* **Key Files Changed:** `kernel/sysproc.c`, `kernel/proc.c`, `kernel/proc.h`, `user/getprocstatetest.c`, `kernel/syscall.h`, `kernel/syscall.c`, `user/user.h`, `user/usys.pl`, `Makefile`

---

##  Build & Run

Use the following commands to clean the environment, build the project, and start the xv6 operating system in QEMU.

```bash
make clean
make qemu

If you are using an explicit RISC-V toolchain, use these commands:

```bash
make clean
make TOOLPREFIX=riscv64-linux-gnu-
make TOOLPREFIX=riscv64-linux-gnu- qemu
```

-----

## Implementation Status

| Component          | Status |
| :----------------- | :----- |
| Syscall wiring     | ✅     |
| Kernel logic       | ✅     |
| User wrappers      | ✅     |
| Output tested      | ✅     |
| Clean build        | ✅     |

-----

## ⚠️ Notes

  * **Do not** modify the assigned syscall numbers unless absolutely necessary to avoid conflicts.
  * Always run `make clean` before rebuilding after pulling updates or making kernel changes.
  * Missing registration in `kernel/syscall.c` or `user/usys.pl` is a common error that can cause xv6 to freeze at boot.
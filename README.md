```markdown
# Custom Syscalls in xv6 (MIT RISC-V)

This repository contains the implementation of 5 custom **system calls** added to the MIT xv6 (RISC-V) operating system:

- `schedtest` — Scheduler Statistics
- `psinfo` — Process Information
- `getmeminfo` — Memory Usage Information
- `setpriority` — Priority-Based Scheduling
- `getprocstatetest` — Process State Statistics

---

## ✅ Implemented Syscalls

### 1. `schedtest`

**What it does:** Reports total number of context switches since boot.

**How to run:**
```sh
schedtest
```

**Output:**
```
Total context switches since boot: 46
```

**Files changed:**
- `kernel/syscall.h` — Added `SYS_schedstat` (22)
- `kernel/syscall.c` — Registered `sys_schedstat` in array
- `kernel/sysproc.c` — Implemented `sys_schedstat()`
- `user/user.h` — Added `schedstat()` declaration
- `user/usys.pl` — Added `schedstat` entry
- `user/schedtest.c` — User program
- `Makefile` — Added `_schedtest` to `UPROGS`

---

### 2. `psinfo`

**What it does:** Displays all active processes with PID, state, and name.

**How to run:**
```sh
psinfo
```

**Output:**
```
PID   STATE   NAME
1     SLEEP   init
2     SLEEP   sh
3     RUN     psinfo
```

**Files changed:**
- `kernel/syscall.h` — Added `SYS_psinfo` (23)
- `kernel/syscall.c` — Registered `sys_psinfo` in array
- `kernel/sysproc.c` — Implemented `sys_psinfo()`
- `user/user.h` — Added `psinfo()` declaration
- `user/usys.pl` — Added `psinfo` entry
- `user/psinfo.c` — User program
- `Makefile` — Added `_psinfo` to `UPROGS`

---

### 3. `getmeminfo`

**What it does:** Returns memory usage statistics (code, heap, stack, pages, pagefaults) for a process.

**How to run:**
```sh
memtest
```

**Files changed:**
- `kernel/syscall.h` — Added `SYS_getmeminfo` (24)
- `kernel/syscall.c` — Registered `sys_getmeminfo` in array
- `kernel/sysproc.c` — Implemented `sys_getmeminfo()`
- `kernel/proc.c` — Added memory statistics tracking (code_size, heap_size, stack_size, pagefaults)
- `kernel/proc.h` — Added memory statistics fields to process structure
- `kernel/memstat.h` — Memory statistics structure definition
- `user/user.h` — Added `getmeminfo()` declaration
- `user/usys.pl` — Added `getmeminfo` entry
- `user/memtest.c` — Test program
- `Makefile` — Added `_memtest` to `UPROGS`

---

### 4. `setpriority`

**What it does:** Changes process priority. Lower number = higher priority. Scheduler picks lowest priority number first.

**How to run:**
```sh
setpriority <pid> <priority>
```

**Examples:**
```sh
setpriority 2 1    # High priority
setpriority 2 10   # Medium priority (default)
setpriority 2 20   # Low priority
```

**Test programs:**
```sh
testpriority 2 5       # Test with verbose output
prioritytest           # Demo with multiple processes
```

**Files changed:**
- `kernel/syscall.h` — Added `SYS_setpriority` (25)
- `kernel/syscall.c` — Registered `sys_setpriority` in array
- `kernel/sysproc.c` — Implemented `sys_setpriority()`
- `kernel/proc.c` — Modified scheduler for priority-based scheduling, initialize priority in `allocproc()`, priority inheritance in `fork()`
- `kernel/proc.h` — Added `priority` field to process structure
- `user/user.h` — Added `setpriority()` declaration
- `user/usys.pl` — Added `setpriority` entry
- `user/setpriority.c` — User program
- `user/testpriority.c` — Test program
- `user/prioritytest.c` — Demo program
- `Makefile` — Added `_setpriority`, `_testpriority`, `_prioritytest` to `UPROGS`

---

### 5. `getprocstatetest`

**What it does:** Reports the number of processes in each state including RUNNING, RUNNABLE, and SLEEPING. Confirms correct real-time tracking of process state transitions during execution.

**How to run:**
```sh
getprocstatetest
```

**Output:**
```
Process State Statistics:
RUNNING:   1
RUNNABLE:  0
SLEEPING:  3
```

**Files changed:**
- `kernel/syscall.h` — Added `SYS_getprocstate` (26)
- `kernel/syscall.c` — Registered `sys_getprocstate` in array
- `kernel/sysproc.c` — Implemented `sys_getprocstate()`
- `kernel/proc.c` — Added process state counting logic
- `kernel/proc.h` — Added process state structure definition
- `user/user.h` — Added `getprocstate()` declaration
- `user/usys.pl` — Added `getprocstate` entry
- `user/getprocstatetest.c` — Test program
- `Makefile` — Added `_getprocstatetest` to `UPROGS`

---

## 🔧 Build & Run

```bash
make clean
make qemu
```

Or with explicit toolchain:

```bash
make clean
make TOOLPREFIX=riscv64-linux-gnu-
make qemu TOOLPREFIX=riscv64-linux-gnu-
```

---

## ✅ Status

| Component          | Status |
| ------------------ | ------ |
| Syscall wiring     | ✅     |
| Kernel logic       | ✅     |
| User wrappers      | ✅     |
| Output tested      | ✅     |
| Clean build        | ✅     |

---

## ⚠ Notes

- Do **not** modify syscall numbers unless strictly required
- Always run `make clean` after pulling updates
- Missing registration in `syscall.c` or `usys.pl` may cause xv6 to freeze at boot

---
```

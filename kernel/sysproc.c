#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "memstat.h"

extern struct proc proc[NPROC];

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;
  struct proc *p = myproc();

  // argint is void in this repo; just call it.
  argint(0, &n);

  addr = p->sz;

  if(growproc(n) < 0)
    return -1;

  // Update heap size statistics.
  if(n > 0) {
    p->heap_size += (uint64)n;
  } else if(n < 0) {
    uint64 dec = (uint64)(-n);
    if(p->heap_size >= dec)
      p->heap_size -= dec;
    else
      p->heap_size = 0;
  }

  return addr;
}


uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

extern uint64 total_context_switches;

uint64
sys_schedstat(void)
{
  return total_context_switches;
}
uint64
sys_psinfo(void)
{
  struct proc *p;

  printf("PID\tSTATE\tNAME\n");

  // proc[] is the global process table array
  for(p = proc; p < &proc[NPROC]; p++){
    acquire(&p->lock);

    if(p->state != UNUSED){
      char *state;

      switch(p->state){
      case UNUSED:
        state = "UNUSED";
        break;
      case SLEEPING:
        state = "SLEEP";
        break;
      case RUNNABLE:
        state = "RUNN";
        break;
      case RUNNING:
        state = "RUN";
        break;
      case ZOMBIE:
        state = "ZOMB";
        break;
      default:
        state = "???";
        break;
      }

      printf("%d\t%s\t%s\n", p->pid, state, p->name);
    }

    release(&p->lock);
  }

  return 0;
}

uint64
sys_getmeminfo(void)
{
  int pid;
  uint64 uaddr;                 // user-space pointer to struct memstat
  struct proc *cur = myproc();
  struct memstat m;
  struct proc *p;

  // argint/argaddr are void; just call them.
  argint(0, &pid);
  argaddr(1, &uaddr);

  // Find target process (similar to kill()).
  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->pid == pid && p->state != UNUSED) {
      // Fill memstat from this process
      m.code_size   = p->code_size;
      m.heap_size   = p->heap_size;
      m.stack_size  = p->stack_size;
      m.total_pages = p->sz / PGSIZE;
      m.pagefaults  = p->pagefaults;
      release(&p->lock);
      goto found;
    }
    release(&p->lock);
  }

  // No such process
  return -1;

found:
  // Copy struct memstat to user space of the *current* process
  if(copyout(cur->pagetable, uaddr, (char *)&m, sizeof(m)) < 0)
    return -1;

  return 0;
}

uint64
sys_setpriority(void)
{
  int pid, new_priority;
  struct proc *p;
  argint(0,&pid);
  argint(1,&new_priority);
  // Validate priority (should be non-negative)
  if(new_priority<0)
    return -1;
  // Find the process with the given pid
  for(p=proc;p<&proc[NPROC];p++) {
    acquire(&p->lock);
    if(p->pid==pid && p->state!=UNUSED) {
      p->priority=new_priority;
      release(&p->lock);
      return 0;
    }
    release(&p->lock);
  }
  // Process not found
  return -1;
}



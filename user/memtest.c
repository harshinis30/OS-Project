#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/memstat.h"
#include "user/user.h"
#define PGSIZE 4096


void print_memstat(char *label, int pid, struct memstat *m) {
  printf("----- %s (pid=%d) -----\n", label, pid);
  printf("  code_size   = %d bytes\n", (int)m->code_size);
  printf("  heap_size   = %d bytes\n", (int)m->heap_size);
  printf("  stack_size  = %d bytes\n", (int)m->stack_size);
  printf("  total_pages = %d\n", (int)m->total_pages);
  printf("  pagefaults  = %d\n", (int)m->pagefaults);

  // Compute expected pages from code + heap + stack
  uint64 used_bytes = m->code_size + m->heap_size + m->stack_size;
  uint64 used_pages = (used_bytes + PGSIZE - 1) / PGSIZE;  // round up

  if(m->total_pages == used_pages + 1) {
    printf(" \nnote: total_pages is 1 page larger than (code+heap+stack).\n");
    printf("      This extra page is the guard page between heap and stack.\n");
  } else if(m->total_pages != used_pages) {
    printf(" \nnote: total_pages != pages(code+heap+stack). ");
    printf("There may be extra pages (e.g., guard or alignment).\n");
  }

  printf("\n");
}


int
main(int argc, char *argv[])
{
  int pid = getpid();
  struct memstat m;

  // 1. Basic meminfo for current process
  if(getmeminfo(pid, &m) < 0) {
    printf("getmeminfo failed for self\n");
    exit(1);
  }
  print_memstat("self (initial)", pid, &m);

  // 2. Grow heap and check heap_size changes
  int grow = 3 * 4096; // 3 pages
  sbrk(grow);

  if(getmeminfo(pid, &m) < 0) {
    printf("getmeminfo failed for self after sbrk\n");
    exit(1);
  }
  print_memstat("self (after heap allocation (3 pages))", pid, &m);

  // 3. Create a child that grows heap more
  int child = fork();
  if(child < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if(child == 0) {
    // Child process
    int child_pid = getpid();
    sbrk(2 * 4096);  // child-specific heap grow

    struct memstat cm;
    if(getmeminfo(child_pid, &cm) < 0) {
      printf("child: getmeminfo failed\n");
      exit(1);
    }
    print_memstat("child (after heap allocation (2 pages))", child_pid, &cm);

    // sleep so parent can also query us
    sleep(50); // around half a second in xv6
    exit(0);
  } else {
    // Parent process: query child's meminfo while it is alive
    struct memstat child_m;

    sleep(20);  // let child run sbrk first

    if(getmeminfo(child, &child_m) < 0) {
      printf("parent: getmeminfo failed for child\n");
    } else {
      print_memstat("child (from parent view)", child, &child_m);
    }

    wait(0);  // clean up child
  }

  printf("memtest finished.\n");
  exit(0);
}


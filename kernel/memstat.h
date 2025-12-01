// kernel/memstat.h
#ifndef MEMSTAT_H
#define MEMSTAT_H

#include "types.h"

struct memstat {
  uint64 code_size;     // bytes used by code+data+bss (approx)
  uint64 heap_size;     // bytes added via sbrk()
  uint64 stack_size;     // bytes reserved for user stack
  uint64 total_pages;    // total pages allocated (sz / PGSIZE)
  uint64 pagefaults;     // number of page faults seen by this process
};

#endif


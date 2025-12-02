#ifndef UPROCSTATE_H
#define UPROCSTATE_H

#include "kernel/types.h"

struct procstate_info {
  int pid;
  uint64 running_ticks;
  uint64 runnable_ticks;
  uint64 sleeping_ticks;
};

#endif

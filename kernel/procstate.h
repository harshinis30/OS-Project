#ifndef PROCSTATE_H
#define PROCSTATE_H

#include "types.h"

struct procstate_info {
  int pid;
  uint64 running_ticks;
  uint64 runnable_ticks;
  uint64 sleeping_ticks;
};

#endif

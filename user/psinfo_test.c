#include "kernel/types.h"
#include "kernel/stat.h"
#include "../user.h"

int
main(int argc, char *argv[])
{
  struct psinfo info[64];
  int n = psinfo(info, 64);

  if (n < 0) {
    printf("psinfo: syscall failed\n");
    exit(1);
  }

  printf("PID\tSTATE\tSIZE\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%ld\n", info[i].pid, info[i].state, info[i].sz);
  }

  exit(0);
}
#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  uint64 count = schedstat();
  printf("Context switches since boot: %lud\n", count);
  exit(0);
}

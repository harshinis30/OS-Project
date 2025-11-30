#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int csw = schedstat();
  printf("Total context switches since boot: %d\n", csw);
  exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  psinfo();   // invoke our syscall
  exit(0);
}

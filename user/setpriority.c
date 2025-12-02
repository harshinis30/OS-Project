#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid, new_priority;
  int ret;

  if(argc < 3){
    printf("Usage: setpriority <pid> <new_priority>\n");
    printf("Example: setpriority 2 5\n");
    exit(1);
  }

  pid = atoi(argv[1]);
  new_priority = atoi(argv[2]);

  ret = setpriority(pid, new_priority);
  
  if(ret == 0){
    exit(0);
  } else {
    printf("setpriority: failed to set priority\n");
    exit(1);
  }
}


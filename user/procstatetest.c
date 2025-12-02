#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "procstate.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf("Usage: procstatetest pid\n");
    exit(1);
  }

  int pid = atoi(argv[1]);
  struct procstate_info info;

  if(getprocstate(pid, &info) < 0){
    printf("getprocstate failed for pid %d\n", pid);
    exit(1);
  }

  printf("Process %d runtime stats (in ticks):\n", info.pid);
  printf("  RUNNING : %d\n", (int)info.running_ticks);
  printf("  RUNNABLE: %d\n", (int)info.runnable_ticks);
  printf("  SLEEPING: %d\n", (int)info.sleeping_ticks);

  exit(0);
}

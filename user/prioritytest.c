#include "kernel/types.h"
#include "user/user.h"

//Test program to demonstrate priority scheduling
//Creates multiple child processes with different priorities
int main(void)
{
    int pid1, pid2, pid3;
    int ret;

    printf("=== Priority Scheduling Test ===\n\n");

    //Get current process PID
    int mypid = getpid();
    printf("Parent PID: %d\n", mypid);

    //Set parent priority to 10 (default)
    printf("Setting parent priority to 10...\n");
    ret = setpriority(mypid, 10);
    if (ret != 0)
    {
        printf("Error setting parent priority\n");
        exit(1);
    }

    //Fork first child
    pid1 = fork();
    if (pid1 == 0)
    {
        //Child 1: Set to high priority (low number = 1)
        int childpid = getpid();
        printf("Child 1 PID: %d - Setting priority to 1 (HIGH)\n", childpid);
        setpriority(childpid, 1);
        printf("Child 1: Running with priority 1\n");
        sleep(5);
        exit(0);
    }

    //Fork second child
    pid2 = fork();
    if (pid2 == 0)
    {
        //Child 2: Set to medium priority (5)
        int childpid = getpid();
        printf("Child 2 PID: %d - Setting priority to 5 (MEDIUM)\n", childpid);
        setpriority(childpid, 5);
        printf("Child 2: Running with priority 5\n");
        sleep(5);
        exit(0);
    }

    //Fork third child
    pid3 = fork();
    if (pid3 == 0)
    {
        //Child 3: Set to low priority (high number = 20)
        int childpid = getpid();
        printf("Child 3 PID: %d - Setting priority to 20 (LOW)\n", childpid);
        setpriority(childpid, 20);
        printf("Child 3: Running with priority 20\n");
        sleep(5);
        exit(0);
    }

    //Parent waits for all children
    printf("\nParent waiting for children...\n");
    wait(0);
    wait(0);
    wait(0);

    printf("\nAll children completed!\n");
    printf("Note: Child 1 (priority 1) should have been scheduled more frequently\n");
    printf("      than Child 3 (priority 20) due to priority scheduling.\n");

    exit(0);
}

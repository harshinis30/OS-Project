#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pid, priority;
    int ret;

    if (argc < 3)
    {
        printf("Usage: testpriority <pid> <new_priority>\n");
        printf("Example: testpriority 2 5\n");
        exit(1);
    }

    pid = atoi(argv[1]);
    priority = atoi(argv[2]);

    printf("Setting priority of process %d to %d...\n", pid, priority);

    ret = setpriority(pid, priority);

    if (ret == 0)
    {
        printf("Successfully set priority!\n");
    }
    else
    {
        printf("Error: Failed to set priority (process not found or invalid priority)\n");
        exit(1);
    }

    exit(0);
}

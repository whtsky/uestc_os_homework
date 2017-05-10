#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int child;
    char *args[] = {"/bin/hello", "Hello", "World!", NULL};

    if (!(child = fork())) {
        printf("pid %d: %d is my father\n", getpid(), getppid());
        execve("/bin/echo", args, NULL);
        printf("pid %d: I'm back, something is wrong!\n", getpid());
    } else {
        int myself = getpid();
        printf("pid %d: %d is my son\n", myself, child);
        wait4(child, NULL, 0, NULL);
        printf("pid %d: done\n", myself);
    }
    return 0;
}

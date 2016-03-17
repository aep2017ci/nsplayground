#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

#define STACK_SIZE (1024 * 1024)

static int childFunc() {
  printf("childFunc(): PID  = %ld\n", (long) getpid());
  printf("childFunc(): PPID = %ld\n", (long) getppid());
  while(true){}
}

int main(int argc, char *argv[]) {
    printf("main(): PID  = %ld\n", (long) getpid());
    printf("main(): PPID  = %ld\n", (long) getppid());

    char *stack = malloc(STACK_SIZE);
    char *stackTop = stack + STACK_SIZE;  /* Linux memory addresss grow downwards */

    pid_t child_pid = clone(childFunc,
                            stackTop,         /* Stack space for child process */
                            CLONE_NEWPID | SIGCHLD, NULL); /*Allows pid namespaceing & for child to signal death to parent*/
    waitpid(child_pid, NULL, 0);
}

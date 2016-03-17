#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

static int childFunc(void *arg) {
  struct utsname uts;
  sethostname(arg, strlen(arg)); /* Change hostname in UTS namespace of child */
  uname(&uts); /* Retrieve hostname - uses an output parameter */
  printf("uts.nodename in child:  %s\n", uts.nodename);
  return 0;
}

int main(int argc, char *argv[]) {
  struct utsname p_uts;

  char *stack = malloc(STACK_SIZE); /* Start of stack */
  char *stackTop = stack + STACK_SIZE; /* End of stack */

  pid_t child_pid = clone(childFunc,
                          stackTop,
                          CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, "monkey.host");

   sleep(1);           /* Give child time to change its hostname */

   /* Display hostname in parent's UTS namespace. This will be
       different from hostname in child's UTS namespace. */

  uname(&p_uts);
  printf("uts.nodename in parent: %s\n", p_uts.nodename);
  waitpid(child_pid, NULL, 0);
}

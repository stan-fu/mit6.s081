#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int pipes1[2], pipes2[2];
  char buf[] = {'a'};
  pipe(pipes1);
  pipe(pipes2);

  int pid = fork();

  // parent write pipes1[1] - read pipes2[0]
  // child read pipes1[0] - write pepes2[1] 
  if (pid == 0) { // child
    pid = getpid();
    close(pipes1[1]);
    close(pipes2[0]);
    read(pipes1[0], buf, 1);
    printf("%d: received ping\n", pid);
    write(pipes2[1], buf, 1);
    exit(0);
  } else {  // parent
    pid = getpid();
    close(pipes1[0]);
    close(pipes2[1]);
    write(pipes1[1], buf, 1);
    read(pipes2[0], buf, 1);
    printf("%d: received pong\n", pid);
    exit(0);
  }
}
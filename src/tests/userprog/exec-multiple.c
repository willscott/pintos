/* Executes and waits for multiple child processes. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  int i;
  int pids[4];
  int pid;
  for (i=0; i<4; i++) {
      pid = fork();
      if (pid == 0) {
          exec("child-simple");
      }
      else {
          pids[i] = pid;
      }

  }
  for (i=0; i<4; i++) {
      wait(pids[i]);
  }
}

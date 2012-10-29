/* Executes and waits for a single child process. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  int pid = fork();
  if (pid == 0) {
      exec ("child-simple");
  }
  else {
      wait(pid);
  }
}

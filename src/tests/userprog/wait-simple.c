/* Wait for a subprocess to finish. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t pid = fork();
  if (pid == 0) {
    exec("child-simple");
  }
  else {
    msg ("wait(exec()) = %d", wait (pid));
  }
}


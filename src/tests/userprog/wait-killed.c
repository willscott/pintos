/* Wait for a process that will be killed for bad behavior. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t pid = fork();
  if (pid == 0) {
    exec("child-bad");
  }
  msg ("wait(exec()) = %d", wait (pid));
}

/* Wait for a subprocess to finish, twice.
   The first call must wait in the usual way and return the exit code.
   The second wait call must return -1 immediately. */

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
    msg ("wait(exec()) = %d", wait (pid));
  }
}

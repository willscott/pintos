/* Tests argument passing to child processes. */

#include <syscall.h>
#include "tests/main.h"

void
test_main (void) 
{
  exec ("child-args childarg");
}

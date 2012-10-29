/* -*- c -*- */

// Rewrite this
// Uses seek

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  const char *child_cmd = "child-rox " CHILD_CNT;
  int handle;
  pid_t pid;
  char buffer[16];

  /* Open child-rox, read from it, write back same data. */
  CHECK ((handle = open ("child-rox")) > 1, "open \"child-rox\"");
  CHECK (read (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "read \"child-rox\"");
  close(handle);
  CHECK ((handle = open ("child-rox")) > 1, "open \"child-rox\"");
  CHECK (write (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "write \"child-rox\"");
  close(handle);

  /* Execute child-rox and wait for it. */
  pid = fork();
  if (pid == 0) {
    exec(child_cmd);
  }
    
  CHECK (pid != -1, "exec \"%s\"", child_cmd);
  quiet = true;
  CHECK (wait (pid) == 12, "wait for child");
  quiet = false;

  /* Write to child-rox again. */
  CHECK ((handle = open ("child-rox")) > 1, "open \"child-rox\"");
  CHECK (write (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "write \"child-rox\"");
}

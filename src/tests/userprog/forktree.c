/* -*- c -*- */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"
#include <stdio.h>

const char *test_name = "forktree";

void 
main (void)
{
    int depth = 3;
    int total = 0;

    while (depth > 0) {
        total += depth;
        if (fork() == -1) {
            fail("fail %d", depth);
        }
        depth--;
    }
    msg("%d\n", total);
    
}


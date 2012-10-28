# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(forktree) begin
(forktree) 6
(forktree) 6
(forktree) 6
(forktree) 6
(forktree) 6
(forktree) 6
(forktree) 6
(forktree) 6
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
forktree: exit(0)
(forktree) end
EOF
pass;

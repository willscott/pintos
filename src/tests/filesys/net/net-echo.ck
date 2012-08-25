# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(net-echo) begin
(net-echo) end
EOF
pass;

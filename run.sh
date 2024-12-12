#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --child-silent-after-fork=yes --suppressions=readline.supp --show-reachable=yes --show-leak-kinds=all ./minishell
:' --track-fds=yes --trace-children=yes

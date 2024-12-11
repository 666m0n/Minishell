#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible --child-silent-after-fork=yes --trace-children=yes --track-fds=yes --suppressions=readline.supp ./minishell
#--trace-children=yes --show-reachable=yes --show-leak-kinds=all --track-fds=yes

#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full  --child-silent-after-fork=yes --suppressions=readline.supp ./minishell
#--trace-children=yes --show-reachable=yes --show-leak-kinds=all --track-fds=yes
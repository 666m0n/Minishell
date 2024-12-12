#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --child-silent-after-fork=yes --trace-children=yes --track-fds=yes --suppressions=readline.supp --trace-children=yes --show-reachable=yes --show-leak-kinds=all --track-fds=yes ./minishell

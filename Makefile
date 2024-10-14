# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 15:04:34 by sviallon          #+#    #+#              #
#    Updated: 2024/10/14 15:13:55 by sviallon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= include/
LIBFT	= libft
SRC_DIR	= src/
OBJ_DIR	= obj/
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g3
RM	= rm -rf
AR	= ar rcs
LIBCOMP = -L./$(LIBFT) -l:libft.a
DEP = $(addprefix $(OBJ_DIR), $(OBJ .o=.d))

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Sources
LEXER_DIR	= lexer/
LXR			= lexer_helper lexer_init lexer

UTILS_DIR	= utils/
UTLS		= env utils

MAIN_DIR	= main/
MAIN		= main

SRC	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF	= .cache_exists

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBCOMP)-o $(NAME)
		@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJSF)
		@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) -MMD -MP -I $(INCLUDE) -c $< -o $@

$(OBJSF) :
		@mkdir -p $(OBJ_DIR)

clean:
		@$(RM) $(OBJ_DIR)
		@$(RM) $(OBJSF)
		@make clean -C $(LIBFT)
		@echo "$(BLUE)Minishell object files cleaned!$(DEF_COLOR)"

fclean: clean
		@$(RM) -f $(NAME)
		@$(RM) -f $(LIBFT)/libft.a
		@echo "$(CYAN)Minishell executable files cleaned!$(DEF_COLOR)"
		@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re: fclean all
		@echo "$(GREEN)Cleaned and rebuilt everything for Minishell !$(DEF_COLOR)"

-include $(DEP)

.PHONY: clean fclean re all bonus
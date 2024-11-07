# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 15:04:34 by sviallon          #+#    #+#              #
#    Updated: 2024/11/07 17:56:16 by sviallon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE	= include/
LIBFT	= libft
SRC_DIR	= src/
OBJ_DIR	= obj/
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g3
LDFLAGS += -lreadline
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
C1 = \033[38;5;198m # Rose vif
C2 = \033[38;5;199m # Rose fuchsia
C3 = \033[38;5;201m # Magenta vif
C5 = \033[38;5;165m # Magenta violet
C6 = \033[38;5;129m # Violet
C7 = \033[38;5;93m  # Violet bleu
C8 = \033[38;5;63m  # Bleu violet
C9 = \033[38;5;69m  # Bleu clair
C10 = \033[38;5;75m # Bleu brillant

# Sources
LEXER_DIR	= lexer/
LXR			= lexer_helper lexer2 lexer expand expand_utils

UTILS_DIR	= utils/
UTLS		= utils

PARSER_DIR	= parser/
PRS			= cmd parser redir syntax

BUILTINS	= builtins/
BLTN		= env builtins

MAIN_DIR	= main/
MAIN		= main test

SRC_FILES+=$(addprefix $(PARSER_DIR),$(PRS))
SRC_FILES+=$(addprefix $(BUILTINS),$(BLTN))
SRC_FILES+=$(addprefix $(LEXER_DIR),$(LXR))
SRC_FILES+=$(addprefix $(UTILS_DIR),$(UTLS))
SRC_FILES+=$(addprefix $(MAIN_DIR),$(MAIN))

SRC	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF	= .cache_exists

define MINISHELL_LOGO
$(C1)███╗   ███╗$(C2)██╗$(C3)███╗   ██╗$(C5)██╗$(C6)███████╗$(C7)██╗  ██╗$(C8)███████╗$(C9)██╗     $(C10)██╗
$(C1)████╗ ████║$(C2)██║$(C3)████╗  ██║$(C5)██║$(C6)██╔════╝$(C7)██║  ██║$(C8)██╔════╝$(C9)██║     $(C10)██║
$(C1)██╔████╔██║$(C2)██║$(C3)██╔██╗ ██║$(C5)██║$(C6)███████╗$(C7)███████║$(C8)█████╗  $(C9)██║     $(C10)██║
$(C1)██║╚██╔╝██║$(C2)██║$(C3)██║╚██╗██║$(C5)██║$(C6)╚════██║$(C7)██╔══██║$(C8)██╔══╝  $(C9)██║     $(C10)██║
$(C1)██║ ╚═╝ ██║$(C2)██║$(C3)██║ ╚████║$(C5)██║$(C6)███████║$(C7)██║  ██║$(C8)███████╗$(C9)███████╗$(C10)███████╗
$(C1)╚═╝     ╚═╝$(C2)╚═╝$(C3)╚═╝  ╚═══╝$(C5)╚═╝$(C6)╚══════╝$(C7)╚═╝  ╚═╝$(C8)╚══════╝$(C9)╚══════╝$(C10)╚══════╝$(DEF_COLOR)
endef
export MINISHELL_LOGO

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBCOMP) $(LDFLAGS) -o $(NAME)
		@echo -e "$$MINISHELL_LOGO"
		@echo -e "$(GREEN)Minishell compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJSF)
		@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) -MMD -MP -I $(INCLUDE) -c $< -o $@

$(OBJSF) :
		@mkdir -p $(OBJ_DIR)$(LEXER_DIR) $(OBJ_DIR)$(UTILS_DIR) $(OBJ_DIR)$(MAIN_DIR) \
				$(OBJ_DIR)$(PARSER_DIR) $(OBJ_DIR)$(BUILTINS)
		@touch $(OBJSF)
clean:
		@$(RM) $(OBJ_DIR)
		@$(RM) $(OBJSF)
		@make clean -C $(LIBFT)
		@echo -e "$(BLUE)Minishell object files cleaned!$(DEF_COLOR)"

fclean: clean
		@$(RM) -f $(NAME)
		@$(RM) -f $(LIBFT)/libft.a
		@echo -e "$(CYAN)Minishell executable files cleaned!$(DEF_COLOR)"
		@echo -e "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re: fclean all
		@echo -e "$(GREEN)Cleaned and rebuilt everything for Minishell !$(DEF_COLOR)"

-include $(DEP)

.PHONY: clean fclean re all bonus
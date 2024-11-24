# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 15:04:34 by sviallon          #+#    #+#              #
#    Updated: 2024/11/24 12:26:23 by emmanuel         ###   ########.fr        #
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
MAKEFLAGS += --no-print-directory
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
NEON_GREEN = \033[38;2;0;255;34m
BG =	     \033[30m\033[48;2;255;255;255m

DARK = \033[38;2;65;65;65m
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
LXR			= lexer_handler lexer lexer_utils lexer_utils_2

UTILS_DIR	= utils/
UTLS		= utils utils2 utils3

PARSER_DIR	= parser/
PRS			= cmd parser_utils parser redir  syntax var var2

BUILTINS	= builtins/
BLTN		= env builtinstest builtin_unset builtin_pwd builtin_export builtin_export_utils \
			builtin_exit builtin_env builtin_echo builtin_cd

CORE_DIR	= core/
CORE		= cleanup error execute external find get has is pipe_executor pipe redirections \
			redirections_2 set heredoc heredoc_handler

MAIN_DIR	= main/
MAIN		= main test

SRC_FILES+=$(addprefix $(CORE_DIR),$(CORE))
SRC_FILES+=$(addprefix $(PARSER_DIR),$(PRS))
SRC_FILES+=$(addprefix $(BUILTINS),$(BLTN))
SRC_FILES+=$(addprefix $(LEXER_DIR),$(LXR))
SRC_FILES+=$(addprefix $(UTILS_DIR),$(UTLS))
SRC_FILES+=$(addprefix $(MAIN_DIR),$(MAIN))

SRC	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF	= .cache_exists
define full_line_background
    @printf '\033[41m\033[30m%-*s\033[0m\n' "$$(tput cols)" " ";
endef
export full_line_background

define MINISHELL_LOGO
$(BG)                                                                                
$(BG)                                ██████  ██        ████████  ██        ██        
$(BG)                              ██        ██████    ██    ██  ██        ██        
$(BG)              ██          ██  ████████  ██    ██  ████████  ██        ██        
$(BG)    ██  ██          ██              ██  ██    ██  ██        ██        ██        
$(BG)  ██  ██  ██  ██  ██  ██  ██  ████████  ██    ██    ██████    ██████    ██████  
$(BG)                                                                                $(DEF_COLOR)
endef
export MINISHELL_LOGO

all:
	@clear
	@printf '\e[8;30;80t'
	@$(MAKE) base

base: $(NAME)

$(NAME): $(OBJ)

	@make -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) $(LIBCOMP) $(LDFLAGS) -o $(NAME)
#	@echo "$(DARK)Minishell compiled ✓$(DEF_COLOR)"
	@clear
	@$(call full_line_background)  # Ligne rouge vif
	@echo "$$MINISHELL_LOGO"
	@$(call full_line_background)  # Ligne rouge vif
	@printf '\033[37m'
	@printf "\033[?25h"  # Réaffiche le curseur


$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJSF)
	@printf "\033[?25l"  # Cache le curseur
	@printf "\033[K$(NEON_GREEN)Compiling ➤ $<\r$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -MMD -MP -I $(INCLUDE) -c $< -o $@

$(OBJSF):
	@mkdir -p $(OBJ_DIR)$(LEXER_DIR) $(OBJ_DIR)$(UTILS_DIR) $(OBJ_DIR)$(MAIN_DIR) \
	$(OBJ_DIR)$(PARSER_DIR) $(OBJ_DIR)$(BUILTINS) $(OBJ_DIR)$(CORE_DIR)
	@touch $(OBJSF)

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJSF)
	@make clean -C $(LIBFT)
	@echo "$(BLUE)Minishell object files cleaned!$(DEF_COLOR)"
	@printf "\033[?25h"  # Réaffiche le curseur

fclean: clean
	@$(RM) -f $(NAME)
	@$(RM) -f $(LIBFT)/libft.a
	@echo "$(CYAN)Minishell executable files cleaned!$(DEF_COLOR)"
	@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"
	@printf "\033[?25h"  # Réaffiche le curseur

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for Minishell !$(DEF_COLOR)"
	@printf "\033[?25h"  # Réaffiche le curseur

-include $(DEP)
.PHONY: clean fclean re all base bonus
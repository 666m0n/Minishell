# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emmmarti <emmmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/12/12 19:08:34 by emmmarti         ###   ########.fr        #
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
RED = \033[31m\033[48;2;0;0;0m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
NEON_GREEN = \033[38;2;0;255;34m
BG =	     \033[30m\033[48;2;255;255;255m
BLYE = \033[30m\033[48;2;255;255;0m
TEST = \033[38;2;153;255;204m

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

NC = \033[0m
SEPARATOR = \033[38;2;153;255;204m----------------------------------------$(NC)



# Sources
LEXER_DIR	= lexer/
LXR			= lexer_handler lexer lexer_utils lexer_utils_2 syntax syntax_utils \
			syntax_2

UTILS_DIR	= utils/
UTLS		= utils utils2 utils3

PARSER_DIR	= parser/
PRS			= cmd parser_utils parser redir var var2

BUILTINS	= builtins/
BLTN		= env builtinstest builtin_unset builtin_pwd builtin_export builtin_export_utils \
			builtin_export_utils_2 builtin_exit builtin_exit_utils builtin_env builtin_echo builtin_cd

CORE_DIR	= core/
CORE		= cleanup error execute external find get has is pipe_executor pipe redirections \
			redirections_2 redirections_3 set heredoc heredoc_handler error_2 execute_2 \
			pipe_2

MAIN_DIR	= main/
MAIN		= main signal signal_utils


# Fichier contenant les tests
TEST_FILE = tests/commands.txt

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
	@printf '\033[41m\033[30m%-80s\033[0m\n' " ";
endef
export full_line_background

define SHELL_LOGO
$(RED)
$(RED)                                  ██████████████
$(RED)                            ██████████████████████████
$(RED)                        ██████████████████████████████████
$(RED)                      ██████████$(BLYE)        $(RED)██$(BLYE)        $(RED)██████████
$(RED)                    ████████$(BLYE)  $(RED)██$(BLYE)        $(RED)██$(BLYE)        $(RED)██$(BLYE)  $(RED)████████
$(RED)                  ████████$(BLYE)    $(RED)████$(BLYE)      $(RED)██$(BLYE)      $(RED)████$(BLYE)    $(RED)████████
$(RED)                ████████$(BLYE)      $(RED)████$(BLYE)      $(RED)██$(BLYE)      $(RED)████$(BLYE)      $(RED)████████
$(RED)              ██████████$(BLYE)        $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)        $(RED)██████████
$(RED)              ████████████$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)████████████
$(RED)            ████████$(BLYE)    $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)    $(RED)████████
$(RED)            ██████$(BLYE)        $(RED)██$(BLYE)    $(RED)████$(BLYE)    $(RED)██$(BLYE)    $(RED)████$(BLYE)    $(RED)██$(BLYE)        $(RED)██████
$(RED)            ████████$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)████████
$(RED)            ██████████$(BLYE)      $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)      $(RED)██████████
$(RED)            ████$(BLYE)    $(RED)████$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)████$(BLYE)    $(RED)████
$(RED)            ████$(BLYE)      $(RED)██$(BLYE)      $(RED)██$(BLYE)  $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)  $(RED)██$(BLYE)      $(RED)██$(BLYE)      $(RED)████
$(RED)            ████$(BLYE)        $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)    $(RED)██$(BLYE)    $(RED)██$(BLYE)        $(RED)████
$(RED)            ████$(BLYE)          $(RED)██$(BLYE)    $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)    $(RED)██$(BLYE)          $(RED)████
$(RED)            ██████$(BLYE)          $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)  $(RED)██$(BLYE)          $(RED)██████
$(RED)              ██████$(BLYE)          $(RED)██$(BLYE)  $(RED)██$(BLYE)          $(RED)██$(BLYE)  $(RED)██$(BLYE)          $(RED)██████
$(RED)                ████████$(BLYE)                                  $(RED)████████
$(RED)                  ████████$(BLYE)                              $(RED)████████
$(RED)                    ██████$(BLYE)                              $(RED)██████
$(RED)                    ██████$(BLYE)                              $(RED)██████
$(RED)                      ████$(BLYE)                              $(RED)████
$(RED)                      ████$(BLYE)                              $(RED)████
$(RED)                      ████████████████$(BLYE)      $(RED)████████████████
$(RED)                      ██████████████████████████████████████
$(RED)                                      ██████$(DEF_COLOR)
endef
export SHELL_LOGO




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
	@echo "$$SHELL_LOGO"
	@sleep 1
	@clear
	@$(call full_line_background)
	@echo "$$MINISHELL_LOGO"
	@$(call full_line_background)
	@echo "$(DARK)Run by sviallon & emmmarti$(DEF_COLOR)"
	@echo
	@$(MAKE) base --no-print-directory

base: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) $(LIBCOMP) $(LDFLAGS) -o $(NAME)
	@printf "\033[?25h"


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

# Règle pour comparer les sorties
compare: $(NAME)
	@clear
	@printf "\033[38;2;153;255;204mBash vs Minishell\033[0m\n\n"
	@count=0; success=0; \
	while read -r test || [ -n "$$test" ]; do \
	[ -z "$$test" ] || [ "$${test#\#}" != "$$test" ] && continue; \
	count=$$((count + 1)); \
	echo "$(SEPARATOR)"; \
	echo "$$test"; \
	echo "$(SEPARATOR)"; \
	if echo "$$test" | grep -q "<<"; then \
	eval "$$test" > /tmp/bash_output.tmp 2>&1; \
	eval "$$test" | ./$(NAME) > /tmp/minishell_output.tmp 2>&1; \
	else \
	bash -c "$$test" > /tmp/bash_output.tmp 2>&1; \
	./$(NAME) -c "$$test" > /tmp/minishell_output.tmp 2>&1; \
	fi; \
	sed 's/^minishell: //' /tmp/minishell_output.tmp | sed 's/^bash: //' | sed 's/^line [0-9]*: //' > /tmp/minishell_cleaned.tmp; \
	sed 's/^minishell: //' /tmp/bash_output.tmp | sed 's/^bash: //' | sed 's/^line [0-9]*: //' > /tmp/bash_cleaned.tmp; \
	if diff -q /tmp/bash_cleaned.tmp /tmp/minishell_cleaned.tmp >/dev/null; then \
	echo "\033[30m\033[48;2;0;255;0m OK $(NC)"; \
	success=$$((success + 1)); \
	else \
	echo "\033[38;2;255;16;0m\033[48;2;57;4;0m KO $(NC)"; \
	fi; \
	rm -f /tmp/bash_output.tmp /tmp/minishell_output.tmp /tmp/bash_cleaned.tmp /tmp/minishell_cleaned.tmp; \
	echo; \
	done < $(TEST_FILE);


# Règle pour comparer une commande spécifique
compare-cmd: $(NAME)
	@read -p "🔍 Entrez la commande à tester : " cmd; \
	echo "\n$(BLUE)Test de la commande : $$cmd$(NC)"; \
	echo "$(SEPARATOR)"; \
	echo "Bash :"; \
	bash -c "$$cmd" 2>&1; \
	echo "\nMinishell :"; \
	./$(NAME) -c "$$cmd" 2>&1; \
	echo "$(SEPARATOR)"


-include $(DEP)
.PHONY: clean fclean re all base bonus
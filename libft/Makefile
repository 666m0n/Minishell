# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emmanuel <emmanuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 10:06:44 by sviallon          #+#    #+#              #
#    Updated: 2024/11/10 11:55:29 by emmanuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INCLUDES = ../include

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)

SRCS_DIR = src/
OBJS_DIR = obj/
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Flags spécifiques selon l'OS
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D LINUX
endif
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -D OSX -arch x86_64
endif

RM = rm -rf
AR = ar rcs
DEP = $(addprefix $(OBJ_DIR), $(OBJ .o=.d))

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources
FTIS_DIR = ft_is/
FTIS = ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

FTMEM_DIR = ft_mem/
FTMEM = ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset \
        ft_memcpy

FTPUT_DIR = ft_put/
FTPUT = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR = ft_to/
FTTO = ft_atoi ft_itoa ft_tolower ft_toupper

FTSTR_DIR = ft_str/
FTSTR = ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
        ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
        ft_strnstr ft_strrchr ft_strtrim ft_substr ft_strcmp

FTLST_DIR = ft_lst/
FTLST = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
        ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

GNL_DIR = gnl/
GNL = get_next_line get_next_line_utils utils

PRINTF_DIR = ft_printf/
FTPRINTF = ft_print_hexa ft_print_msc ft_print_uns ft_printf ft_printf_fd

SRC_FILES+=$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES+=$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES+=$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES+=$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES+=$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES+=$(addprefix $(FTLST_DIR),$(FTLST))
SRC_FILES+=$(addprefix $(GNL_DIR), $(GNL))
SRC_FILES+=$(addprefix $(PRINTF_DIR), $(FTPRINTF))

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF = .cache_exists

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo -e "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJSF)
	@echo -e "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -MMD -MP -I $(INCLUDES) -c $< -o $@

$(OBJSF):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)$(FTIS_DIR)
	@mkdir -p $(OBJS_DIR)$(FTMEM_DIR)
	@mkdir -p $(OBJS_DIR)$(FTPUT_DIR)
	@mkdir -p $(OBJS_DIR)$(FTTO_DIR)
	@mkdir -p $(OBJS_DIR)$(FTSTR_DIR)
	@mkdir -p $(OBJS_DIR)$(FTLST_DIR)
	@mkdir -p $(OBJS_DIR)$(GNL_DIR)
	@mkdir -p $(OBJS_DIR)$(PRINTF_DIR)

clean:
	@$(RM) -rf $(OBJS_DIR)
	@$(RM) -rf $(OBJSF)
	@echo -e "$(BLUE)libft objects files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) -f $(NAME)
	@echo -e "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re: fclean all
	@echo -e "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

-include $(DEP)

.PHONY: clean fclean re all bonus

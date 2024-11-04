NAME = test_builtins
INCLUDES = ../include

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)

# Compilateur et flags de base
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Flags spécifiques selon l'OS
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D LINUX
endif
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -D OSX -arch x86_64
endif

# Chemins
LIBFT_PATH = ../libft
LIBFT_SRC = $(LIBFT_PATH)/src/ft_printf/ft_printf.c \
            $(LIBFT_PATH)/src/ft_printf/ft_print_hexa.c \
            $(LIBFT_PATH)/src/ft_printf/ft_print_msc.c \
            $(LIBFT_PATH)/src/ft_printf/ft_print_uns.c \
            $(LIBFT_PATH)/src/ft_str/ft_strcmp.c \
			$(LIBFT_PATH)/src/ft_str/ft_strlen.c \
			$(LIBFT_PATH)/src/ft_mem/ft_memset.c

# Sources des tests
TEST_SRC = test_builtins.c test_echo.c main_test.c
SRC_PROJECT = ../src/builtins/builtin_echo.c

# Objets
OBJS_DIR = obj/
TEST_OBJS = $(addprefix $(OBJS_DIR), $(notdir $(TEST_SRC:.c=.o)))
PROJ_OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRC_PROJECT:.c=.o)))
LIBFT_OBJS = $(addprefix $(OBJS_DIR), $(notdir $(LIBFT_SRC:.c=.o)))
ALL_OBJS = $(TEST_OBJS) $(PROJ_OBJS) $(LIBFT_OBJS)

all: $(NAME)

$(NAME): $(ALL_OBJS)
	@echo "Linking test program..."
	@$(CC) $(CFLAGS) -o $(NAME) $(ALL_OBJS)

$(OBJS_DIR)%.o: ../src/builtins/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: $(LIBFT_PATH)/src/ft_printf/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: $(LIBFT_PATH)/src/ft_str/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: $(LIBFT_PATH)/src/ft_mem/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@$(RM) -rf $(OBJS_DIR)
	@echo "Test objects cleaned!"

fclean: clean
	@$(RM) -f $(NAME)
	@echo "Test executable cleaned!"

re: fclean all

.PHONY: all clean fclean re

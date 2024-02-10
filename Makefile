NAME = minishell
SRC = src/*.c
PWD= bin/pwd
PWD_SRC = src/pwd/pwd.c
ECHO= bin/echo
ECHO_SRC = src/echo/echo.c
LIBFT = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
INCLUDES = -lreadline
RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME) $(PWD) $(ECHO)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)finished compiling minishell$(ENDCOLOR)"

$(PWD):
	$(CC) $(PWD_SRC) $(FLAGS) -o $(PWD)

$(ECHO): $(LIBFT)
	$(CC) $(ECHO_SRC) $(LIBFT) $(FLAGS) -o $(ECHO)

$(LIBFT):
	cd libft && make

clean:
	rm -f $(NAME)

fclean: clean
	rm -f ./bin/*
	cd libft && make fclean
	@echo "$(GREEN)finished cleaning builtins Binaries$(ENDCOLOR)"

re: fclean all

debug: all
	@echo "$(GREEN)Starting Debugging Minishell:$(ENDCOLOR)"
	@lldb $(NAME)

leak: all
	@echo "$(GREEN)Checking Minishell leaks:$(ENDCOLOR)"
	@valgrind ./$(NAME)

exec: all
	@echo "$(GREEN)Starting Minishell:$(ENDCOLOR)"
	@./$(NAME)

.PHONY: all clean fclean re

NAME = minishell
SRC = src/*.c src/*/*.c
LIBFT = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
INCLUDES = -lreadline
RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)finished compiling minishell$(ENDCOLOR)"

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

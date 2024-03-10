NAME = minishell

MINISHELL_SRC = src/main.c src/parser.c src/parser_list.c src/evaluation.c src/shell_setting.c src/utils.c src/validations.c src/env/env.c src/prompt_split.c src/arg_expansion.c
MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)

BINS = $(PWD) $(ECHO)

PWD= bin/pwd
PWD_SRC = src/pwd/pwd.c
PWD_OBJ = $(PWD_SRC:.c=.o)

ECHO= bin/echo
ECHO_SRC = src/echo/echo.c
ECHO_OBJ = $(ECHO_SRC:.c=.o)

LIBFT = libft/libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
INCLUDES = -lreadline

RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME) $(BINS)

$(NAME): $(LIBFT) $(MINISHELL_OBJ) $(PWD_OBJ) $(ECHO_OBJ)
	$(CC) $(FLAGS) $(MINISHELL_OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)finished compiling minishell$(ENDCOLOR)"

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(PWD):
	$(CC) $(FLAGS) $(PWD_OBJ) -o $(PWD)
	@echo "$(GREEN)finished compiling pwd$(ENDCOLOR)"

$(ECHO):
	$(CC) $(FLAGS) $(ECHO_OBJ) $(LIBFT) -o $(ECHO)
	@echo "$(GREEN)finished compiling echo$(ENDCOLOR)"

$(LIBFT):
	@make -C libft/

clean:
	rm -f $(MINISHELL_OBJ) $(ECHO_OBJ) $(PWD_OBJ)
	@echo "$(GREEN)finished cleaning binaries$(ENDCOLOR)"
	@make clean -C libft/

fclean: clean
	rm -f $(BINS) $(NAME)
	@echo "$(GREEN)finished cleaning binaries$(ENDCOLOR)"
	@make fclean -C libft/

exec: all
	./$(NAME)

leak: all
	valgrind ./$(NAME)

re: fclean all

.PHONY: clean fclean re exec leak all

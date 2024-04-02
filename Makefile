NAME = minishell

MINISHELL_SRC = src/arg_expansion.c src/builtins.c src/cd.c src/command_split.c src/command_split_utils.c src/echo.c src/env.c src/env_split.c src/env_utils.c src/error.c src/evaluation.c src/execution_path.c src/exits.c src/expansion_edge_cases.c src/export.c src/heredoc.c src/input_redirection.c src/list_validations.c src/main.c src/node_args.c src/output_redirection.c src/parser.c src/pipe.c src/process.c src/prompt_setup.c src/prompt_split.c src/pwd.c src/shell_setting.c src/split_charset.c src/split_join.c src/unset.c src/utils.c src/validations.c

MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)

LIBFT = libft/libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
INCLUDES = -lreadline

RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MINISHELL_OBJ)
	$(CC) $(FLAGS) $(MINISHELL_OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)finished compiling minishell$(ENDCOLOR)"

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

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

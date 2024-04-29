NAME = minishell

SRC = src/arg_expansion.c src/builtins.c src/cd.c src/command_split.c src/command_split_utils.c src/echo.c src/env.c src/env_split.c src/env_utils.c src/evaluation.c src/execution_path.c src/exits.c src/expansion_edge_cases.c src/export.c src/heredoc.c src/input_redirection.c src/main.c src/node_args.c src/output_redirection.c src/parser.c src/pipe.c src/process.c src/prompt_setup.c src/prompt_split.c src/pwd.c src/shell_setting.c src/split_charset.c src/split_join.c src/unset.c src/utils.c src/validations.c src/quote_split.c src/double_token_validation.c src/process_utils.c src/exit_utils.c src/evaluation_utils.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
LINKS = -lreadline

RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LINKS) -o $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: clean fclean re all

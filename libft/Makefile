# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 19:50:18 by pdrago            #+#    #+#              #
#    Updated: 2024/01/27 04:23:18 by pdrago           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = libft.a 
SRC = ft_atoi.c ft_binary_search.c ft_atoi_base.c ft_strrev.c ft_atol.c ft_strupper.c ft_strlower.c ft_strchr_idx.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c stack/stack_newstack.c stack/stack_newnode.c stack/stack_map.c stack/stack_iter.c stack/stack_clear.c stack/push.c stack/pop.c queue/dequeue.c queue/enqueue.c queue/queue_clear.c queue/queue_delnode.c queue/queue_iter.c queue/queue_map.c queue/queue_newnode.c queue/queue_newqueue.c list/list_addback.c list/list_addfront.c list/list_clear.c list/list_delnode.c list/list_iter.c list/list_map.c list/list_newlist.c list/list_newnode.c list/list_removenode.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c hashmap/creation.c hashmap/deletion.c hashmap/hashing.c hashmap/operations.c hashmap/resize.c
OBJ = $(SRC:.c=.o)
RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	@echo "$(GREEN)finished compiling libft$(ENDCOLOR)"

.c.o:
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) a.out

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

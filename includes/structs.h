/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:38 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/12 00:18:36 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <sys/types.h>

# define STD 0
# define INPUT_FILE 1
# define HEREDOC 2
# define OUTPUT_FILE_TRUNCATE 3
# define OUTPUT_FILE_APPEND 4

typedef struct s_pid_node
{
	pid_t				pid;
	struct s_pid_node	*next;
}					t_pid_node;

typedef struct s_pid_list
{
	t_pid_node			*head;
	t_pid_node			*tail;
}					t_pid_list;

typedef struct s_node
{
	char			*basic_command;
	char			**splited_command;
	char			**args;
	int				has_pipe;
	int				node_pipe[2];
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_list
{
	t_node			*head;
	t_node			*tail;
}					t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_validation
{
	int	in_single_quotes;
	int	in_double_quotes;
	int	token_last;
}	t_validation;

typedef struct s_pids
{
	pid_t	*array;
	int		size;
	int		index;
}	t_pids;

typedef struct s_shell
{
	int				last_status;
	char			*prompt_string;
	int				original_stdin;
	int				original_stdout;
	int				has_pipes;
	t_env			*env;
	t_list			*prompt_list;
	t_pids			pids;
	char			**envp;
	char			**env_array;
}					t_shell;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:48:38 by rafaelro          #+#    #+#             */
/*   Updated: 2024/03/20 17:37:04 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include <sys/types.h>

#define STD 0
#define INPUT_FILE 1
#define HEREDOC 2
#define OUTPUT_FILE_TRUNCATE 3
#define OUTPUT_FILE_APPEND 4

typedef struct s_pid_node
{
	pid_t	pid;
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
	int			has_pipe;
	int			node_pipe[2];
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

typedef struct s_process
{
	pid_t pid;
	char	*command;
} 	t_process;

typedef struct s_processes_data
{
	t_process	**processes;
	int		size;
	int		index;
} 	t_processes_data;
typedef struct s_shell
{
	int				last_status;
	char			*prompt_string;
	int			original_stdin;
	int			original_stdout;
	t_env			*env;
	t_list			*prompt_list;
	t_processes_data	processes_data;
	char			**envp;
}					t_shell;

#endif

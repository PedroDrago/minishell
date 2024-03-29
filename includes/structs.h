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
	char			*command;
	char			**args;
	char			*token;
	struct s_node	*next;
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

typedef struct s_pid_data
{
	int	size;
	int	index;
	pid_t	*p_array; //NOTE: pid_arrays
	char	**c_array; // NOTE: Command arrays

} 	t_pid_data;
typedef struct s_shell
{
	int				last_status;
	char			*prompt_string;
	int			original_stdin;
	t_env			*env;
	t_list			*prompt_list;
	t_pid_data		*pids;
}					t_shell;

#endif

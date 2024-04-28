/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:03:51 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:07:45 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <unistd.h>

int	prep_process(t_node *node, t_shell *shell)
{
	if (!node->splited_command)
		return (FALSE);
	if (node->has_pipe)
		dup2(node->node_pipe[1], 1);
	if (node->prev && node->prev->has_pipe)
		dup2(node->node_pipe[0], 0);
	return (perform_redirections(node->splited_command, shell));
}

void	post_process(pid_t pid, t_node *node, t_shell *shell)
{
	if (node->has_pipe)
		close(node->node_pipe[1]);
	if (node->prev && node->prev->has_pipe)
		close(node->node_pipe[0]);
	append_process(pid, shell);
}

int	execute_node(t_node *node, t_shell *shell)
{
	pid_t	pid;

	expand_arguments(node, shell);
	node->args = get_args(node->splited_command);
	remove_empty_args(node);
	if (node->splited_command && is_builtin(node->splited_command[0]))
	{
		execute_builtin(node, shell);
		return (TRUE);
	}
	kill(getpid(), SIGUSR2);
	pid = fork();
	if (pid == 0)
	{
		if (!prep_process(node, shell))
		{
			free_process_data(shell);
			exit_safely(shell, 2);
		}
		execute_command(shell, node->args);
	}
	else
		post_process(pid, node, shell);
	return (TRUE);
}

void	append_process(pid_t pid, t_shell *shell)
{
	shell->pids.array[shell->pids.index++] = pid;
}

void	init_processes_data(t_list *list, t_shell *shell)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = list->head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	shell->pids.array = malloc(sizeof(pid_t) * i);
	shell->pids.size = i;
	shell->pids.index = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:03:51 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/05 18:51:16 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

int	prep_process(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	int status;

	(void)shell;
	if (!node->splited_command)
		return (FALSE);
	if (!node->next)
	{
		dup2(*prevpipe, 0);
		close(*prevpipe);
		while (wait(&status) != -1)
			;
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
	}
	return (1);
}

void	post_process(pid_t pid, t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	/*if (!node->next)
	{
		close(*prevpipe);
	}
	else
	{
		close(pipefd[1]);
		close(*prevpipe);
	}*/
	close(pipefd[1]);
	close(*prevpipe);
	*prevpipe = pipefd[0];
	
	(void)node;
	append_process(pid, shell);
}

int	execute_node(t_node *node, t_shell *shell, int *prevpipe)
{
	pid_t	pid;

	int	pipefd[2];
	pipe(pipefd);
	expand_arguments(node, shell);
	node->args = get_args(node->splited_command);
	remove_empty_args(node);
	set_exit_status(0, shell);
	if (node->splited_command && is_builtin(node->splited_command[0]))
	{
		execute_builtin(node, shell, prevpipe, pipefd);
		return (TRUE);
	}
	kill(getpid(), SIGUSR2);
	perform_redirections(node->splited_command, shell, prevpipe);
	pid = fork();
	if (pid == 0)
	{
		if (!prep_process(node, shell, prevpipe, pipefd))
		{
			free_process_data(shell);
			exit_safely(shell, 2);
		}
		execute_command(shell, node->args);
	}
	else
		post_process(pid, node, shell, prevpipe, pipefd);
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

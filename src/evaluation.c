/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:05 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/21 19:09:14 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_command(t_shell *shell, char *command, char **args)
{
	char *path;

	path = get_right_path(shell, command);
	execve(path, args, NULL);
	exit(1);
}

int	perform_redirections(char **splited_command)
{
	int	i;
	int		original_fd;

	i = 0;
	original_fd = dup(0);
	while(splited_command[i])
	{
		if(is_redirect_input(splited_command[i]))
			redirect_input(splited_command[++i]);
		else if(is_redirect_output(splited_command[i]))
			redirect_output(splited_command[++i]);
		else if(is_heredoc(splited_command[i]))
			do_heredoc(splited_command[++i], original_fd);
		i++;
	}
	return (TRUE);
}

void	wait_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->processes_data.size)
	{
		status = -1;
		waitpid(shell->processes_data.processes[i]->pid, &status, 0);
		set_exit_status(status, shell);
		if (status > 0)
			resolve_error(status, shell->processes_data.processes[i]->command);
		i++;
	}
}

int	exec_list(t_list *list, t_shell *shell)
{
	t_node *tmp;

	tmp = list->head;
	while (tmp)
	{
		execute_node(tmp, list, shell);
		tmp = tmp->next;
	}
	wait_children(shell);
	return (TRUE);
}

int	evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;

	prompt_list = parse_prompt(prompt);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	if (!validate_list(prompt_list))
		return (TRUE);
	setup_list_pipes(prompt_list);
	init_processes_data(prompt_list, shell);
	exec_list(prompt_list, shell);
	free_list(prompt_list);
	return (TRUE);
}

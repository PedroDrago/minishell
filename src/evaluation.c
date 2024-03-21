/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:05 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/21 01:05:01 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_right_path(t_shell *shell, t_node *current)
{
	char	*path;
	char	**paths_split;
	t_env	*node;
	int	i;
	int	stat_return;
	char	*value;
	struct stat	file_info; 

	stat_return = -1;
	path = ft_strdup(current->command);
	node = get_env_node(shell->env, "PATH");
	i = 0;
	if (!node || !node->value)
		value = ft_strdup("");
	else
		value = node->value;
	paths_split = ft_split(value, ':');
	if (!paths_split)
		exit(1);
	while (paths_split[i])
	{
		stat_return = stat(path, &file_info);
		if (stat_return == 0)
		{
			if (!(file_info.st_mode & S_IXUSR))
				exit(126);
			return (path);
		}
		free(path);
		path = ft_strjoin(paths_split[i], "/", O_NONE);
		path = ft_strjoin(path, current->command, O_ONE);
		i++;
	}
	stat_return = stat(path, &file_info);
	if (stat_return == 0)
	{
		if (!(file_info.st_mode & S_IXUSR))
			exit(126);
		return (path);
	}
	free(path);
	exit(127);
}

int	execute_command(t_shell *shell, t_node *current)
{
	char *path;

	path = get_right_path(shell, current);
	execv(path, current->args);
	exit(1);
}

void	exec_last(t_node *current, t_shell *shell, int *yield)
{
	int	pid;

	if (is_builtin(current->command))
		exec_builtin(current, shell, 1);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(yield[0], 0);
			close(yield[0]);
			close(yield[1]);
			execute_command(shell, current);
		}
		else
			wait_for_child(yield, pid, shell, current);
	}
	return ;
}

int	evaluate_pipeline(t_node *current, t_shell *shell)
{
	int	*yield;

	yield = (int *)malloc(sizeof(int) * 2);
	if (!yield)
		return (FALSE);
	if (pipe(yield) < 0)
		return (free(yield), FALSE);
	while (current->next)
	{
		if (!current->token || is_pipe(current->token))
			yield = pipe_output(current, yield, shell);
		else if (is_redirect_output(current->token))
		{
			redirect_output(current, shell, yield);
			current = current->next;
		}
		current = current->next;
	}
	exec_last(current, shell, yield);
	close(yield[1]);
	close(yield[0]);
	free(yield);
	return (TRUE);
}

void	resolve_error(int status, t_node *current)
{
	// printf("Status Received in handler: %i\n", status);
	if (status == 32512)
	{
		ft_putstr_fd(current->command, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	else if (status == 32256)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(current->command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}

}

void	evaluate_solo(t_node *current, t_shell *shell)
{
	int	pid;
	int	status;

	if (is_builtin(current->command))
		exec_builtin(current, shell, 1);
	else
	{
		pid = fork();
		g_pid = pid;
		if (pid == 0)
			execute_command(shell, current);
		waitpid(pid, &status, 0);
		set_exit_status(status, shell);
		if (status > 0 && WTERMSIG(status) != SIGINT)
			resolve_error(status, current);
	}
}

int	evaluate_prompt(char *prompt, t_shell *shell)
{
	t_list	*prompt_list;
	t_node	*current;

	prompt_list = generate_list(prompt, shell);
	if (!prompt_list)
		return (FALSE);
	shell->prompt_list = prompt_list;
	current = prompt_list->head;
	if (!current->token)
		evaluate_solo(current, shell);
	else if (!evaluate_pipeline(current, shell))
		return (free_list(prompt_list), FALSE);
	free_list(prompt_list);
	shell->prompt_list = NULL;
	return (TRUE);
}

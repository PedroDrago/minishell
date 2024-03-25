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
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


char **get_paths_split(t_shell *shell)
{
	char	**splited;
	t_env	*node;

	node = get_env_node(shell->env, "PATH");
	if (!node || !node->value)
		return (NULL);
	splited = ft_split(node->value, ':');
	if (!splited)
		return (NULL);
	return (splited);
}

char *get_current_path_str(char *path, char *command)
{
	char	*joined;

	joined = ft_strjoin(path, "/", O_ONE);
	if (!joined)
		return(NULL);
	joined = ft_strjoin(joined, command, O_ONE);
	if (!joined)
		return(NULL);
	return (joined);
}

int	can_open_file(int stat_return, struct stat *file_info)
{
	if (stat_return < 0)
		return (0);
	if (!(file_info->st_mode & S_IXUSR))
		exit(126);
	return (1);
	
}

char	*get_right_path(t_shell *shell, t_node *current) //FIX: Leak? Child process
{
	char	*path;
	char	**paths_split;
	int	i;
	struct stat	file_info; 

	i = 0;
	paths_split = get_paths_split(shell);
	if (!paths_split)
		return (NULL);
	while(paths_split[i])
	{
		path = get_current_path_str(paths_split[i++], current->command);
		if (can_open_file(stat(path, &file_info), &file_info))
			return (path);
	}
	exit(127);
}
int	execute_command(t_shell *shell, t_node *current)
{
	char *path;

	path = get_right_path(shell, current);
	execve(path, current->args, NULL);
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
	while (current)
	{
		if (!current->token || is_pipe(current->token))
			yield = pipe_output(current, yield, shell);
		else if (is_redirect_output(current->token))
		{
			redirect_output(current, shell, yield);
			current = current->next;
		}
		else if (is_redirect_input(current->token))
		{
			if (!current->next->token)
			{
				redirect_input(current, shell, 1);
				current = NULL;
				break ;
			}
			redirect_input(current, shell, yield[1]);
			current = current->next;
		}
		else if (is_heredoc(current->token))
		{
			if (!current->next->token)
			{
				heredoc(current, shell, 1);
				current = NULL;
				break ;
			}
			heredoc(current, shell, yield[1]);
			current = current->next;
			
		}
		if (!current->next)
		{
			exec_last(current, shell, yield);
			break ;
		}
		current = current->next;
	}
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

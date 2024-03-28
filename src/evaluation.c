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
#include <sys/wait.h>
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

void	exec_last(t_node *node, t_shell *shell)
{
	int pipe_fd[2];

	g_pid = fork();
	if (g_pid == 0)
	{
		execute_command(shell, node);
		exit(1);
	}
	else
	{
		append_pid_node(shell->pid_list, create_pid_node(g_pid));
	}
	(void) pipe_fd;
}

void	pipe_output(t_node *node, t_shell *shell)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execute_command(shell, node);
	}
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		append_pid_node(shell->pid_list, create_pid_node(g_pid));
	}
}

void	exec_list(t_node *node, t_shell *shell)
{
	shell->pid_list = create_pid_list();

	while (node)
	{
		if (!node->token)
		{
			exec_last(node, shell);
		}
		else if (is_pipe(node->token))
		{
			pipe_output(node, shell);
		}
		node = node->next;
	}
	t_pid_node *current = shell->pid_list->head;
	int	status = -1;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
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
	exec_list(current, shell);

	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:33 by pdrago            #+#    #+#             */
/*   Updated: 2024/04/12 10:41:18 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>

void	perform_builtin_redirections(char **splited_com, int *status,
	int original_fd)
{
	while (*splited_com)
	{
		if (is_redirect_input(*splited_com))
		{
			*status = redirect_input_builtin(*(++splited_com));
			if (*status)
				return ;
		}
		else if (is_redirect_output(*splited_com))
		{
			*status = redirect_output_builtin(*splited_com, *(splited_com + 1));
			if (++splited_com && status)
				return ;
		}
		else if (is_heredoc(*splited_com))
		{
			*status = fork();
			if (*status == 0)
				do_heredoc_builtin(*(++splited_com), original_fd);
			waitpid(*status, status, 0);
		}
		++splited_com;
	}
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5))
		return (TRUE);
	if (!ft_strncmp(command, "cd", 3))
		return (TRUE);
	if (!ft_strncmp(command, "pwd", 4))
		return (TRUE);
	if (!ft_strncmp(command, "export", 7))
		return (TRUE);
	if (!ft_strncmp(command, "unset", 6))
		return (TRUE);
	if (!ft_strncmp(command, "env", 4))
		return (TRUE);
	if (!ft_strncmp(command, "exit", 5))
		return (TRUE);
	return (FALSE);
}

int	prep_builtin(t_node *node)
{
	int	status;
	int	original_fd;

	status = 0;
	original_fd = dup(0);
	if (node->has_pipe)
		dup2(node->node_pipe[1], 1);
	if (node->prev && node->prev->has_pipe)
		dup2(node->node_pipe[0], 0);
	perform_builtin_redirections(node->splited_command, &status, original_fd);
	return (status);
}

void	post_builtin(t_node *node, t_shell *shell)
{
	if (node->has_pipe)
		close(node->node_pipe[1]);
	if (node->prev && node->prev->has_pipe)
		close(node->node_pipe[0]);
	dup2(shell->original_stdin, 0);
	dup2(shell->original_stdout, 1);
}

void	execute_builtin(t_node *node, t_shell *shell)
{
	if (prep_builtin(node))
		return (post_builtin(node, shell));
	set_exit_status(0, shell);
	if (!ft_strncmp(node->splited_command[0], "echo", 5))
		echo(node->args);
	else if (!ft_strncmp(node->splited_command[0], "cd", 3))
		cd(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(node->splited_command[0], "export", 7))
		export(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "unset", 6))
		unset(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "env", 4))
		env(shell->env);
	else if (!ft_strncmp(node->splited_command[0], "exit", 5)
		&& (!node->prev && !node->next))
	{
		free_process_data(shell);
		builtin_exit(shell, node);
	}
	post_builtin(node, shell);
}

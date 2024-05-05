/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:33 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/05 20:14:30 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void	perform_builtin_redirections(char **splited_com, int *status,
	int original_fd, t_shell *shell)
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
				do_heredoc_builtin(*(++splited_com), original_fd, shell);
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

int	prep_builtin(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	int	status;
	int	original_fd;
	(void)pipefd;
	(void)prevpipe;
	original_fd = dup(0);
	status = 0;
	if (!node->next)
	{
	//	dup2(*prevpipe, STDIN_FILENO);
	//	close(*prevpipe);
	}
	else
	{
		//close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	//	dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
	}
	perform_builtin_redirections(node->splited_command, &status,
		original_fd, shell);
	return (status);
}

void	post_builtin(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	/*char	*file;*/
	/**/
	/*file = NULL;*/
	/*if (node->prev && node->prev->has_pipe)*/
	/*{*/
	/*	file = get_next_line(node->node_pipe[0]);*/
	/*	while (file)*/
	/*	{*/
	/*		free(file);*/
	/*		file = get_next_line(node->node_pipe[0]);*/
	/*	}*/
	/*}*/
	if (!node->next)
	{
		close(*prevpipe);
	}
	else
	{
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
	(void)prevpipe;
	(void)pipefd;
	(void) node;
	(void) shell;
}

void	execute_builtin(t_node *node, t_shell *shell, int *prevpipe, int *pipefd)
{
	int	status;

	status = prep_builtin(node, shell, prevpipe, pipefd);
	if (status)
		;
	else if (!ft_strncmp(node->splited_command[0], "echo", 5))
		status = echo(node->args);
	else if (!ft_strncmp(node->splited_command[0], "cd", 3))
		status = cd(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "pwd", 4))
		status = pwd();
	else if (!ft_strncmp(node->splited_command[0], "export", 7))
		status = export(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "unset", 6))
		status = unset(node->args, shell);
	else if (!ft_strncmp(node->splited_command[0], "env", 4))
		status = env(shell->env);
	else if (!ft_strncmp(node->splited_command[0], "exit", 5)
		&& (!node->prev && !node->next))
	{
		free_process_data(shell);
		builtin_exit(shell, node);
	}
	set_builtin_exit_status(node, shell, status, prevpipe, pipefd);
}

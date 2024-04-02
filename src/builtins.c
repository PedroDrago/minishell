/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:33 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:37:50 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	perform_builtin_redirections(char **splited_command)
{
	int	i;
	int	status;
	int		original_fd;

	i = 0;
	original_fd = dup(0);
	status = 0;
	while(splited_command[i])
	{
		if(is_redirect_input(splited_command[i]))
		{
			status = redirect_input_builtin(splited_command[++i]);
			if (status)
				return (status);
		}
		else if(is_redirect_output(splited_command[i]))
		{
			status = redirect_output_builtin(splited_command[++i]);
			if (status)
				return (status);
		}
		else if(is_heredoc(splited_command[i]))
			do_heredoc(splited_command[++i], original_fd);
		i++;
	}
	return (status);
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

int	prep_builtin(t_node *node, char ***args, t_shell *shell) //NOTE: Yeah bitch, char pointer pointer pointer
{
	int	status;
	expand_arguments(node, shell);
	*args = get_args(node->splited_command);
	if (node->has_pipe)
		dup2(node->node_pipe[1], 1);
	if (node->prev && node->prev->has_pipe)
		dup2(node->node_pipe[0], 0);
	status = perform_builtin_redirections(node->splited_command);
	if (status)
		resolve_builtin_error(status);
	return (status);
}

void	post_builtin(t_node *node, t_shell *shell, char **args, int status)
{
	set_exit_status(status, shell);
	if (node->has_pipe)
		close(node->node_pipe[1]);
	if (node->prev && node->prev->has_pipe)
		close(node->node_pipe[0]);
	dup2(shell->original_stdin, 0);
	dup2(shell->original_stdout, 1);
	(void) args;
}

void	execute_builtin(t_node *node, t_shell *shell)
{
	char	**args;
	int	status;

	status = prep_builtin(node, &args, shell);
	if (status)
	{
		post_builtin(node, shell, args, status);
		return ;
	}
	if (!ft_strncmp(node->splited_command[0], "echo", 5))
		echo(args);
	else if (!ft_strncmp(node->splited_command[0], "cd", 3))
		cd(args, shell);
	else if (!ft_strncmp(node->splited_command[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(node->splited_command[0], "export", 7))
		export(args, shell);
	else if (!ft_strncmp(node->splited_command[0], "unset", 6))
		unset(args, shell);
	else if (!ft_strncmp(node->splited_command[0], "env", 4))
		env(shell->env);
	else if (!ft_strncmp(node->splited_command[0], "exit", 5))
		exit_safely(shell);
	post_builtin(node, shell, args, status);
}

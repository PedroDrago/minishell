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


void	resolve_builtin_error(int status)
{
	if (status == 156)
		ft_putstr_fd("Minishell: Permission for redirected file denied\n", 2);
	else if (status == 157)
		ft_putstr_fd("Minishell: Redirected file not found\n", 2);
}
int	prep_builtin(t_node *node, char ***args) //NOTE: Yeah bitch, char pointer pointer pointer
{
	int	status;
	// WARN: EXPAND_ENVS()
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
	free_split(args);
}
void	execute_builtin(t_node *node, t_shell *shell)
{
	char	**args;
	int	status;

	status = prep_builtin(node, &args);
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

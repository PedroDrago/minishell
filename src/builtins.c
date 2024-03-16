#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_builtin(char *command)
{
	if(!ft_strncmp(command, "echo", 5))
		return (TRUE);
	if(!ft_strncmp(command, "cd", 3))
		return (TRUE);
	if(!ft_strncmp(command, "pwd", 4))
		return (TRUE);
	if(!ft_strncmp(command, "export", 7))
		return (TRUE);
	if(!ft_strncmp(command, "unset", 6))
		return (TRUE);
	if(!ft_strncmp(command, "env", 4))
		return (TRUE);
	if(!ft_strncmp(command, "exit", 5))
		return (TRUE);
	return (FALSE);
}


void	exec_builtin(t_node *node, t_shell *shell, int fd_out)
{
	int	status;

	if(!ft_strncmp(node->command, "echo", 5))
		status = echo(split_len(node->args), node->args, fd_out);
	else if(!ft_strncmp(node->command, "cd", 3))
		status = cd(node, shell);
	else if(!ft_strncmp(node->command, "pwd", 4))
		status = pwd(fd_out);
	else if(!ft_strncmp(node->command, "export", 7))
		status = export(node, shell, fd_out);
	else if(!ft_strncmp(node->command, "unset", 6))
		status = unset(node, shell);
	else if(!ft_strncmp(node->command, "env", 4))
		status = env(shell->env, fd_out);
	else if(!ft_strncmp(node->command, "exit", 5))
		exit_safely(shell);
	set_exit_status(status, shell);
}

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

void	cd(t_node *current, t_shell *shell)
{
	char *cwd;

	cwd = get_cwd();
	set_env_value(shell->env, "OLDPWD" , cwd);
	free(cwd);
	chdir(current->args[1]);
	cwd = get_cwd();
	set_env_value(shell->env, "PWD" , cwd);
	free(cwd);
}

void	exec_builtin(t_node *current, t_shell *shell, int fd_out)
{
	if(!ft_strncmp(current->command, "echo", 5))
		echo(split_len(current->args), current->args, fd_out);
	if(!ft_strncmp(current->command, "cd", 3))
		cd(current, shell);
	if(!ft_strncmp(current->command, "pwd", 4))
		pwd(fd_out);
	// if(!ft_strncmp(current->command, "export", 7))
	// if(!ft_strncmp(current->command, "unset", 6))
	if(!ft_strncmp(current->command, "env", 4))
		env(shell->env, fd_out);
	if(!ft_strncmp(current->command, "exit", 5))
	{
		// FIX: Tem que dar free na lista tb, mas n ta acessivel aqui ainda.
		exit_safely(shell);
	}
	(void) shell;
}

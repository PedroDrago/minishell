#include "../includes/minishell.h"

void	resolve_error(int status, char *command)
{
	//40192 file not found (redirections)
	//39936 no permission for file (redirections)
	if (status == 32512) // command not found (127);
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	else if (status == 32256) // no permission (126);
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (status == 40192)
	{
		ft_putstr_fd("Minishell: Redirected file not found\n", 2);
	}
	else if (status == 39936)
	{
		ft_putstr_fd("Minishell: Permission for redirected file denied\n", 2);
	}

}

void	resolve_builtin_error(int status)
{
	if (status == 156)
		ft_putstr_fd("Minishell: Permission for redirected file denied\n", 2);
	else if (status == 157)
		ft_putstr_fd("Minishell: Redirected file not found\n", 2);
}

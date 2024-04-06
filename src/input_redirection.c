#include "../includes/minishell.h"

int	is_redirect_input(char *token)
{
	if (!ft_strncmp(token, "<", 2))
		return (TRUE);
	return (FALSE);
}

int	redirect_input_builtin(char *file)
{
	int	fd;
	struct stat file_info;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		if (stat(file, &file_info) < 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		return(1);
	}
	dup2(fd, 0);
	return (0);
}

void	redirect_input(char *file)
{
	int	fd;
	struct stat file_info;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		if (stat(file, &file_info) < 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	dup2(fd, 0);
}

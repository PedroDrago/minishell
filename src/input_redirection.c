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
		if (stat(file, &file_info) < 0)
			return (157);
		return (156);
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
		if (stat(file, &file_info) < 0)
			exit (157);
		exit(156);
	}
	dup2(fd, 0);
}

#include "../includes/minishell.h"
#include <stdio.h>

int	is_truncate(char *token)
{
	return (!ft_strncmp(token, ">", 2));
}

int	is_append(char *token)
{
	return (!ft_strncmp(token, ">>", 3));
}

int	is_redirect_output(char *token)
{
	return (is_truncate(token) || is_append(token));
}

void	redirect_output(char *redirection, char *file)
{
	int	tmp_fd;
	struct stat file_info;

	if (is_append(redirection))
	{
		tmp_fd= open(file, O_RDWR | O_APPEND | O_CREAT, 0664);
		if (tmp_fd < 0)
		{
			if (stat(file, &file_info) < 0)
				exit (157);
			perror("[OUT APPEND] Minishell");
			exit(1);
		}
	}
	else
	{
		tmp_fd= open(file, O_RDWR | O_TRUNC | O_CREAT, 0664);
		if (tmp_fd < 0)
		{
			perror("[OUT RED] Minishell");
			if (stat(file, &file_info) < 0)
				exit (157);
			exit(1);
		}
	}
	dup2(tmp_fd, 1);
}


int	redirect_output_builtin(char *redirection, char *file)
{
	int	tmp_fd;
	struct stat file_info;

	if (is_append(redirection))
	{
		tmp_fd= open(file, O_RDWR | O_APPEND | O_CREAT, 0664);
		if (tmp_fd < 0)
		{
			if (stat(file, &file_info) < 0)
				return (157);
			perror("[OUT APPEND BUILTIN] Minishell");
			return (1);
		}
	}
	else
	{
		tmp_fd= open(file, O_RDWR | O_TRUNC | O_CREAT, 0664);
		if (tmp_fd < 0)
		{
			if (stat(file, &file_info) < 0)
				return (157);
			perror("[OUT RED BUILTIN] Minishell");
			return (1);
		}
	}
	dup2(tmp_fd, 1);
	return (0);
}

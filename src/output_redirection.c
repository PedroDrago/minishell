/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:04:05 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:04:06 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	redirect_output(char *redirection, char *file, t_shell *shell)
{
	int			tmp_fd;
	struct stat	file_info;
	int			mode;

	if (is_append(redirection))
		mode = O_APPEND;
	else
		mode = O_TRUNC;
	tmp_fd = open(file, O_RDWR | mode | O_CREAT, 0664);
	if (tmp_fd < 0)
	{
		if (mode == O_APPEND)
			perror("[OUT APPEND] Minishell");
		if (mode == O_TRUNC)
			perror("[OUT RED] Minishell");
		if (stat(file, &file_info) < 0)
		{
			exit_safely(shell, 157);
			/*exit (157);*/
		}
		exit_safely(shell, 1);
		/*exit(1);*/
	}
	dup2(tmp_fd, 1);
}

int	redirect_output_builtin(char *redirection, char *file)
{
	int			tmp_fd;
	struct stat	file_info;
	int			mode;

	if (is_append(redirection))
		mode = O_APPEND;
	else
		mode = O_TRUNC;
	tmp_fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0664);
	if (tmp_fd < 0)
	{
		if (stat(file, &file_info) < 0)
			return (157);
		if (mode == O_APPEND)
			perror("[OUT APPEND BUILTIN] Minishell");
		if (mode == O_TRUNC)
			perror("[OUT RED BUILTIN] Minishell");
		return (1);
	}
	dup2(tmp_fd, 1);
	return (0);
}

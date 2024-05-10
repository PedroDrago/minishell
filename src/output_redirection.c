/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:04:05 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/07 19:19:54 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	file = uncontrol_arg(file);
	if (is_append(redirection))
		mode = O_APPEND;
	else
		mode = O_TRUNC;
	tmp_fd = open(file, O_RDWR | mode | O_CREAT, 0664);
	if (tmp_fd < 0)
	{
		if (mode == O_APPEND)
			perror("Minishell");
		if (mode == O_TRUNC)
			perror("Minishell");
		free_process_data(shell);
		if (stat(file, &file_info) < 0)
			exit_redirect_output(shell, file, 157);
		exit_redirect_output(shell, file, 1);
	}
	dup2(tmp_fd, 1);
	close(tmp_fd);
	free(file);
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
	file = uncontrol_arg(file);
	tmp_fd = open(file, O_RDWR | mode | O_CREAT, 0664);
	if (tmp_fd < 0)
	{
		if (stat(file, &file_info) < 0)
		{
			free(file);
			return (157);
		}
		perror("Minishell");
		free(file);
		return (1);
	}
	dup2(tmp_fd, 1);
	close(tmp_fd);
	free(file);
	return (0);
}

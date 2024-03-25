/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:12 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:18:13 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	is_redirect_input(char *token)
{
	if (!ft_strncmp(token, "<", 2))
		return (TRUE);
	return (FALSE);
}

int	is_heredoc(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (TRUE);
	return (FALSE);
}

void	read_heredoc(int *file, char *delimiter)
{
	char *prompt;
	int	len;

	prompt = readline("> ");
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len))
	{
		ft_putstr_fd(prompt, file[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", file[1]);
		prompt = readline("> ");
	}
}

int	heredoc(t_node *current, t_shell *shell, int fd_out)
{
	int	file[2];
	int	pid;
	int	status;


	pipe(file);
	if (!current->next || !ft_strlen(current->next->command))
		return (printf("Minishell: missing delimiter\n"), FALSE);
	read_heredoc(file, current->next->command);
	if (is_builtin(current->command)) // WARN: No builtin reads from stdin, so redirecting input does nothing | Also, this will segfault if current.next is null
		return (exec_builtin(current, shell, fd_out), close(file[0]), close(file[1]), TRUE);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(file[0], 0);
			dup2(fd_out, 1);
			close(file[1]);
			execute_command(shell, current);
		}
		else
		{
			status = 0;
			close(file[1]);
			close(file[0]);
			waitpid(pid, &status, 0);
			set_exit_status(status, shell);
			if (status > 0)
				resolve_error(status, current);
		}
	}
	return (TRUE);
}

int	redirect_input(t_node *current, t_shell *shell, int fd_out)
{
	int	file;
	int	pid;
	int	status;

	if (is_builtin(current->command)) // WARN: No builtin reads from stdin, so redirecting input does nothing | Also, this will segfault if current.next is null
		return (exec_builtin(current, shell, fd_out), TRUE);
	file = open(current->next->command, O_RDONLY);
	if (file < 0)
		return (ft_putstr_fd("No file or no permission\n", fd_out), FALSE); // FIX: error?
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(file, 0);
			dup2(fd_out, 1);
			execute_command(shell, current);
		}
		else
		{
			status = 0;
			close(file);
			waitpid(pid, &status, 0);
			set_exit_status(status, shell);
			if (status > 0)
				resolve_error(status, current);
		}
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:12:31 by rafaelro          #+#    #+#             */
/*   Updated: 2024/05/05 16:55:14 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	is_heredoc(char *token)
{
	if (!ft_strncmp(token, "<<", 3))
		return (TRUE);
	return (FALSE);
}

void	sighandler(int sig)
{
	close(0);
	(void) sig;
}

int	do_heredoc(char *delimiter, int original_fd, int prevpipe)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;
	int		pid;
	int		status;

	(void)original_fd;
	//dup2(original_fd, 0);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		signal(SIGINT, sighandler);
		prompt = readline("> ");
		if (!prompt)
			exit(0);
		len = ft_strlen(delimiter);
		while (ft_strncmp(prompt, delimiter, len + 1))
		{
			ft_putstr_fd(prompt, pipe_fd[1]);
			ft_putstr_fd("\n", pipe_fd[1]);
			prompt = readline("> ");
			if (!prompt)
				exit(0);
		}
		exit(0);
	}
	close(pipe_fd[1]);
	wait(&status);
	dup2(pipe_fd[0], prevpipe);
	close(pipe_fd[0]);
	return (TRUE);
}

void	exit_heredoc(t_shell *shell, int status)
{
	free_process_data(shell);
	exit_safely(shell, status);
}

void	do_heredoc_builtin(char *delimiter, int original_fd, t_shell *shell)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;

	signal(SIGINT, sighandler);
	dup2(original_fd, 0);
	pipe(pipe_fd);
	prompt = readline("> ");
	if (!prompt)
		exit_heredoc(shell, 1);
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len + 1))
	{
		ft_putstr_fd(prompt, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			exit_heredoc(shell, 1);
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	exit_heredoc(shell, 0);
}

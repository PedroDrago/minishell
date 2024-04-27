/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:12:31 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:12:32 by rafaelro         ###   ########.fr       */
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
	(void) sig;
	exit(2);
}

int	do_heredoc(char *delimiter, int original_fd)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;

	signal(SIGINT, sighandler);
	dup2(original_fd, 0);
	pipe(pipe_fd);
	prompt = readline("> ");
	if (!prompt)
		return (FALSE); // FIX: ????
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len + 1))
	{
		ft_putstr_fd(prompt, pipe_fd[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			return (FALSE); // FIX: ????
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	return (TRUE);
}

int	do_heredoc_builtin(char *delimiter, int original_fd)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;

	signal(SIGINT, sighandler);
	dup2(original_fd, 0);
	pipe(pipe_fd);
	prompt = readline("> ");
	if (!prompt)
		exit(1); // FIX: ????
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len + 1))
	{
		ft_putstr_fd(prompt, pipe_fd[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			exit(1); // FIX: ????
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	exit(0);
	return (TRUE);
}

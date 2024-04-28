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

int	do_heredoc(char *old_delimiter, int original_fd, t_shell *shell)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;
	char	delimiter[500];

	ft_strlcpy(delimiter, old_delimiter, 500);
	signal(SIGINT, sighandler);
	dup2(original_fd, 0);
	pipe(pipe_fd);
	free_before_safely_exit(shell);
	prompt = readline("> ");
	if (!prompt)
		return (FALSE);
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len + 1))
	{
		ft_putstr_fd(prompt, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		prompt = readline("> ");
		if (!prompt)
			return (FALSE);
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	return (TRUE);
}

void	exit_heredoc(t_shell *shell, int status)
{
	free_process_data(shell);
	exit_safely(shell, status);
}

void	do_heredoc_builtin(char *old_delimiter, int original_fd, t_shell *shell)
{
	int		pipe_fd[2];
	char	*prompt;
	int		len;
	char	delimiter[500];
	
	ft_strlcpy(delimiter, old_delimiter,500);
	signal(SIGINT, sighandler);
	dup2(original_fd, 0);
	pipe(pipe_fd);
	free_before_safely_exit(shell);
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

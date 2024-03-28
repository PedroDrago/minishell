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

int	read_heredoc(int *file, char *delimiter)
{
	char *prompt;
	int	len;

	prompt = readline("> ");
	if (!prompt)
		return (FALSE); // FIX: ????
	len = ft_strlen(delimiter);
	while (ft_strncmp(prompt, delimiter, len))
	{
		ft_putstr_fd(prompt, file[1]); // FIX: ctrl+D e ctrl+C?
		ft_putstr_fd("\n", file[1]);
		prompt = readline("> ");
		if (!prompt)
			return (FALSE); // FIX: ????
	}
	return (TRUE);
}

int	heredoc(t_node *current, t_shell *shell, int fd_out)
{
	int	file[2];
	int	pid;
	int	status;


	pipe(file);
	if (!current->next || !ft_strlen(current->next->command))
		return (printf("Minishell: missing delimiter\n"), FALSE);
	if (!read_heredoc(file, current->next->command))
		return (TRUE);
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

int	open_input_file(t_node *node)
{
	int	file;

	if (!node->next || !node->next->command
		|| !ft_strlen(node->next->command))
		return (printf("minishell: Syntax error\n"), -1);
	file = open(node->next->command, O_RDONLY);
	if (file < 0)
		return (-1);
	return (file);
}

int	redirect_input(t_node *node, t_shell *shell)
{
	int	file;

	file = open_input_file(node);
	if (file < 0)
		return (FALSE); // FIX: deu merda pra abrir
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(file, 0);
		execute_command(shell, node);
		exit(1);
	}
	else
		shell->pids->array[shell->pids->index++] = g_pid;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:46:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect_output(char *token)
{
	if (!ft_strncmp(token, ">", 2) || !(ft_strncmp(token, ">>", 3)))
		return (TRUE);
	return (FALSE);
}

void	execute_redirection(t_node *current, t_shell *shell, int *old_yield,
		int file)
{
	dup2(old_yield[0], 0);
	dup2(file, 1);
	close(old_yield[0]);
	close(old_yield[1]);
	close(file);
	execute_command(shell, current);
}

int	open_file(t_node *current)
{
	int	file;

	if (!current->next || !current->next->command
		|| !ft_strlen(current->next->command))
		return (printf("minishell: Syntax error\n"), FALSE);
	if (!ft_strncmp(current->token, ">", 2))
		file = open(current->next->command, O_RDWR | O_TRUNC | O_CREAT, 0664);
	else
		file = open(current->next->command, O_RDWR | O_APPEND | O_CREAT, 0664);
	if (file < 0)
		return (-1);
	return (file);
}

void	redirect_output(t_node *current, t_shell *shell, int *old_yield)
{
	int	file;
	int	pid;
	int	status;

	file = open_file(current);
	if (file < 0)
		return ;
	if (is_builtin(current->command))
		exec_builtin(current, shell, file);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_redirection(current, shell, old_yield, file);
		else
		{
			close(old_yield[0]);
			close(old_yield[1]);
			close(file);
			waitpid(pid, &status, 0);
			set_exit_status(status, shell);
			if (status > 0 && WTERMSIG(status) != SIGINT)
				printf("%s: command not found(output_redirection.c)\n", current->command);
		}
	}
}

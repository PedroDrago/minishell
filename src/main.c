/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/05 18:56:39 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <term.h>
#include <unistd.h>

int		g_sig;

void	pre_prompt(t_shell *shell)
{
	rl_replace_line("", 0);
	kill(getpid(), SIGUSR1);
	(void) shell;
}


int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_shell	shell;

	init_shell(&shell, argc, argv, envp);
	prompt = NULL;
	signal(SIGUSR1, exit_program);
	signal(SIGUSR2, exit_program);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		pre_prompt(&shell);
		shell.has_pipes = 0;
		prompt = get_prompt(&shell);
		if (!validate_prompt(prompt, &shell))
		{
			free(prompt);
			continue ;
		}
		if (!evaluate_prompt(prompt, &shell))
			return (exit_safely(&shell, 1), EXIT_FAILURE);
	}
	return (exit_safely(&shell, 0), EXIT_SUCCESS);
}

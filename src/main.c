/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/04/10 21:42:20 by rafaelro         ###   ########.fr       */
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
	shell->original_stdin = dup(0);
	shell->original_stdout = dup(1);
	g_sig = -1;
}

void	post_prompt(t_shell *shell)
{
	dup2(shell->original_stdin, 0);
	dup2(shell->original_stdout, 1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_shell	*shell;

	shell = init_shell(argc, argv, envp);
	if (!shell)
		exit(1);
	prompt = NULL;
	signal(SIGUSR1, exit_program);
	signal(SIGUSR2, exit_program);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		pre_prompt(shell);
		prompt = get_prompt(shell);
		if (!validate_prompt(prompt, shell))
			continue ;
		if (!evaluate_prompt(prompt, shell))
			return (exit_safely(shell), EXIT_FAILURE);
	}
	return (exit_safely(shell), EXIT_SUCCESS);
}

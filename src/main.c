/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:38:18 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int		g_sig;

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
	while (TRUE)
	{
		rl_replace_line("", 0);
		kill(getpid(), SIGUSR1);
		shell->original_stdin = dup(0);
		shell->original_stdout = dup(1);
		g_sig = -1;
		prompt = get_prompt(shell);
		add_history(prompt);
		if (!prompt || !ft_strlen(prompt) || !valid_quotes(prompt))
			continue ;
		if (!evaluate_prompt(prompt, shell))
			return (exit_safely(shell), EXIT_FAILURE);
		dup2(shell->original_stdin, 0);
		dup2(shell->original_stdout, 1);
	}
	return (exit_safely(shell), EXIT_SUCCESS);
}

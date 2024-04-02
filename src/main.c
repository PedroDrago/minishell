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
#include <stdio.h>
#include <unistd.h>

int		g_pid;

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_shell	*shell;

	shell = init_shell(argc, argv, envp);
	if (!shell)
		exit(1);
	prompt = NULL;
	while (TRUE)
	{
		shell->original_stdin = dup(0);
		shell->original_stdout = dup(1);
		g_pid = 0;
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

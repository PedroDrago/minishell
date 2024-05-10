/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:15 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/07 16:37:49 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_current_envp(t_shell *shell)
{
	t_env	*env;
	int		count;
	char	**env_array;
	char	*node;

	env = shell->env;
	count = 0;
	while (env && ++count)
		env = env->next;
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return ;
	free_split(shell->env_array);
	env = shell->env;
	count = 0;
	while (env)
	{
		node = ft_strjoin(env->key, "=", O_NONE);
		node = ft_strjoin(node, env->value, O_ONE);
		env_array[count++] = node;
		env = env->next;
	}
	env_array[count] = NULL;
	shell->env_array = env_array;
}

int		g_sig;

void	pre_prompt(t_shell *shell)
{
	get_current_envp(shell);
	rl_replace_line("", 0);
	kill(getpid(), SIGUSR1);
	(void)shell;
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

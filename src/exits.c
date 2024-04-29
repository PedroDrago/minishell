/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:12:59 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:12:59 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_program(int sig)
{
	static int	process = 0;

	if (sig == SIGUSR2)
		process = 1;
	if (sig == SIGUSR1)
		process = 0;
	g_sig = sig;
	if (g_sig == SIGINT)
	{
		if (!process)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}

void	free_before_safely_exit(t_shell *shell)
{
	free_process_data(shell);
	free(shell->prompt_string);
	shell->prompt_string = NULL;
	free_env(shell->env);
	shell->env = NULL;
	free_list(shell->prompt_list);
	shell->prompt_list = NULL;
	rl_clear_history();
}

void	exit_safely(t_shell *shell, unsigned char status)
{
	if (shell->prompt_list)
		free_list(shell->prompt_list);
	if (shell->prompt_string)
		free(shell->prompt_string);
	if (shell->env)
		free_env(shell->env);
	rl_clear_history();
	exit(status);
}

void	builtin_exit(t_shell *shell, t_node *node)
{
	int		len;
	int		is_numeric;

	len = split_len(node->args);
	ft_putstr_fd("exit\n", 1);
	if (len == 1)
		exit_safely(shell, 0);
	is_numeric = is_numeric_argument(node->args[1]);
	if (len == 2 && is_numeric)
		if (is_valid_lli(node->args[1]))
			exit_safely(shell, ft_atolli_mod(node->args[1]));
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(node->args[1], 2);
	if (len == 2 && (!is_numeric || !is_valid_lli(node->args[1])))
	{
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_safely(shell, 2);
	}
	if (!is_numeric)
	{
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_safely(shell, 156);
	}
	ft_putstr_fd(": too many arguments\n", 2);
	exit_safely(shell, 1);
}

void	set_builtin_exit_status(t_node *node, t_shell *shell, int status)
{
	int	pid;

	post_builtin(node, shell);
	pid = fork();
	if (pid == 0)
	{
		free_process_data(shell);
		exit_safely(shell, status);
	}
	else
		append_process(pid, shell);
}

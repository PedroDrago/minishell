#include "../includes/minishell.h"

void	exit_program(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_pid == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exit_safely(t_shell *shell)
{
	free(shell->prompt_string);
	free_env(shell->env);
	free(shell);
	exit(1);
}

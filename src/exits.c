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
		if(!process)
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
	free_env(shell->env);
	free(shell);
	rl_clear_history();
}

void	exit_safely(t_shell *shell)
{
	free(shell->prompt_string);
	free_env(shell->env);
	free(shell);
	rl_clear_history();
	exit(0);
}

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	g_pid;

void	exit_program(int sig)
{
	char	*pwd;

	(void)sig;
	write(1, "\n", 1);
	if (g_pid == 0)
	{
		pwd = get_cwd();
		ft_putstr_fd(pwd, 1);
		rl_on_new_line();
		rl_clear_history();
		rl_replace_line("", 0);
		rl_redisplay();
		free(pwd);
	}
}

void	exit_safely(t_shell *shell)
{
	free_env(shell->env);
	free(shell->path);
	free(shell->shell_path);
	free(shell);
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_shell	*shell;

	shell = init_shell(argc, argv[0], envp);
	if (!shell)
		exit(1);
	while (TRUE)
	{
		g_pid = 0;
		ft_putstr_fd(get_env_node(shell->env, "PWD")->value, 1);
		prompt = readline("$ ");
		if (prompt == NULL)
			exit_safely(shell);
		add_history(prompt);
		if (!prompt || !ft_strlen(prompt))
			continue ;
		if (!valid_prompt(prompt))
		{
			write(2, "Minishell: Invalid Prompt\n", 26);
			continue ;
		}
		if (!evaluate_prompt(prompt, shell))
			return (terminate_shell(shell), EXIT_FAILURE);
	}
	return (terminate_shell(shell), EXIT_SUCCESS);
}

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	g_pid;

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
	free_env(shell->env);
	free(shell);
	exit(1);
}

char *create_prompt_str(t_shell *shell)
{
	char	*str;
	char	*user;
	char	*pwd;

	if (shell->prompt_string != NULL)
		free (shell->prompt_string);
	str = ft_calloc(1, 1);
	str = ft_strjoin(str, "\e[1;32m", O_ONE);
	user = get_env_node(shell->env, "USER")->value;
	if (!user)
		user = "username";
	str = ft_strjoin(str, user, O_ONE);
	str = ft_strjoin(str, "\e[0m:\e[1;34m", O_ONE);
	pwd = get_env_node(shell->env, "PWD")->value;
	if (!pwd)
		user = ".";
	str = ft_strjoin(str, pwd, O_ONE);
	str = ft_strjoin(str, "\e[0m$ ", O_ONE);
	shell->prompt_string = str;
	return (str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_shell	*shell;

	shell = init_shell(envp);
	if (!shell)
		exit(1);
	while (TRUE)
	{
		g_pid = 0;
		prompt = readline(create_prompt_str(shell));
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
			return (exit_safely(shell), EXIT_FAILURE);
	}
	(void) argc, (void) argv;
	return (exit_safely(shell), EXIT_SUCCESS);
}

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

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
	if (shell->prompt_list)            //FIX: THis causes a segfault. I don't know why.
		free_list(shell->prompt_list);
	free_env(shell->env);
	if (shell->prompt_string)
		free(shell->prompt_string);
	free(shell);
	exit(1);
}

char *get_env_node_value(t_env *env, char *key)
{
	t_env *node;

	node = get_env_node(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

char *get_prompt_user(char *str, t_shell *shell)
{
	char	*user;

	str = ft_strjoin(str, "\e[1;32m", O_ONE);
	user = get_env_node_value(shell->env, "USER");
	if (!user)
		user = "username";
	str = ft_strjoin(str, user, O_ONE);
	str = ft_strjoin(str, "\e[0m:\e[1;34m", O_ONE);
	return (str);
}

char *get_prompt_pwd(char *str, t_shell *shell)
{
	char	*pwd;
	char	*home;

	pwd = get_env_node(shell->env, "PWD")->value;
	pwd = get_env_node_value(shell->env, "PWD");
	if (!pwd)
		pwd = ".";
	home = get_env_node_value(shell->env, "HOME");
	if (home && !ft_strncmp(pwd, home, ft_strlen(pwd)))
		pwd = "~";
	str = ft_strjoin(str, pwd, O_ONE);
	str = ft_strjoin(str, "\e[0m$ ", O_ONE);
	return (str);
}

char *get_prompt_string(t_shell *shell)
{
	char	*str;

	if (shell->prompt_string != NULL)
		free (shell->prompt_string);
	str = ft_calloc(1, 1);
	str = get_prompt_user(str, shell);
	str = get_prompt_pwd(str, shell);
	shell->prompt_string = str;
	return (str);
}

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	signal(SIGINT, exit_program);
	if (!shell)
		exit(EXIT_FAILURE);
	shell->env = load_envs(envp);
	if (!shell->env)
		return (free(shell), NULL);
	shell->last_status = -99;
	shell->prompt_string = NULL;
	shell->prompt_list = NULL;
	(void) argc, (void) argv;
	return (shell);
}

char *get_prompt(t_shell *shell)
{
	char *prompt;

	prompt = readline(get_prompt_string(shell));
	if (prompt == NULL)
		exit_safely(shell);
	while (prompt[ft_strlen(prompt) - (!!ft_strlen(prompt) * 1)] == '\\')
	{
		prompt[ft_strlen(prompt) - 1] = '\0';
		prompt = ft_strjoin(prompt, readline("> "), O_NONE);
		if (prompt == NULL)
			exit_safely(shell);
	}
	return (prompt);
}
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
		g_pid = 0;
		prompt = get_prompt(shell);
		add_history(prompt);
		if (!prompt || !ft_strlen(prompt) || !valid_quotes(prompt))
			continue ;
		if (!evaluate_prompt(prompt, shell))
			return (exit_safely(shell), EXIT_FAILURE);
	}
	return (exit_safely(shell), EXIT_SUCCESS);
}

#include "../includes/minishell.h"
#include <stdlib.h>

void	exit_program()
{
	printf("Implementar sair do processo atual com ctrl+c\n");
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

	signal(SIGINT, exit_program);
	shell = init_shell(argc, argv[0], envp);
	if (!shell)
		exit(1);
	while (TRUE)
	{
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

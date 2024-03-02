#include "../includes/minishell.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char	*prompt;
	t_shell	*shell;

	shell = init_shell(argc, argv[0]);
	if (!shell)
		exit(1);
	while (TRUE)
	{
		prompt = readline("$ ");
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

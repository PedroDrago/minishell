#include "../includes/minishell.h"

int	terminate_shell(t_shell *shell, int EXIT_STATUS)
{
	free (shell->path);
	free (shell->shell_path);
	return (EXIT_STATUS);
}

int	main(int argc, char *argv[])
{
	char	*prompt;
	t_shell	shell;

	if (!init_shell(&shell, argc, argv[0]))
		return (EXIT_FAILURE);
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
		if (!evaluate(prompt, &shell))
			return (terminate_shell(&shell, EXIT_FAILURE));
	}
	return (terminate_shell(&shell, EXIT_SUCCESS));
}

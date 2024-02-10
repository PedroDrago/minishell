#include "../includes/minishell.h"

int	resolve_prompt(char *prompt, t_shell *shell)
{
	t_command command;
	char **splited;

	splited = ft_split(prompt, ' ');
	if (!splited)
		return (FALSE);
	fill_command(&command, splited);
	if (!resolve_command(command, shell))
		return (FALSE);
	free_split(splited);
	return (TRUE);
}

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
		return (free_split(splited), free_split(command.args), FALSE);
	free_split(splited);
	free_split(command.args);
	return (TRUE);
}

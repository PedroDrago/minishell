#include "../includes/minishell.h"

char	**get_args(char **splited_command)
{
	char	**args;
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while(splited_command[i] && !is_pipe(splited_command[i]))
	{
		count++;
		i++;
		while (splited_command[i] && is_token(splited_command[i]) && !is_pipe(splited_command[i]))
			i += 2;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while(splited_command[i] && !is_pipe(splited_command[i]))
	{
		args[j++] = splited_command[i++];
		while (splited_command[i] && is_token(splited_command[i]) && !is_pipe(splited_command[i]))
			i += 2;
	}
	args[j] = NULL;
	return (args);
}


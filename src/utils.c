#include "../includes/minishell.h"

void	free_split(char **splited)
{
	int	count;

	count = -1;
	while (splited[++count])
		free(splited[count]);
	free (splited);
}

#include "../includes/minishell.h"

int	is_token(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (TRUE);
	if (!ft_strncmp(str, "<<", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">>", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">", 2))
		return (TRUE);
	if (!ft_strncmp(str, "|", 2))
		return (TRUE);
	return (FALSE);
}

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (TRUE);
	return (FALSE);
}

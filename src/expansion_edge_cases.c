#include "../includes/minishell.h"

char	*dup_value(char *arg)
{
	char	*value;

	if (!arg[1])
		value = ft_strdup("$");
	else if (arg[2])
		value = ft_strdup(&arg[2]);
	else
		value = ft_strdup("");
	return (free(arg), value);
}

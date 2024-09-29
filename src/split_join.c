#include "../includes/minishell.h"

void	init_vars(int *j, int *z, int *single_q, int *double_q)
{
	*j = 0;
	*z = 0;
	*single_q = 0;
	*double_q = 0;
}

int	split_str_len(char **splited)
{
	int	i;
	int	j;
	int	z;
	int	inside_single;
	int	inside_double;

	i = -1;
	init_vars(&j, &z, &inside_single, &inside_double);
	while (splited && splited[++i])
	{
		j = 0;
		while (splited[i][j])
		{
			j++;
			z++;
		}
	}
	return (z);
}

int	is_valid_arg_char(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

void	split_join_loop(char **splited, char *join, int z)
{
	int	i;
	int	j;

	i = -1;
	while (splited[++i])
	{
		j = 0;
		while (splited[i] && splited[i][j])
			join[z++] = splited[i][j++];
	}
	join[z] = '\0';
}

char	*split_join(char **splited)
{
	char	*join;

	join = malloc(sizeof(char) * (split_str_len(splited) + 1));
	if (!join)
		return (NULL);
	split_join_loop(splited, join, 0);
	return (join);
}

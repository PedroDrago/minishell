/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:48 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:18:50 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (splited[i][j] && splited[i][j] == '\'')
				j++;
			if (splited[i][j] && splited[i][j] == '\"')
				j++;
			if (!splited[i][j])
				break ;
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
	int	inside_double;
	int	inside_single;
	int	i;
	int	j;

	inside_double = 0;
	inside_single = 0;
	i = -1;
	while (splited[++i])
	{
		j = 0;
		while (splited[i] && splited[i][j])
		{
			if (splited[i][j] == '\'' && (j == 0 || splited[i][j - 1] != '\\'))
				if (!inside_double && ++j)
					inside_single = !inside_single;
			if (splited[i][j] == '\"' && (j == 0 || splited[i][j - 1] != '\\'))
				if (!inside_single && ++j)
					inside_double = !inside_double;
			if (!splited[i][j])
				break ;
			join[z++] = splited[i][j++];
		}
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

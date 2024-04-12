/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:49 by pdrago            #+#    #+#             */
/*   Updated: 2024/04/11 20:27:57 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_edge_cases(char **splited, char *str, char sep)
{
	if (*str == sep)
	{
		splited[0] = ft_strdup(str);
		splited[1] = NULL;
		splited[2] = NULL;
		return (TRUE);
	}
	if (!ft_strchr(str, sep))
	{
		splited[0] = ft_strdup(str);
		splited[1] = NULL;
		splited[2] = NULL;
		return (TRUE);
	}
	if (str[ft_strlen(str) - 1] == sep)
	{
		splited[0] = ft_substr(str, 0, ft_strlen(str) - 1);
		splited[1] = ft_strdup("");
		splited[2] = NULL;
		return (TRUE);
	}
	return (FALSE);
}

char	**split_keyvalue(char *str, char sep)
{
	char	**splited;
	int		j;
	int		i;

	splited = (char **)malloc(sizeof(char *) * 3);
	if (!splited || !str)
		return (NULL);
	if (do_edge_cases(splited, str, sep))
		return (splited);
	j = 0;
	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	splited[0] = ft_substr(str, j, i);
	if (!splited[0])
		return (free_split(splited), NULL);
	i++;
	j = i;
	while (str[i] && str[i] != ' ')
		i++;
	splited[1] = ft_substr(str, j, i);
	if (!splited[1])
		return (free_split(splited), NULL);
	splited[2] = NULL;
	return (splited);
}

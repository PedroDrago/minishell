/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:11:47 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:12:23 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char **splited_command)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (splited_command[i])
	{
		count++;
		i++;
		while (splited_command[i] && is_token(splited_command[i]))
			i += 2;
	}
	return (count);
}

char	**get_args(char **splited_command)
{
	char	**args;
	int		i;
	int		j;

	args = malloc(sizeof(char *) * (count_args(splited_command) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (splited_command[i])
	{
		args[j++] = ft_strdup(splited_command[i++]);
		while (splited_command[i] && is_token(splited_command[i]))
			i += 2;
	}
	args[j] = NULL;
	return (args);
}

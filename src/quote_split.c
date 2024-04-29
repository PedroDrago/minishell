/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:03:34 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:03:35 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int	get_next_quote(char *str, int start, char quote)
{
	while (str[start++])
		if (str[start] == quote)
			return (start);
	return (start);
}

int	get_next_end(char *str, int start)
{
	while (str[start])
	{
		if (str[start + 1] == '\'' || str[start + 1] == '\"')
			return (start);
		start++;
	}
	return (start);
}

int	count_quote_split(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = get_next_quote(str, i, str[i]);
		else
			i = get_next_end(str, i);
		count++;
		if (!str[i])
			return (count);
		i++;
	}
	return (count);
}

void	do_quote_split(char *str, char **splited)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"')
			end = get_next_quote(str, end, str[end]);
		else
			end = get_next_end(str, end);
		*splited++ = command_split_substr(str, start, end);
		if (!str[end])
			break ;
		start = ++end;
	}
	*splited = NULL;
}

char	**quote_split(char *str)
{
	char	**splited;

	if (!str)
		return (NULL);
	splited = (char **)malloc(sizeof(char *) * (count_quote_split(str) + 1));
	if (!splited)
		return (NULL);
	do_quote_split(str, splited);
	return (splited);
}

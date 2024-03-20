/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:19:02 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:19:08 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_quotes(char *prompt)
{
	int	single_quotes;
	int	double_quotes;
	int	count;

	single_quotes = 0;
	double_quotes = 0;
	count = -1;
	while (prompt[++count])
	{
		if (prompt[count] == '\'')
		{
			single_quotes++;
			if (double_quotes % 2 != 0)
				single_quotes = 0;
		}
		else if (prompt[count] == '\"')
		{
			double_quotes++;
			if (single_quotes % 2 != 0)
				double_quotes = 0;
		}
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (write(2, "Minishell: Unclosed quotes\n", 27), FALSE);
	return (TRUE);
}

int	has_invalid_characters(char **splited)
{
	int	i;
	int	j;

	i = 0;
	while (splited[i])
	{
		if ((splited[i][0] == '\'' || splited[i][0] == '\"') && (++i))
			continue ;
		j = 0;
		while (splited[i][j])
		{
			if (splited[i][j] == ';')
				return (TRUE);
			else if (splited[i][j] == '\\')
				if ((size_t)j != ft_strlen(splited[i] - 1))
					return (TRUE);
			j++;
		}
		i++;
	}
	return (FALSE);
}

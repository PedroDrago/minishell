/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:13:24 by pdrago            #+#    #+#             */
/*   Updated: 2024/05/08 15:34:28 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	str_unquote(char **str)
{
	int	j;

	j = 0;
	if (*str[0] == '\"' || *str[0] == '\'')
	{
		ft_memmove(str[j], (const void *)(&str[j][1]), ft_strlen(str[j]));
		while (str[j] && str[j++])
			;
		if (j > 1)
		{
			j--;
			str[j][0] = 4;
		}
	}
}

char	*uncontrol_arg(char *arg)
{
	int		i;
	int		count;
	char	*new_arg;

	i = -1;
	count = 0;
	while (arg[++i])
		if (arg[i] == 4)
			count++;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg) - count + 1));
	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] != 4)
			new_arg[count++] = arg[i];
		i++;
	}
	new_arg[count] = '\0';
	return (new_arg);
}

void	uncontrol_args(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (args[i])
	{
		if (ft_strchr(args[i], 4))
		{
			tmp = args[i];
			args[i] = uncontrol_arg(args[i]);
			free(tmp);
		}
		i++;
	}
}

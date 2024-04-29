/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:45 by pdrago            #+#    #+#             */
/*   Updated: 2024/04/26 20:42:23 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split_len(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

int	echo(char *argv[])
{
	int	flag;
	int	i;

	flag = 0;
	if (split_len(argv) <= 1)
		return (ft_putstr_fd("\n", 1), 0);
	i = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
		flag = i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[++i])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

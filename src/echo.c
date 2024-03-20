/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:45 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:37:56 by pdrago           ###   ########.fr       */
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

int	echo(int argc, char *argv[], int fd_out)
{
	int	flag;
	int	i;

	flag = 0;
	if (split_len(argv) <= 1)
		return (0);
	i = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
		flag = i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd_out);
		if (argv[++i])
			ft_putstr_fd(" ", fd_out);
	}
	if (!flag)
		ft_putstr_fd("\n", fd_out);
	(void)argc;
	return (0);
}

int	exec_echo(t_node *command, int fd_out)
{
	if (!command->token)
		echo(split_len(command->args), command->args, 1);
	else
		echo(split_len(command->args), command->args, fd_out);
	return (TRUE);
}

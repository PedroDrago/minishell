/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:18:40 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:18:40 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(void)
{
	char	*buffer;
	int		size;

	size = 100;
	buffer = (char *) malloc(sizeof(char) * size + 1);
	if (!buffer)
		return (1);
	while (!getcwd(buffer, size))
	{
		free(buffer);
		size += 100;
		buffer = (char *) malloc(sizeof(char) * size);
		if (!buffer)
			return (1);
	}
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	free(buffer);
	return (0);
}

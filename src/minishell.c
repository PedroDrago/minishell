/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:29:05 by pdrago            #+#    #+#             */
/*   Updated: 2024/02/02 11:21:24 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*prompt;
	int		history_fd;

	history_fd = open("history", O_RDWR | O_APPEND | O_CREAT, 0777);
	while (TRUE)
	{
		prompt = readline("$ ");
		if (!register_command(prompt, history_fd)) 
			return (1);
	}
}

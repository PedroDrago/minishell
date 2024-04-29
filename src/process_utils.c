/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:05:05 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:05:05 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_empty_args(t_node *node)
{
	int		i;
	int		j;
	int		emptys;
	char	**new_args;

	i = -1;
	emptys = 0;
	while (node->args[++i])
		if (ft_strlen(node->args[i]) == 0)
			emptys++;
	new_args = malloc(sizeof(char *) * (i - emptys + 1));
	if (!new_args)
		exit(1);
	i = 0;
	j = 0;
	while (node->args[i])
	{
		if (ft_strlen(node->args[i]) == 0 && ++i)
			continue ;
		new_args[j++] = ft_strdup(node->args[i++]);
	}
	new_args[j] = NULL;
	free_split(node->args);
	node->args = new_args;
}

void	free_process_data(t_shell *shell)
{
	free(shell->pids.array);
	shell->pids.array = NULL;
	shell->pids.index = 0;
	shell->pids.size = 0;
}

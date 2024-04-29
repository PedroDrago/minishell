/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelro <rafaelro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:04:22 by rafaelro          #+#    #+#             */
/*   Updated: 2024/04/26 20:11:21 by rafaelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_list_pipes(t_list *list)
{
	t_node	*tmp;
	int		pipe_fd[2];

	tmp = list->head;
	while (tmp)
	{
		if (tmp->has_pipe)
		{
			pipe(pipe_fd);
			tmp->node_pipe[1] = pipe_fd[1];
			tmp->next->node_pipe[0] = pipe_fd[0];
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int	is_token(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (TRUE);
	if (!ft_strncmp(str, "<<", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">>", 3))
		return (TRUE);
	if (!ft_strncmp(str, ">", 2))
		return (TRUE);
	if (!ft_strncmp(str, "|", 2))
		return (TRUE);
	return (FALSE);
}

int	is_pipe(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (TRUE);
	return (FALSE);
}

// line 27: WARN: Needs previous validation so that tmp->next won't be NULL;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:46:24 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:42:49 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

static void	ft_free_all(t_queue *new, int free_content)
{
	t_queuenode	*node;

	while (new)
	{
		node = new->head->next;
		if (free_content)
			free (new->head->content);
		free(new);
		new->head = node;
	}
	free(new);
}

t_queue	*queue_map(t_queue *queue, void *(*func)(void *), int free_content)
{
	t_queuenode	*current;
	t_queuenode	*new_node;
	t_queue		*new_queue;

	if (!queue || !queue->tail || !func)
		return (NULL);
	new_queue = queue_newqueue();
	current = queue->tail;
	while (current)
	{
		new_node = queue_newnode(func(current->content));
		if (!new_node)
		{
			ft_free_all(new_queue, free_content);
			return (NULL);
		}
		enqueue(new_queue, current);
		current = current->previous;
	}
	return (new_queue);
}

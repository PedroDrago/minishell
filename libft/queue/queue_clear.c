/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:36:42 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:05:36 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	queue_clear(t_queue *queue, int free_content)
{
	t_queuenode	*current;
	t_queuenode	*tmp;

	if (!queue || !queue->head)
		return ;
	current = queue->head;
	while (current)
	{
		tmp = current->next;
		if (free_content)
			free (current->content);
		free (current);
		current = tmp;
	}
	queue->size = 0;
}

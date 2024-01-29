/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:22:30 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:44:21 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_queuenode	*dequeue(t_queue *queue)
{
	t_queuenode	*node;

	if (!queue || !queue->tail)
		return (NULL);
	queue->size--;
	node = queue->tail;
	queue->tail->previous->next = NULL;
	queue->tail = queue->tail->previous;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

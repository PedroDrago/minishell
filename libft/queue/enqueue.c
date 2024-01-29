/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:20:27 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:22:11 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	enqueue(t_queue *queue, t_queuenode *node)
{
	if (!queue || !node)
		return ;
	queue->size++;
	if (!queue->head)
	{
		queue->head = node;
		queue->tail = node;
		return ;
	}
	node->next = queue->head;
	queue->head->previous = node;
	queue->head = node;
}

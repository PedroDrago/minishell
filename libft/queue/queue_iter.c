/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:28 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:34:57 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	queue_iter(t_queue *queue, void (*func)(void *))
{
	t_queuenode	*current;

	current = queue->head;
	while (current)
	{
		func(current->content);
		current = current->next;
	}
}

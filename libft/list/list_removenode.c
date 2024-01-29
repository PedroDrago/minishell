/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_removenode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:47:08 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:06:06 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_listnode	*list_removenode(t_list *list, t_listnode *node)
{
	t_listnode	*tmp;

	if (!list || !node)
		return (NULL);
	list->size--;
	if (node == list->head)
	{
		tmp = list->head;
		list->head->next->previous = NULL;
		list->head = list->head->next;
	}
	else if (node == list->tail)
	{
		tmp = list->tail;
		list->tail->previous->next = NULL;
		list->tail = list->tail->previous;
	}
	else
	{
		node->previous->next = node->next;
		node->next->previous = node->previous;
	}
	node->next = NULL;
	node->previous = NULL;
	return (tmp);
}

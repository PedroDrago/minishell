/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_addback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:28:33 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:05:33 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_addback(t_list *lst, t_listnode *new)
{
	if (!lst || !new)
		return ;
	lst->size++;
	if (!lst->head)
	{
		lst->head = new;
		lst->tail = new;
		return ;
	}
	lst->tail->next = new;
	new->previous = lst->tail;
	lst->tail = new;
}

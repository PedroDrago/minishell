/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:28 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:16:59 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_iter(t_list *lst, void (*f)(void *))
{
	t_listnode	*current;

	current = lst->head;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}

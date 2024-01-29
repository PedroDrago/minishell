/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:36:42 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:07:44 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_clear(t_list *list, int free_content)
{
	t_listnode	*current;
	t_listnode	*tmp;

	if (!list || !list->head)
		return ;
	current = list->head;
	while (current)
	{
		tmp = current->next;
		if (free_content)
			free (current->content);
		free (current);
		current = tmp;
	}
}

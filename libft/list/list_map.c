/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:46:24 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:45:31 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	ft_free_all(t_list *new, int free_content)
{
	t_listnode	*node;

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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), int free_content)
{
	t_listnode	*new_node;
	t_list		*new_list;

	if (!f || !lst)
		return (NULL);
	new_list = list_newlist();
	while (lst)
	{
		new_node = list_newnode(f(lst->head->content));
		if (!new_node)
		{
			ft_free_all(new_list, free_content);
			lst = NULL;
			return (NULL);
		}
		list_addback(new_list, new_node);
		lst->head = lst->head->next;
	}
	return (new_list);
}

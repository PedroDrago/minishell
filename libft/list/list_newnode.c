/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_newnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:10:35 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 10:11:36 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_listnode	*list_newnode(void *content)
{
	t_listnode	*node;

	node = (t_listnode *) malloc (sizeof(t_listnode));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_newnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:02:44 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:03:36 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stacknode	*new_node(void *content)
{
	t_stacknode	*node;

	node = (t_stacknode *) malloc (sizeof(t_stacknode));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->previous = NULL;
	node->content = content;
	return (node);
}

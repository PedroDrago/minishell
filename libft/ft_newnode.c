/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:00:58 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 12:23:43 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_newnode(void *content)
{
	t_node	*node;

	node = (t_node *) malloc (sizeof(content) + sizeof (t_node *));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

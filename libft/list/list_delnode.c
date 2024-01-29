/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:34:35 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:22:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_delnode(t_listnode *node, int free_content)
{
	if (free_content)
		free (node->content);
	free(node);
}

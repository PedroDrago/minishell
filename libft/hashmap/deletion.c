/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:32:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 21:32:22 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

void	destroy_hashnode(t_hashnode *node)
{
	if (node->allocation_flag == KEY_MALLOCED)
		free(node->key);
	else if (node->allocation_flag == VALUE_MALLOCED)
		free(node->value);
	else if (node->allocation_flag == BOTH_MALLOCED)
	{
		free(node->key);
		free(node->value);
	}
	free (node);
}

void	destroy_map(t_hashmap *hashmap)
{
	unsigned int	count;
	t_hashnode		*current;
	t_hashnode		*next;

	count = 0;
	while (count < hashmap->max_size)
	{
		if (hashmap->array[count] != NULL)
		{
			current = hashmap->array[count];
			while (current != NULL)
			{
				next = current->next;
				destroy_hashnode(current);
				current = next;
			}
		}
		count++;
	}
	free (hashmap->array);
	free (hashmap);
}

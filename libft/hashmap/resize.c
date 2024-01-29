/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:36:52 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 23:44:05 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

void	*resize(t_hashmap *map)
{
	unsigned int	count;
	t_hashmap		*newmap;

	newmap = create_hashmap(map->current_size + 20);
	if (!newmap)
		return (NULL);
	count = 0;
	while (count < map->current_size)
	{
		if (map->array[count] != NULL)
		{
			newmap->array[poor_hash(map->array[count]->key)
				% newmap->max_size] = map->array[count];
			newmap->current_size++;
		}
		count++;
	}
	destroy_map(map);
	map = newmap;
	return (map);
}

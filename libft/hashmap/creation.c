/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:34:43 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 21:33:30 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

t_hashnode	*create_hashnode(unsigned char *key,
				void *value, int allocation_flag)
{
	t_hashnode	*n;

	if (!value || !key)
		return (NULL);
	n = (t_hashnode *) malloc (sizeof(t_hashnode));
	if (!n)
		return (NULL);
	n->key = key;
	n->value = value;
	n->next = NULL;
	n->allocation_flag = allocation_flag;
	return (n);
}

t_hashmap	*create_hashmap(unsigned int max_size)
{
	t_hashmap		*map;
	unsigned int	count;

	if (max_size < 1)
		return (NULL);
	map = (t_hashmap *) malloc (sizeof(t_hashmap));
	if (!map)
		return (NULL);
	map->array = (t_hashnode **) malloc (sizeof(t_hashnode *) * max_size);
	if (!map->array)
		return (NULL);
	map->max_size = max_size;
	map->current_size = 0;
	count = 0;
	while (count < max_size)
		map->array[count++] = NULL;
	return (map);
}

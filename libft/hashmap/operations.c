/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:32:30 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 21:33:05 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (0);
	while ((((unsigned char) s1[count]) == ((unsigned char) s2[count]))
		&& (s1[count]) && (s2[count]) && (--n))
		count++;
	return ((unsigned char) s1[count] - (unsigned char) s2[count]);
}

static void	insert_node(t_hashmap *hashmap, unsigned char *key
			, unsigned long key_index, t_hashnode *newnode)
{
	t_hashnode	*current;

	if (hashmap->array[key_index] == NULL)
	{
		hashmap->array[key_index] = newnode;
		return ;
	}
	if (!ft_strncmp((const char *) hashmap->array[key_index]->key
			, (const char *)key, ft_strlen((const char *) key)))
	{
		destroy_hashnode(hashmap->array[key_index]);
		hashmap->array[key_index] = newnode;
		return ;
	}
	current = hashmap->array[key_index];
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
}

void	insert(t_hashmap *hashmap, unsigned char *key,
		void *value, int allocation_flag)
{
	unsigned long	key_index;
	t_hashnode		*newnode;

	if (!hashmap || !key || !value)
		return ;
	hashmap->current_size++;
	if (hashmap->current_size > hashmap->max_size)
		if (!resize(hashmap))
			return ;
	key_index = poor_hash(key) % hashmap->max_size;
	newnode = create_hashnode(key, value, allocation_flag);
	if (!newnode)
		return ;
	insert_node(hashmap, key, key_index, newnode);
}

void	*get(t_hashmap *hashmap, unsigned char *key)
{
	unsigned long	key_index;
	t_hashnode		*current;

	if (!hashmap || !key)
		return (NULL);
	key_index = poor_hash(key) % hashmap->max_size;
	if (hashmap->array[key_index] == NULL)
		return (NULL);
	if (hashmap->array[key_index]->next == NULL)
		return (hashmap->array[key_index]->value);
	current = hashmap->array[key_index];
	while (current != NULL
		&& ft_strncmp((const char *) current->key, (const char *) key
			, ft_strlen((const char *) key)))
		current = current->next;
	return (current->value);
}

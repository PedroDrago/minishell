/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:59:37 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/27 04:21:26 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>

# ifndef NONE_MALLOCED
#  define NONE_MALLOCED 0
# endif

# ifndef KEY_MALLOCED
#  define KEY_MALLOCED 1
# endif

# ifndef VALUE_MALLOCED
#  define VALUE_MALLOCED 2
# endif

# ifndef BOTH_MALLOCED
#  define BOTH_MALLOCED 3
# endif

typedef struct s_hashnode
{
	struct s_hashnode	*next;
	unsigned char		*key;
	int					allocation_flag;
	void				*value;
}	t_hashnode;

typedef struct s_hashmap
{
	unsigned int			max_size;
	unsigned int			current_size;
	t_hashnode				**array;
}	t_hashmap;

unsigned long	poor_hash(unsigned char *key);
t_hashnode		*create_hashnode(unsigned char *key,
					void *value, int allocation_flag);
t_hashmap		*create_hashmap(unsigned int max_size);
void			*resize(t_hashmap *map);
void			*get(t_hashmap *hashmap, unsigned char *key);
void			destroy_map(t_hashmap *hashmap);
void			destroy_hashnode(t_hashnode *node);
void			insert(t_hashmap *hashmap, unsigned char *key,
					void *value, int allocation_flag);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:33:14 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 21:33:16 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

unsigned long	poor_hash(unsigned char *key)
{
	int				count;
	unsigned long	hash;

	if (!key)
		return (0);
	hash = 0;
	count = -1;
	while (key[++count])
		hash += key[count];
	return (hash);
}

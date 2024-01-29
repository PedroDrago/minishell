/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:20:17 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:55 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	count;

	count = 0;
	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	while (count < n)
	{
		if (ptr1[count] != ptr2[count])
			return ((unsigned char)ptr1[count] - (unsigned char)ptr2[count]);
		count++;
	}
	return (0);
}

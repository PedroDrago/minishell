/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:10 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:57 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr_s;
	size_t	count;

	ptr_s = (char *) s;
	count = 0;
	while (count < n)
	{
		if (ptr_s[count] == c)
			return ((void *) s + count);
		count++;
	}
	return (NULL);
}

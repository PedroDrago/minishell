/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:39:29 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:50 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		count;
	char	*srcpy;
	char	*destcpy;

	srcpy = (char *) src;
	destcpy = (char *) dest;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		count = n - 1;
		while (count >= 0)
		{
			destcpy[count] = srcpy[count];
			count--;
		}
	}
	else
	{
		count = -1;
		while (++count < (int) n)
			destcpy[count] = srcpy[count];
	}
	return (dest);
}

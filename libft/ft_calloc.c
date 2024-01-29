/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 03:27:11 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:25:41 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocation;

	if (nmemb == 0 || size == 0)
	{
		allocation = malloc (1);
		return (allocation);
	}
	allocation = malloc (nmemb * size);
	if (!allocation)
		return (NULL);
	ft_bzero(allocation, (nmemb * size));
	return (allocation);
}

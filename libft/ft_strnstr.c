/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:17:00 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_count;
	size_t	little_count;

	if (!ft_strlen(little) || big == little)
		return ((char *)big);
	big_count = 0;
	little_count = 0;
	while (big[big_count] && big_count < len)
	{
		if (big[big_count] == little[0])
		{
			while (big[big_count + little_count]
				&& (little[little_count] == big[big_count + little_count])
				&& (big_count + little_count < len))
				little_count++;
			if (little[little_count] == '\0')
				return ((char *)&big[big_count]);
			little_count = 0;
		}
		big_count++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:24 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:15 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	count;

	count = 0;
	map = (char *) malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!map)
		return (NULL);
	while (s[count])
	{
		map[count] = f(count, s[count]);
		count++;
	}
	map[count] = '\0';
	return (map);
}

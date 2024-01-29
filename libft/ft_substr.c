/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:02:21 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:23:59 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	count2;
	char	*substr;

	if (start >= ft_strlen(s))
	{
		substr = (char *) malloc (1);
		substr[0] = 0;
		return (substr);
	}
	substr = (char *)malloc(sizeof(*s) * (len + 1));
	if (!substr)
		return (NULL);
	count = 0;
	count2 = 0;
	count = start;
	while (s[count] && count2 < len)
	{
		substr[count2] = s[count];
		count2++;
		count++;
	}
	substr[count2] = 0;
	return (substr);
}

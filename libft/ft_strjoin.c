/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 03:17:57 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/14 11:42:21 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_vars(char *s1, char *s2, int should_free)
{
	if (should_free == 1)
		free (s1);
	else if (should_free == 2)
		free (s2);
	else if (should_free == 3)
	{
		free (s1);
		free (s2);
	}
}

char	*ft_strjoin(char const *s1, char const *s2, int should_free)
{
	char	*joined;
	int		count;

	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	count = 0;
	if (s1)
	{
		while (s1[count])
		{
			joined[count] = s1[count];
			count++;
		}
	}
	while (*s2)
		joined[count++] = *s2++;
	joined[count] = '\0';
	free_vars((char *)s1, (char *) s2, should_free);
	return (joined);
}

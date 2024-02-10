/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 03:17:57 by pdrago            #+#    #+#             */
/*   Updated: 2024/02/09 21:48:37 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_vars(char *s1, char *s2, int should_free)
{
	if (should_free == O_ONE)
		free (s1);
	else if (should_free == O_TWO)
		free (s2);
	else if (should_free == O_BOTH)
	{
		free (s1);
		free (s2);
	}
}

static void	concatenate_s1(char const *s1, char *joined)
{
	int	count;

	count = 0;
	if (!s1)
		return ;
	while (s1[count])
	{
		joined[count] = s1[count];
		count++;
	}
	joined[count] = '\0';
}

static void	concatenate_s2(char const *s2, char *joined)
{
	int	count2;
	int	count;

	if (!s2)
		return ;
	count2 = 0;
	count = 0;
	while (joined[count])
		count++;
	while (s2[count2])
	{
		joined[count] = s2[count2];
		count++;
		count2++;
	}
	joined[count] = '\0';
}

char	*ft_strjoin(char *s1, char *s2, int should_free)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	concatenate_s1(s1, joined);
	concatenate_s2(s2, joined);
	return (free_vars((char *)s1, (char *) s2, should_free), joined);
}

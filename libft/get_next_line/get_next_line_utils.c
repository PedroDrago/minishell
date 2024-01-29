/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:46:03 by pdrago            #+#    #+#             */
/*   Updated: 2023/11/16 23:11:38 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_break_line(const char *s)
{
	int		count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
	{
		if (s[count] == '\n')
			return (1);
		count++;
	}
	return (0);
}

int	gnl_len(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
		count++;
	return (count);
}

char	*ft_joinfree(char *s1, char *s2)
{
	char	*joined;
	int		count;

	joined = (char *)malloc(sizeof(char) * (gnl_len(s1) + gnl_len(s2) + 1));
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
		free (s1);
	}
	while (*s2)
		joined[count++] = *s2++;
	joined[count] = '\0';
	if (!(*joined))
	{
		free (joined);
		return (NULL);
	}
	return (joined);
}

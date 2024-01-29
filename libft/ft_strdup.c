/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:38:29 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:30 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		count;

	ret = (char *) malloc (sizeof(char) * ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	count = 0;
	while (s[count])
	{
		ret[count] = s[count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}

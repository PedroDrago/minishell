/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:52:26 by pdrago            #+#    #+#             */
/*   Updated: 2023/11/26 01:54:39 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_idx(const char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (-1);
	while (str[count] && str[count] != c)
		count++;
	return (count);
}

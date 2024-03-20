/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_edge_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:22:44 by pdrago            #+#    #+#             */
/*   Updated: 2024/03/20 17:22:46 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dup_value(char *arg)
{
	char	*value;

	if (!arg[1])
		value = ft_strdup("$");
	else if (arg[2])
		value = ft_strdup(&arg[2]);
	else
		value = ft_strdup("");
	return (free(arg), value);
}

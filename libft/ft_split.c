/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 01:58:34 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:37 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_count(char const *str, char sep)
{
	int	index;
	int	splits;

	if (str == 0 || str[0] == 0)
		return (0);
	index = 1;
	splits = 0;
	if (str[0] != sep)
		splits++;
	while (str[index] != '\0')
	{
		if (str[index] != sep && str[index - 1] == sep)
			splits++;
		index++;
	}
	return (splits);
}

static int	ft_next_split_count(char const *str, char sep, int index)
{
	int	count;

	count = 0;
	while (str[index] == sep && str[index] != '\0')
		index++;
	while (str[index] != '\0' && str[index] != sep)
	{
		count++;
		index++;
	}
	return (count);
}

static char	**ft_free_all(char **str_tab, int max)
{
	int	index;

	index = 0;
	while (index < max && str_tab[index] != 0)
	{
		free(str_tab[index]);
		index++;
	}
	free(str_tab);
	return (0);
}

static char	**ft_split_split(char const *s, char c, char **tab_str)
{
	int		char_s;
	int		tab_count;
	int		char_tab;

	char_s = 0;
	tab_count = -1;
	while (++tab_count < ft_split_count(s, c))
	{
		char_tab = 0;
		tab_str[tab_count] = (char *) malloc(sizeof(char)
				* ft_next_split_count(s, c, char_s) + 1);
		if (!(tab_str[tab_count]))
			return (ft_free_all(tab_str, tab_count));
		while (s[char_s] != '\0' && s[char_s] == c)
			char_s++;
		while (s[char_s] != '\0' && s[char_s] != c)
			tab_str[tab_count][char_tab++] = s[char_s++];
		tab_str[tab_count][char_tab] = '\0';
	}
	tab_str[tab_count] = 0;
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;

	if (s == 0)
		return (0);
	tab_str = (char **) malloc(sizeof(*tab_str) * (ft_split_count(s, c) + 1));
	if (!(tab_str))
		return (0);
	tab_str = ft_split_split(s, c, tab_str);
	return (tab_str);
}
